#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#define x_val 4
#define y_val 5

#define M1_IN1_PIN 5
#define M1_IN2_PIN 6
#define M1_ENC_A 3
#define M1_ENC_B 4

#define M2_IN1_PIN 10
#define M2_IN2_PIN 11
#define M1_ENC_A 8
#define M1_ENC_B 9


// GLOBALS

int x = 512;
int y = 512;

int j = 0;

double FULL_TILT = 0.6  //rad/s

int M1_PINS[] = {M1_IN1_PIN, M1_IN2_PIN, M1_ENC_A, M1_ENC_B};
int M1_DES = 0;

int M2_PINS[] = {M2_IN1_PIN, M2_IN2_PIN, M2_ENC_A, M2_ENC_B};
int M2_DES = 0;

int K_P = 10;
int K_I = 0;
unsigned long START = 0;

volatile int M1_VEL = 0;
int M1_POS = -999;
volatile int M1_POS_LAST = -999;
volatile int M2_VEL = 0;
int M2_POS = -999;
volatile int m2_POS_LAST = -999;

Motor_DC motor_1(M1_PINS, K_P, K_I);
Motor_DC motor_2(M2_PINS, K_P, K_I);

void setup() {

    CNT1 = 0; // Reset timer counter

    OCR1A = 160; // Set compare match value for 10ms

    // Set Timer 1 mode to CTC with prescaler 1
    TCCR1A = (1 << WGM11);
    TCCR1B = (1 << CS10);

    // Enable Timer 1 interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Initialize interrupt handler
    attachInterruptVector(TIMER1_vel, timer1ISR,  INTERRUPT_MODE);
    motor_1.stop()
    motor_2.stop()
    delay(1000); // Stop for 1 second

    Serial.begin(9600); // Initialize serial communication
}

int read_joystick(){
    x = analogRead(x_val);
    y = analogRead(y_val);
}

void on_off(){
    on = !on;
}

void compress(){
    double y_norm = (y-510)/510;
    double x_norm = (x-510)/510;
    int max_speed = y_norm * FULL_TILT;
    if (x_norm > 0.3){
        M1_DES = max_speed;
        M2_DES = y_norm*x_norm*FULL_TILT;
    }
    else if (x_norm < -0.3){
        M1_DES = y_norm*abs(x_norm)*FULL_TILT;
        M2_DES = max_speed;
    }
    else{
        M1_DES = max_speed;
        M2_DES = max_speed;
    }
}

void decompress(){
    double y_norm = (y-510)/510;
    double x_norm = (x-510)/510;
    int max_speed = abs(y_norm)*FULL_TILT;
    if (x_norm > 0.3){
        M1_DES = max_speed;
        M2_DES = y_norm*x_norm*FULL_TILT;
    }
    else if (x_norm < -0.3){
        M1_DES = y_norm*abs(x_norm)*FULL_TILT;
        M2_DES = max_speed;
    }
    else{
        M1_DES = max_speed;
        M2_DES = max_speed;
    }

}

void print_xy(){
  Serial.print("x = ");
  Serial.print(x);
  Serial.print(" y = ");
  Serial.print(y);
  Serial.println();
}

ISR(TIMER1_vel){
    M1_POS = motor_1.get_angle();  //rad
    M2_POS = motor_2.get_angle();  //rad
    M1_VEL = (M1_POS-M1_POS_LAST)/.01  //rad/s
    M2_VEL = (M2_POS-M2_POS_LAST)/.01  //rad/s
    M1_POS_LAST = M1_POS;
    M2_POS_LAST = M2_POS;
}

void loop() {
  

  read_joystick();

  if (y > 550){
      compress();
      START = millis();
      while (START-millis() < 20){
        motor_1.pid(M1_VEL,M1_DES);
        motor_2.pid(M2_VEL,M2_DES);
        motor_1.go();
        motor_2.go();
      }
  }
  else if (y < 470){
      decompress();
      START = millis();
      while (START-millis() < 20){
        motor_1.pid(M1_VEL,M1_DES);
        motor_2.pid(M2_VEL,M2_DES);
        motor_1.go();
        motor_2.go();
      }
  }
  else{
      stop();
  }
}

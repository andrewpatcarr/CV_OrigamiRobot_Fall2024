#include <Encoder.h>

#define x_val 4
#define y_val 5

#define M1_IN1_PIN 5
#define M1_IN2_PIN 6
#define M1_ENC_A 2
#define M1_ENC_B 8

#define M2_IN1_PIN 10
#define M2_IN2_PIN 11
#define M2_ENC_A 3
#define M2_ENC_B 9

Encoder enc_1(M1_ENC_A, M1_ENC_B);
Encoder enc_2(M2_ENC_A, M2_ENC_B);
// GLOBALS

double x = 512;
double y = 512;

int j = 0;

double FULL_TILT = 10;  //degrees. Need to find what is a good number for each jump
int PREV_DIR = 0;

int M1_PINS[2] = {M1_IN1_PIN, M1_IN2_PIN};
double M1_DES = 0;

int M2_PINS[2] = {M2_IN1_PIN, M2_IN2_PIN};
double M2_DES = 0;

int K_P = 10;
int K_I = 1;
int PID_TIME = 20;
unsigned long START = 0;
unsigned long LAST_TIME = 0;

volatile int M1_VEL = 0;
double M1_POS = -999;
volatile int M1_POS_LAST = -999;
volatile int M2_VEL = 0;
double M2_POS = -999;
volatile int M2_POS_LAST = -999;

class Motor_DC
{
  private:
      int in1;
      int in2;
      int encA;
      int encB;
      double k_p;
      double k_i;
      double interval;
      int error;
      double integral;
      unsigned long prev_time;
      int speed;
      double output;
      int pwm;
      double pos;
      double last_pos;
      int angle;
      double vel;
      unsigned long vel_time;
      unsigned long last_vel_time;

  public:
      Motor_DC(int pins[2], int k_p, int k_i){
          in1 = pins[0];
          in2 = pins[1];
          this->k_p = k_p;
          this->k_i = k_i;
          
      }
      void init(){
          pinMode(in1, OUTPUT);
          pinMode(in2, OUTPUT);
          //pinMode(encA, INPUT);
          //pinMode(encB, INPUT);
          
      }
      void pid(int des){
          interval = millis() - prev_time;
          prev_time = millis();
          
          error = pos - des;
          integral += error * interval;
          //Serial.print("Error: ");
          //Serial.println(error);
          output = k_p*error + k_i*integral;
          
      }
      void forward(int pwm){
          analogWrite(in1, pwm);
          analogWrite(in2, 0);
          //Serial.println(" forwarded ");
      }
      void reverse(int pwm){
          analogWrite(in1, 0);
          analogWrite(in2, pwm);
          //Serial.println(" reversed ");
      }
      void stop(){
          analogWrite(in1, 0);
          analogWrite(in2, 0);
      }
      void go(){
          integral = 0;
          pwm = abs(output);
          //Serial.print("Output: ");
          //Serial.print(output);
          //Serial.print(" PWM: ");
          //Serial.print(pwm);
          if (output > 0){
              forward(min(pwm,255));
          }
          else if (output < 0){
              reverse(min(pwm,255));
          }
          else {
              stop();
          }
      }
      void update_pos(double pos){
          this->pos = pos;
          
      }
      void clear_integral(){
          integral = 0;
      }

};

Motor_DC motor_1(M1_PINS, K_P, K_I);
Motor_DC motor_2(M2_PINS, K_P, K_I);

void setup() {

  motor_1.init();
  motor_2.init();
  motor_1.stop();
  motor_2.stop();
  delay(500); // Stop for 1 second

  Serial.begin(9600); // Initialize serial communication
  delay(500);
  Serial.println("done with setup");

}
int i = 0;
void loop() {
  if (i != 0){
      motor_1.forward(100);
      delay(1000);
      motor_1.reverse(100);
      delay(1000);
      i++;
  }
  

  read_joystick();
  //print_xy();
  if (y > 550){
      check_dir(0);
      compress();
      //Serial.print("M1 Pos: ");
      //Serial.print(get_m1_angle());
      //Serial.print(" Des pos: ");
      //Serial.println(M1_DES);
      // add way to ensure back to even tension when coming from turn back to compression
      START = millis();
      while (millis() - START < PID_TIME){
        do_pid();
      }
      
  }
  else if (y < 470){
      check_dir(1);
      decompress();
      //Serial.print("M1 Pos: ");
      //Serial.print(get_m1_angle());
      //Serial.print(" Des pos: ");
      //Serial.println(M1_DES);
      // add way to ensure back to even tension when coming from turn back to decompression
      START = millis();
      while (millis()-START < PID_TIME){
        do_pid();
      }
  }
  else{
      motor_1.stop();
      motor_2.stop();
      delay(PID_TIME);
  }
}

int read_joystick(){
    x = analogRead(x_val);
    y = analogRead(y_val);
}

double get_m1_angle(){
    long pos = enc_1.read();
    double angle = pos*180/(12*297.92);  //degree
    return angle;
}
double get_m2_angle(){
    long pos = enc_2.read();
    double angle = pos*180/(12*297.92);  //degree
    return angle;
}

void compress(){
    Serial.print("y: ");
    Serial.print(y);
    double y_norm = (y-510)/510;
    Serial.print(" y_norm: ");
    Serial.print(y_norm);
    
    double x_norm = (x-482)/510;
    double max_speed = ((y-510)/510) * FULL_TILT;
    //double max_speed = 1;
    if (x_norm > 0.3){
        M1_DES += max_speed;
        M2_DES += x_norm * FULL_TILT;
    }
    else if (x_norm < -0.3){
        M1_DES += abs(x_norm) * FULL_TILT;
        M2_DES += max_speed;
    }
    else{
        M1_DES += max_speed;
        M2_DES += max_speed;
    }
    
    Serial.print(" compress: ");
    Serial.println(max_speed);
}

void decompress(){
    double y_norm = (y-510)/510;
    double x_norm = (x-510)/510;
    double max_speed = -abs(y_norm) * FULL_TILT;
    //double max_speed = -1;
    if (x_norm > 0.3){
        M1_DES += max_speed;
        M2_DES += -abs(y_norm)*x_norm * FULL_TILT;
    }
    else if (x_norm < -0.3){
        M1_DES += -y_norm*abs(x_norm) * FULL_TILT;
        M2_DES += max_speed;
    }
    else{
        M1_DES += max_speed;
        M2_DES += max_speed;
    }
    Serial.print("y: ");
    Serial.print(y);
    Serial.print(" y_norm: ");
    Serial.print(y_norm);
    Serial.print(" decompress: ");
    Serial.println(max_speed);

}
void print_xy(){
  Serial.print("x = ");
  Serial.print(x);
  Serial.print(" y = ");
  Serial.print(y);
  Serial.println();
}
void do_pid(){
  M1_POS = get_m1_angle();
  M2_POS = get_m2_angle();
  motor_1.update_pos(M1_POS);
  motor_2.update_pos(M2_POS);
  motor_1.pid(M1_DES);
  motor_2.pid(M2_DES);
  motor_1.go();
  motor_2.go();
  delay(5);
}
void check_dir(int dir){
  if (dir != PREV_DIR){
    motor_1.clear_integral();
    motor_2.clear_integral();
    M1_DES = M1_POS;
    M2_DES = M2_POS;
    PREV_DIR = dir;
  }
}

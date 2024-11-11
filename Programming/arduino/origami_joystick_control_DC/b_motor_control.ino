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
    int pos;
    int angle;

public:
    Motor_DC(pins, k_p, k_i){
        in1 = pins[0];
        in2 = pins[1];
        encA = pins[2];
        encB = pins[3];
        this->k_p = k_p;
        this->k_i = k_i;
    }
    void init(){
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        //pinMode(encA, INPUT);
        //pinMode(encB, INPUT);
        Encoder enc(encA, encB);
    }
    void pid(){
        interval = millis() - prev_time;
        prev_time = millis();
        speed = vel;
        error = speed - vel;
        integral += error * interval;

        output = k_p*error + k_i*integral;
    }
    void forward(pwm){
        analogWrite(in1, pwm);
        analogWrite(in2, 0);
    }
    void reverse(pwm){
        analogWrite(in1, 0);
        analogWrite(in2, pwm);
    }
    void stop(){
        analogWrite(in1, 0);
        analogWrite(in2, 0);
    }
    void go(){
        pwm = abs(output);
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
    double get_angle(){
        pos = enc.read();
        angle = pos*2*pi()/(12*297.92);  //rad
        return angle;
    }

};
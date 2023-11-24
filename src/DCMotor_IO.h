#include <ESP32_Servo.h>

#define RC_RECEIVER_PIN 19

#define DCMOTOR_THROTTLE_NEUTRAL_FREQ 1500
#define DCMOTOR_THROTTLE_FORWARD_MAX_FREQ 1350
#define DCMOTOR_THROTTLE_BACKWARDS_MAX_FREQ 1580



class DCMotor_IO
{
    public:
        
        DCMotor_IO(/* args */);
        ~DCMotor_IO();

        void initDCMotor();
        void runDCMotor(int speed);
        void runDCMotor(int thresh, int speed, int inputMinMax[2]);
        void stopDCMotor();

        void mapSpeed();

    private:

        Servo dcMotorThrottle = Servo();
        int dcMotorSpeed = DCMOTOR_THROTTLE_NEUTRAL_FREQ;

};

DCMotor_IO::DCMotor_IO(/* args */){}
DCMotor_IO::~DCMotor_IO(){}

void DCMotor_IO::initDCMotor()
{  
    dcMotorThrottle.attach(RC_RECEIVER_PIN);
}



void DCMotor_IO::runDCMotor(int speed)
{
    dcMotorThrottle.write(speed);
}

void DCMotor_IO::runDCMotor(int thresh, int speed, int inputMinMax[2])
{   
    int tmpSpeed;
    if(speed > -thresh)
    {
        tmpSpeed = map( speed, 
                            thresh,
                            inputMinMax[1],
                            DCMOTOR_THROTTLE_NEUTRAL_FREQ,
                            DCMOTOR_THROTTLE_FORWARD_MAX_FREQ);
        dcMotorThrottle.write(tmpSpeed);
    }
    if(speed < thresh)
    {
        tmpSpeed = map( speed, 
                            inputMinMax[0],
                            thresh,
                            DCMOTOR_THROTTLE_BACKWARDS_MAX_FREQ,
                            DCMOTOR_THROTTLE_NEUTRAL_FREQ);
        dcMotorThrottle.write(tmpSpeed);
    }
}

void DCMotor_IO::stopDCMotor()
{
    dcMotorThrottle.write(DCMOTOR_THROTTLE_NEUTRAL_FREQ);
}




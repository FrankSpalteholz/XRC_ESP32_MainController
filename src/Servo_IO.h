#include <HCPCA9685.h>
#include "elapsedMillis.h"
#include <Wire.h>

#define SERVO_COUNT 3
#define L2C_SERVO_DRIVER_ADR 0x40

#define SERVO_GIMBAL_YAW_PIN 14
#define SERVO_GIMBAL_PITCH_PIN 15
#define SERVO_STEER_PIN 0

#define SERVO_GIMBAL_YAW_MID_POSE 180
#define SERVO_GIMBAL_YAW_UP_LIMIT 360
#define SERVO_GIMBAL_YAW_LOW_LIMIT 0

#define SERVO_GIMBAL_PITCH_MID_POSE 198
#define SERVO_GIMBAL_PITCH_UP_LIMIT 260
#define SERVO_GIMBAL_PITCH_LOW_LIMIT 140

#define SERVO_STEER_MID_POSE 198
#define SERVO_STEER_UP_LIMIT 275
#define SERVO_STEER_LOW_LIMIT 121

#define INPUT_DEVICE_LOW_LIMIT 0
#define INPUT_DEVICE_UP_LIMIT 1024


class Servo_IO
{
private:
    
    HCPCA9685 servoController = HCPCA9685(L2C_SERVO_DRIVER_ADR);

public:
    Servo_IO(/* args */);
    ~Servo_IO();

    void initServos();
    bool isServoControllerConnected(Stream &stream, byte I2C_Addr);

    void moveServo(uint8_t servoNum, int direction);
    void moveServo(uint8_t servoNum, int input, int inputMinMax[2]);

    void resetServoPosition(uint8_t servoNum);
    void testServo(byte servoNum, uint8_t minMax[2], int speed);
    void mapServoControlData(int data, int servoNum);
    void outputServoOutData();

private:

    int servoCurrentPositions[3] = {0,0,0};

    int mappedServoOutData[3] = {0,0,0};

    int servoGimbalYaw_currentPos  = 0; 
    int servoGimbalYawDir = 1;
    int servoGimbalYawIsIdle = 0;
};

Servo_IO::Servo_IO(/* args */){}
Servo_IO::~Servo_IO(){}


bool Servo_IO::isServoControllerConnected(Stream &stream, byte L2C_Addr)
{   
    Wire.begin();
    Wire.beginTransmission(L2C_Addr);
    uint8_t error = Wire.endTransmission();
    //Wire.end();

    if (error == 0)
        return true;
    else
        return false;
    return false;
}

void Servo_IO::initServos()
{   
    /* Initialise the library and set it to 'servo mode' */ 
    servoController.Init(SERVO_MODE);
    /* Wake the device up */
    servoController.Sleep(false);
    servoController.Servo(SERVO_GIMBAL_YAW_PIN, SERVO_GIMBAL_YAW_MID_POSE);
    servoController.Servo(SERVO_GIMBAL_PITCH_PIN, SERVO_GIMBAL_PITCH_MID_POSE);
    servoController.Servo(SERVO_STEER_PIN, SERVO_STEER_MID_POSE);

    servoCurrentPositions[0] = SERVO_GIMBAL_YAW_MID_POSE;
    servoCurrentPositions[1] = SERVO_GIMBAL_PITCH_MID_POSE;
    servoCurrentPositions[2] = SERVO_STEER_MID_POSE;
    

}

void Servo_IO::resetServoPosition(uint8_t servoNum)
{
    switch (servoNum)
    {
    case 0:
        servoController.Servo(SERVO_GIMBAL_YAW_PIN, SERVO_GIMBAL_YAW_MID_POSE);
        servoCurrentPositions[0] = SERVO_GIMBAL_YAW_MID_POSE;
        break;
    case 1:
        servoController.Servo(SERVO_GIMBAL_PITCH_PIN, SERVO_GIMBAL_PITCH_MID_POSE);
        servoCurrentPositions[1] = SERVO_GIMBAL_PITCH_MID_POSE;
        break;
    case 2:
        servoController.Servo(SERVO_STEER_PIN, SERVO_STEER_MID_POSE);
        servoCurrentPositions[2] = SERVO_STEER_MID_POSE;

        break;
    }

}

void Servo_IO::moveServo(uint8_t servoNum, int direction)
{
    switch (servoNum)
    {
        case 0:
            servoCurrentPositions[0] += 1*direction;
            if( servoCurrentPositions[0] <= SERVO_GIMBAL_YAW_UP_LIMIT && 
                servoCurrentPositions[0] >= SERVO_GIMBAL_YAW_LOW_LIMIT)
            {
                servoController.Servo(SERVO_GIMBAL_YAW_PIN,servoCurrentPositions[0]);

            }
            else if(servoCurrentPositions[0] < SERVO_GIMBAL_YAW_LOW_LIMIT)
            {   
                servoCurrentPositions[0] = SERVO_GIMBAL_YAW_LOW_LIMIT;  
                servoController.Servo(SERVO_GIMBAL_YAW_PIN,servoCurrentPositions[0]);  

            }
            else if(servoCurrentPositions[0] > SERVO_GIMBAL_YAW_UP_LIMIT)
            {   
                servoCurrentPositions[0] = SERVO_GIMBAL_YAW_UP_LIMIT;  
                servoController.Servo(SERVO_GIMBAL_YAW_PIN,servoCurrentPositions[0]);  
            }
            break;
        case 1:
            servoCurrentPositions[1] += 1*direction;
            if( servoCurrentPositions[1] <= SERVO_GIMBAL_PITCH_UP_LIMIT && 
                servoCurrentPositions[1] >= SERVO_GIMBAL_PITCH_LOW_LIMIT)
            {
                servoController.Servo(SERVO_GIMBAL_PITCH_PIN,servoCurrentPositions[1]);

            }
            else if(servoCurrentPositions[1] < SERVO_GIMBAL_PITCH_LOW_LIMIT)
            {   
                servoCurrentPositions[1] = SERVO_GIMBAL_PITCH_LOW_LIMIT;  
                servoController.Servo(SERVO_GIMBAL_PITCH_PIN,servoCurrentPositions[1]);  

            }
            else if(servoCurrentPositions[1] > SERVO_GIMBAL_PITCH_UP_LIMIT)
            {   
                servoCurrentPositions[1] = SERVO_GIMBAL_PITCH_UP_LIMIT;  
                servoController.Servo(SERVO_GIMBAL_PITCH_PIN,servoCurrentPositions[1]);  
            }
            break;
        case 2:
            servoCurrentPositions[2] += 1*direction;
            if( servoCurrentPositions[2] <= SERVO_STEER_UP_LIMIT && 
                servoCurrentPositions[2] >= SERVO_STEER_LOW_LIMIT)
            {
                servoController.Servo(SERVO_STEER_PIN,servoCurrentPositions[2]);

            }
            else if(servoCurrentPositions[2] < SERVO_STEER_LOW_LIMIT)
            {   
                servoCurrentPositions[2] = SERVO_STEER_LOW_LIMIT;  
                servoController.Servo(SERVO_STEER_PIN,servoCurrentPositions[2]);  

            }
            else if(servoCurrentPositions[2] > SERVO_STEER_UP_LIMIT)
            {   
                servoCurrentPositions[2] = SERVO_STEER_UP_LIMIT;  
                servoController.Servo(SERVO_STEER_PIN,servoCurrentPositions[2]);  
            }
            break;
    }
}

void Servo_IO::moveServo(uint8_t servoNum, int input, int inputMinMax[2])
{
    if(servoNum == 2)
    {
        servoCurrentPositions[2] = map( input,
                                        inputMinMax[0],
                                        inputMinMax[1],
                                        SERVO_STEER_LOW_LIMIT,
                                        SERVO_STEER_UP_LIMIT); 
        servoController.Servo(SERVO_STEER_PIN, servoCurrentPositions[2]);
    }
 
}

void Servo_IO::mapServoControlData(int data, int servoNum)
{
    switch (servoNum)
    {
    case 0:
        mappedServoOutData[0] = map(data, INPUT_DEVICE_LOW_LIMIT, INPUT_DEVICE_UP_LIMIT, SERVO_GIMBAL_YAW_LOW_LIMIT, SERVO_GIMBAL_YAW_UP_LIMIT);
        break;
    case 1:
        mappedServoOutData[1] = map(data, INPUT_DEVICE_LOW_LIMIT, INPUT_DEVICE_UP_LIMIT, SERVO_GIMBAL_PITCH_LOW_LIMIT, SERVO_GIMBAL_PITCH_UP_LIMIT);
        break;
    case 2:
        mappedServoOutData[2] = map(data, INPUT_DEVICE_LOW_LIMIT, INPUT_DEVICE_UP_LIMIT, SERVO_STEER_LOW_LIMIT, SERVO_STEER_UP_LIMIT);
        break;
    default:
        break;
    }

}


// needs debug!
void Servo_IO::testServo(byte servoNum, uint8_t minMax[2], int speed)
{   
    for (uint8_t i =  minMax[0]; i < minMax[1]; i++)
    {   
        servoController.Servo(0, i);
        delay(speed);
    }

    for (uint8_t i = minMax[1]; i >= minMax[0]; i--)
    {
        servoController.Servo(0, i);
        delay(speed);
    }
    

}


#include <Dependencies.h>

#define SERIAL_BAUD 9600
#define L2C_SERVO_DRIVER_ADR 0x40

const char* PS4_MAC_ADRESS = "30:c6:f7:2f:ef:a2";

PS4_IO ps4Controller = PS4_IO();
Servo_IO servoController = Servo_IO();
DCMotor_IO dcMotorController = DCMotor_IO();
ROS_IO rosController = ROS_IO();


//////////////////////////////////////////////////////////////////////////////////////

elapsedMillis getPS4DataTimer;
const uint8_t getPS4DataTimerDelay = 10;

elapsedMillis servoGimbalYawTimer;
const uint8_t servoGimbalYawTimerDelay = 5;

elapsedMillis servoGimbalPitchTimer;
const uint8_t servoGimbalPitchTimerDelay = 10;

elapsedMillis servoSteerTimer;
const uint8_t servoSteerTimerDelay = 2;

elapsedMillis dcMotorTimer;
const uint8_t dcMotorTimerDelay = 10;

//////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////


void initServoController();
void initPS4Controller();
void initSerial(unsigned long baud);

void ps4GetRawThumbStickValues();
void ps4ServosControl();

//////////////////////////////////////////////////////////////////////////////////////

bool isDebug = 1;
bool isPS4THumbStickValuesDebug = 0;

bool isPS4Controller = 1;
bool isServo = 1;
bool isDCMotor = 1;

int PS4ControllerState = 0;
int ServoControllerState = 0;


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void setup()
{

    initSerial(SERIAL_BAUD);
    
    Serial.println("\n\n");
    Serial.println("[ XRC ESP32 CONTROLLER DEBUG ]");
    Serial.println("____________________________________________________________\n\n");

    if(isPS4Controller)
        initPS4Controller();
    if(isServo)
        initServoController();
    if(isDCMotor)
        dcMotorController.initDCMotor();

    delay(250);

}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void loop()
{   

    if(ps4Controller.isConnected() && PS4ControllerState == 0)
    {   
        if(ps4Controller.isTouchPadPressed())
        {
            if(isDebug)
            {
                Serial.print("[PS4 Controller] ... running [Battery ");
                Serial.print(ps4Controller.getBatteryState());
                Serial.println("0%]\n");
            }
            PS4ControllerState = 1;
        }        
    }

    if(PS4ControllerState == 1)
    {
        ps4GetRawThumbStickValues();
    }

    if(ServoControllerState == 1 && PS4ControllerState == 1)
    {   
        ps4ServosControl();

        if(dcMotorTimer > dcMotorTimerDelay)
        {
            //if(!ps4Controller.isR2Pressed())
           // {  
                dcMotorController.runDCMotor(   PS4_THUMBSTICK_THRESH,
                                                ps4Controller.getThumbStickLeftValuesY(), 
                                                PS4_THUMBSTICK_LEFTY_MINMAX_LIMITS);
           // }

            dcMotorTimer = 0;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void initServoController()
{
    
    if(servoController.isServoControllerConnected(Serial, L2C_SERVO_DRIVER_ADR))
    {    
        if(isDebug)
            Serial.println("[Servo Controller] ... running\n");
        servoController.initServos();
        ServoControllerState = 1;
    }
    else
    {   
        if(isDebug)
            Serial.println("[Servo Controller] ...  CONNECTION FAIL\n");
    }
}

void initSerial(unsigned long baud)
{
    Serial.begin(baud);
}

void initPS4Controller()
{
    ps4Controller.initPS4(PS4_MAC_ADRESS);
}

void ps4GetRawThumbStickValues()
{
    
        if(getPS4DataTimer > getPS4DataTimerDelay)
        {
            ps4Controller.getThumbStickValues(0);
            ps4Controller.getThumbStickValues(1);

            if(isPS4THumbStickValuesDebug)
            {
                ps4Controller.outputThumbStickRawValues(Serial,0);
                ps4Controller.outputThumbStickRawValues(Serial,1);
            }
            getPS4DataTimer = 0;
        }
}

void ps4ServosControl()
{
    if(ps4Controller.isPS4ButtonPressed())
        {
            servoController.resetServoPosition(0);
            servoController.resetServoPosition(1);
        }
        if(servoGimbalYawTimer > servoGimbalYawTimerDelay)
        {
            if(ps4Controller.isThumbStickMovedLeft(0) && ps4Controller.isR2Pressed())
            {
                servoController.moveServo(0, 1);
            }
            if(ps4Controller.isThumbStickMovedRight(0) && ps4Controller.isR2Pressed())
            {
                servoController.moveServo(0, -1);
            }
            servoGimbalYawTimer = 0;
        }
        if(servoGimbalPitchTimer > servoGimbalPitchTimerDelay)
        {
            if(ps4Controller.isThumbStickMovedUp(1) && ps4Controller.isR2Pressed())
            {
                servoController.moveServo(1, -1);
            }
            if(ps4Controller.isThumbStickMovedDown(1) && ps4Controller.isR2Pressed())
            {
                servoController.moveServo(1, 1);
            }
            servoGimbalPitchTimer = 0;
        }
        if(servoSteerTimer > servoSteerTimerDelay)
        { 
            if(!ps4Controller.isR2Pressed())
            {  
                servoController.moveServo(2,ps4Controller.getThumbStickRightValuesX(), 
                                            PS4_THUMBSTICK_RIGHTX_MINMAX_LIMITS);
            }
            servoSteerTimer = 0;
        }

}




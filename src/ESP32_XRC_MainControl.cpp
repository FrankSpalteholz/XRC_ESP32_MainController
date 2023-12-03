#include <Dependencies.h>

#define SERIAL_BAUD 9600
#define SERIAL2_BAUD 115200
#define L2C_SERVO_DRIVER_ADR 0x40

#define RXD2 16
#define TXD2 17

const char* PS4_MAC_ADRESS = "30:c6:f7:2f:ef:a2";

PS4_IO ps4Controller = PS4_IO();
Servo_IO servoController = Servo_IO();
DCMotor_IO dcMotorController = DCMotor_IO();
ROS_IO rosController = ROS_IO();
CCom uartRemote = CCom();
Lcd_IO lcdController = Lcd_IO();

//////////////////////////////////////////////////////////////////////////////////////

// CHECK SPEED!!!! Especially if Yaw and Steer are fast enough
elapsedMillis getRemoteDataTimer;
const uint8_t getRemoteDataTimerDelay = 10;

elapsedMillis drawOnDisplayDataTimer;
const uint8_t drawOnDisplayDataTimerDelay = 10;

elapsedMillis getPS4DataTimer;
const uint8_t getPS4DataTimerDelay = 10;

elapsedMillis sendPS4DataTimer;
const uint8_t sendPS4DataTimerDelay = 10;

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
void initSerial(unsigned long baud, bool isRemote);

void ps4GetRawThumbStickValues();
void ps4ServosControl();
void ps4SetLED(bool controllerState);

//////////////////////////////////////////////////////////////////////////////////////

bool isDebug = 1;
bool isPS4THumbStickValuesDebug = 0;

bool PS4ControllerMode = 0;
bool RemoteControllerMode = 1;

bool isServo = 0;
bool isDCMotor = 1;
bool isLCD = 1;

int PS4ControllerState = 0;
int RemoteControllerState = 0;
int ServoControllerState = 0;


//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////

void setup()
{

    initSerial(SERIAL_BAUD, RemoteControllerMode);
    
    Serial.println("\n\n");
    Serial.println("[ XRC ESP32 CONTROLLER DEBUG ]");
    Serial.println("____________________________________________________________\n\n");

    if(PS4ControllerMode)
    {
        initPS4Controller();
        if(isDebug)
         Serial.println("[Controller] ... PS4");
    }

    if(RemoteControllerMode)
    {   
        if(isDebug)
         Serial.println("[Controller] ... JETSON");
    }
    
    if(isServo)
        initServoController();
    
    if(isDCMotor)
        dcMotorController.initDCMotor();
    
    if(isLCD)
        lcdController.initDisplay();

    delay(500);

}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void loop()
{

//////////////////////////////////////////////////////////////////////////////////////

    

    if(PS4ControllerMode)
    {
        if(ps4Controller.isConnected() && PS4ControllerState == 0)
        {   
            ps4SetLED(false);
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
            ps4SetLED(true);

            if(dcMotorTimer > dcMotorTimerDelay)
            {
                dcMotorController.runDCMotor(   PS4_THUMBSTICK_THRESH,
                                                ps4Controller.getThumbStickLeftValuesY(), 
                                                PS4_THUMBSTICK_LEFTY_MINMAX_LIMITS);
                dcMotorTimer = 0;
            }
        }
    }

//////////////////////////////////////////////////////////////////////////////////////

    if(RemoteControllerMode)
    {
        if(getRemoteDataTimer > getRemoteDataTimerDelay)
        {         
            uartRemote.reveiceDataSerial(Serial2);
            if(uartRemote.getIsConnected() && uartRemote.getIsNewData())
            {
                uartRemote.parseData();
                if(isDebug)
                    uartRemote.logData("[Remote DataIN] ... ");
            }
            else
            {
                uartRemote.resetDataIN(0);
                uartRemote.resetDataIN(1);
                uartRemote.resetDataIN(2);
                uartRemote.resetDataIN(3);

                // if(isDebug)
                //     uartRemote.logData("[Remote DataIN] ... ");
            }

            getRemoteDataTimer = 0;
        }
    }

    if(isLCD)
    {
        if(drawOnDisplayDataTimer > drawOnDisplayDataTimerDelay)
        {   
            if(RemoteControllerMode)
            {   
                int data[4]; 
                for (int i = 0; i < DATA_IN_COUNT; i++)
                    data[i] = uartRemote.getDataIN(i);
                lcdController.debugOutputDisplay(60, "JETSON", data);
            }
            
            if(PS4ControllerMode)
            {   
                int data[4]; 
                for (int i = 0; i < DATA_IN_COUNT; i++)
                    data[i] = uartRemote.getDataIN(i);  // TODO IMPLEMENT PS4 DATA!!!!!
                lcdController.debugOutputDisplay(60, "PS4", data);
            }

            
            drawOnDisplayDataTimer = 0;
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

void initSerial(unsigned long baud, bool isRemote)
{
    Serial.begin(baud);

    if(isRemote)
        Serial2.begin(SERIAL2_BAUD, SERIAL_8N1, RXD2, TXD2);
}

//////////////////////////////////////////////////////////////////////////////////////


void ps4SetLED(bool controllerState)
{
    if (sendPS4DataTimer > sendPS4DataTimerDelay)
    {
        if(!controllerState)
        {
            ps4Controller.setRGB(255,0,0);
        }
        else
        {
            ps4Controller.setRGB(0,150,255);
        }
        
        sendPS4DataTimer = 0;
    }
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



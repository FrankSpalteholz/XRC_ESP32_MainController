// #include <Dependencies.h>

// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////

// #define STICK_MAX_VALUE 127
// #define MOTOR_MAX_VALUE 125
// #define MOTOR_LEAN_MAX_VALUE 35

// elapsedMillis getPS4DataTimer;
// const uint8_t getPS4DataTimerDelay = 50;

// typedef struct struct_PS4Data {

//     int stickLeftX;
//     int stickLeftY;
//     int stickRightX;
//     int stickRightY;

//     int R2;
//     int L2;

//     bool ButtonCrossPressed;
//     bool ButtonSquarePressed;
//     bool ButtonTrianglePressed;
//     bool ButtonCirclePressed;

//     bool ButtonUpPressed;
//     bool ButtonDownPressed;

// } struct_PS4Data;

// // Create a struct_message 
// struct_PS4Data PS4Data;

// uint8_t stickThreshold = 13;

// int motorOutData[MOTOR_DATA_OUT_COUNT] = {}; // 4 tupples ... one tupple per motor(speed, direction)
// int platformOutData[PLATFORM_DATA_OUT_COUNT] = {}; 

// CCom cComMotors = CCom(MOTOR_DATA_OUT_COUNT);
// CCom cComPlatform = CCom(PLATFORM_DATA_OUT_COUNT);


// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////

// void initPS4Controller();
// void initPS4Data();
// void initOutData(uint8_t dataCount, int dataOut[]);

// void getPS4Data();

// void processDriveMotorStates(uint8_t thresh);
// void processPlatformStates(uint8_t thresh);

// void setMotorState(int sendArray[], uint8_t thresh, uint8_t motorNum, uint8_t speed, int direction);

// void outputAllControllerInputs();
// void logOutData(const char *logHeader, int dataCount, int dataIn[]);


// //////////////////////////////////////////////////////////////////////////////////////

// void setup() {

//     Serial.begin(9600);
//     Serial2.begin(9600, SERIAL_8N1, SERIAL2_RX, SERIAL2_TX);

//     initPS4Controller();
//     initPS4Data();
//     initOutData(MOTOR_DATA_OUT_COUNT, motorOutData);
//     initOutData(PLATFORM_DATA_OUT_COUNT, platformOutData);
// }

// //////////////////////////////////////////////////////////////////////////////////////

// void loop() {
  
//   if(getPS4DataTimer > getPS4DataTimerDelay)
//   {
    
//     getPS4Data();

//     processDriveMotorStates(stickThreshold);
//     processPlatformStates(stickThreshold);

//     //logOutData("[MotorOutData] ", MOTOR_DATA_OUT_COUNT, motorOutData);
//     //logOutData("[PlatformOutData] ", PLATFORM_DATA_OUT_COUNT, platformOutData);

//     cComMotors.sendDataUART(Serial, MOTOR_DATA_OUT_COUNT, motorOutData);
//     cComPlatform.sendDataUART(Serial2, PLATFORM_DATA_OUT_COUNT, platformOutData);

//     //outputAllControllerInputs();
    
//     getPS4DataTimer = 0;
    
//   }

// }

// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////

// void processDriveMotorStates(uint8_t thresh)
// {
//     // State Stop
//     if(   PS4Data.stickLeftX < thresh && PS4Data.stickLeftX > (-thresh) && 
//           PS4Data.stickLeftY < thresh && PS4Data.stickLeftY > (-thresh) &&
//           PS4Data.stickRightX < thresh && PS4Data.stickRightX > (-thresh) &&
//           PS4Data.stickRightY < thresh && PS4Data.stickRightY > (-thresh))
//     {
//           //Serial.println("[Motor State STOP]");
//           for (int i = 0; i < DRIVING_MOTORS_COUNT; i++)
//           {
//             setMotorState(motorOutData, thresh, i, 0, 0);
//           }
//     }
    
//     // TODO add rightStick values!!!
//     //State Forward 
//     if(PS4Data.stickLeftY > thresh)
//     {     
//           // //Serial.println("[Motor State BACKWARDS]");
//           // for (int i = 0; i < DRIVING_MOTORS_COUNT; i++)
//           // {
//           //   setMotorState(motorOutData, thresh, i, abs(PS4Data.stickLeftY), 1);
//           // }
//           //PS4.setRumble(10,200);
//           //Serial.println("[Motor State FORWARD]");
//           if(PS4Data.stickRightX < -thresh)
//           {
//               setMotorState(motorOutData, thresh, 0, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), 1);
//               setMotorState(motorOutData, thresh, 1, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), 1);
//               setMotorState(motorOutData, thresh, 2, PS4Data.stickLeftY, 1);
//               setMotorState(motorOutData, thresh, 3, PS4Data.stickLeftY, 1);  
//           }
//           else if(PS4Data.stickRightX > thresh)
//           {
//               setMotorState(motorOutData, thresh, 0, PS4Data.stickLeftY, 1);  
//               setMotorState(motorOutData, thresh, 1, PS4Data.stickLeftY, 1);
//               setMotorState(motorOutData, thresh, 2, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), 1);
//               setMotorState(motorOutData, thresh, 3, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), 1);
//           }
//           else
//           {
//               for (int i = 0; i < DRIVING_MOTORS_COUNT; i++)
//               {
//                 setMotorState(motorOutData, thresh, i, abs(PS4Data.stickLeftY), 1);
//               }
//           }
//     }

//     //State Backwards
//     if(   PS4Data.stickLeftY < (-thresh))
//     {
//           //Serial.println("[Motor State BACKWARDS]");
          
          
          
//           if(PS4Data.stickRightX > thresh)
//           {
//               setMotorState(motorOutData, thresh, 0, PS4Data.stickLeftY, -1);
//               setMotorState(motorOutData, thresh, 1, PS4Data.stickLeftY, -1);  
//               setMotorState(motorOutData, thresh, 2, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), -1);
//               setMotorState(motorOutData, thresh, 3, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), -1);
//           }
//           else if(PS4Data.stickRightX < -thresh)
//           {
//               setMotorState(motorOutData, thresh, 0, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), -1);
//               setMotorState(motorOutData, thresh, 1, PS4Data.stickLeftY - map(abs(PS4Data.stickRightX),thresh, STICK_MAX_VALUE, 0, MOTOR_LEAN_MAX_VALUE), -1);
//               setMotorState(motorOutData, thresh, 2, PS4Data.stickLeftY, -1);
//               setMotorState(motorOutData, thresh, 3, PS4Data.stickLeftY, -1);  
//           }  
//           else
//           {
//               for (int i = 0; i < DRIVING_MOTORS_COUNT; i++)
//               {
//                 setMotorState(motorOutData, thresh, i, abs(PS4Data.stickLeftY), -1);
//               }
//           }
//     }
// }

// void processPlatformStates(uint8_t thresh)
// {
//     // State Stop
//     if(   PS4Data.R2 < thresh && PS4Data.L2 < thresh)
//     {
//       setMotorState(platformOutData, thresh, 0, 0, 0);
//     }

//     // State Up
//     if(   PS4Data.R2 > thresh && PS4Data.L2 < thresh)
//     {
//       //Serial.println("[Motor State UP]");
//       setMotorState(platformOutData, thresh, 0, abs(PS4Data.R2), 1);
//     }

//     // State Up
//     if(   PS4Data.L2 > thresh && PS4Data.R2 < thresh)
//     {
//       //Serial.println("[Motor State DOWN]");
//       setMotorState(platformOutData, thresh, 0, abs(PS4Data.L2), -1);
//     }
// }

// void setMotorState(int sendArray[], uint8_t thresh, uint8_t motorNum, uint8_t speed, int direction)
// {

//   sendArray[motorNum * 2] = map(speed, 0, STICK_MAX_VALUE, 0, MOTOR_MAX_VALUE);
//   sendArray[motorNum * 2 + 1] = direction;

// }

// void getPS4Data()
// {

//     PS4Data.stickLeftX = PS4.LStickX();
//     PS4Data.stickLeftY = PS4.LStickY();
//     PS4Data.stickRightX = PS4.RStickX();
//     PS4Data.stickRightY = PS4.RStickY();

//     PS4Data.R2 = PS4.R2Value();
//     PS4Data.L2 = PS4.L2Value();

//     PS4Data.ButtonUpPressed = PS4.Up();
//     PS4Data.ButtonDownPressed = PS4.Down();

//     PS4Data.ButtonCrossPressed = PS4.Cross();
//     PS4Data.ButtonCirclePressed = PS4.Circle();
//     PS4Data.ButtonSquarePressed = PS4.Square();
//     PS4Data.ButtonTrianglePressed = PS4.Triangle();

// }

// void initOutData(uint8_t dataCount, int dataOut[])
// {
//   for (int i = 0; i < dataCount; i++)
//   {
//     dataOut[i] = 0;
//   }
// }

// void initPS4Data()
// {

//   PS4Data.stickLeftX = 0;
//   PS4Data.stickLeftY = 0;
//   PS4Data.stickRightX = 0;
//   PS4Data.stickRightY = 0;

//   PS4Data.ButtonUpPressed = 0;
//   PS4Data.ButtonDownPressed = 0;

//   PS4Data.ButtonCrossPressed = 0;
//   PS4Data.ButtonCirclePressed = 0;
//   PS4Data.ButtonSquarePressed = 0;
//   PS4Data.ButtonTrianglePressed = 0;

// }

// void setMotorOutData()
// {

//   PS4Data.stickLeftX = 0;
//   PS4Data.stickLeftY = 0;
//   PS4Data.stickRightX = 0;
//   PS4Data.stickRightY = 0;

//   PS4Data.ButtonUpPressed = 0;
//   PS4Data.ButtonDownPressed = 0;

//   PS4Data.ButtonCrossPressed = 0;
//   PS4Data.ButtonCirclePressed = 0;
//   PS4Data.ButtonSquarePressed = 0;
//   PS4Data.ButtonTrianglePressed = 0;

// }

// void initPS4Controller()
// {
//   PS4.begin(BLUETOOTH_MAC_ADDRESS);
//   //PS4.setLed(0, 186, 246);
//   PS4.setLed(254, 254, 254);
// }

// void logOutData(const char *logHeader, int dataCount, int dataIn[])
// {
//     Serial.print(logHeader);
//     for(int i = 0; i < dataCount-1; i++)
//     {
//       Serial.print(dataIn[i]);
//       Serial.print(":");
//     }
//     Serial.print(dataIn[dataCount-1]);

//     Serial.println();
// }

// void outputAllControllerInputs()
// {
//   if (PS4.isConnected()) {
//   if (PS4.Right()) Serial.println("Right Button");
//   if (PS4.Down()) Serial.println("Down Button");
//   if (PS4.Up()) Serial.println("Up Button");
//   if (PS4.Left()) Serial.println("Left Button");

//   if (PS4.Square()) Serial.println("Square Button");
//   if (PS4.Cross()) Serial.println("Cross Button");
//   if (PS4.Circle()) Serial.println("Circle Button");
//   if (PS4.Triangle()) Serial.println("Triangle Button");

//   if (PS4.UpRight()) Serial.println("Up Right");
//   if (PS4.DownRight()) Serial.println("Down Right");
//   if (PS4.UpLeft()) Serial.println("Up Left");
//   if (PS4.DownLeft()) Serial.println("Down Left");

//   if (PS4.L1()) Serial.println("L1 Button");
//   if (PS4.R1()) Serial.println("R1 Button");

//   if (PS4.Share()) Serial.println("Share Button");
//   if (PS4.Options()) Serial.println("Options Button");
//   if (PS4.L3()) Serial.println("L3 Button");
//   if (PS4.R3()) Serial.println("R3 Button");

//   if (PS4.PSButton()) Serial.println("PS Button");
//   if (PS4.Touchpad()) Serial.println("Touch Pad Button");

//   if (PS4.L2()) {
//     Serial.printf("L2 button at %d\n", PS4.L2Value());
//   }
//   if (PS4.R2()) {
//     Serial.printf("R2 button at %d\n", PS4.R2Value());
//   }

//   if (PS4.LStickX()) {
//     Serial.printf("Left Stick x at %d\n", PS4.LStickX());
//   }
//   if (PS4.LStickY()) {
//     Serial.printf("Left Stick y at %d\n", PS4.LStickY());
//   }
//   if (PS4.RStickX()) {
//     Serial.printf("Right Stick x at %d\n", PS4.RStickX());
//   }
//   if (PS4.RStickY()) {
//     Serial.printf("Right Stick y at %d\n", PS4.RStickY());
//   }

//   if (PS4.Charging()) Serial.println("The controller is charging");
//   if (PS4.Audio()) Serial.println("The controller has headphones attached");
//   if (PS4.Mic()) Serial.println("The controller has a mic attached");

//   Serial.printf("Battery Level : %d\n", PS4.Battery());

//   Serial.println();
//   // This delay is to make the output more human readable
//   // Remove it when you're not trying to see the output
//   delay(250);
// }

// }
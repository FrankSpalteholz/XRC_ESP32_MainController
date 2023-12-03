// #include <Dependencies.h>

// #define POTI_1 34
// #define POTI_2 35

// #define INPUT_DEVICE_LOW_LIMIT 0
// #define INPUT_DEVICE_UP_LIMIT 4095

// #define SERVO_GIMBAL_YAW 0
// #define SERVO_GIMBAL_PITCH 1
// #define SERVO_STEER 2

// #define SERVO_GIMBAL_YAW_MID_POSE 128
// #define SERVO_GIMBAL_YAW_UP_LIMIT 270
// #define SERVO_GIMBAL_YAW_LOW_LIMIT 0

// #define SERVO_GIMBAL_PITCH_MID_POSE 198
// #define SERVO_GIMBAL_PITCH_UP_LIMIT 270
// #define SERVO_GIMBAL_PITCH_LOW_LIMIT 0

// #define SERVO_STEER_UP_LIMIT 100
// #define SERVO_STEER_LOW_LIMIT 0

// #define AVERAGE_LENGTH  10

// #define  I2CAdd 0x40

// HCPCA9685 HCPCA9685(I2CAdd);

// unsigned int averagePotiValues[2] = {0,0};
// int mappedServoOutData[3] = {0,0,0};

// void getPotiValues(int pin1, int pin2);
// void outputAveragePotiValues();
// void readAndAveragePotiData(int pin1, int pin2);
// void mapServoControlData(int data, int servoNum);
// void outputServoOutData();

// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////

// void setup()
// {
//     Serial.begin(9600);

//     /* Initialise the library and set it to 'servo mode' */ 
//     HCPCA9685.Init(SERVO_MODE);

//     /* Wake the device up */
//     HCPCA9685.Sleep(false);

//     HCPCA9685.Servo(SERVO_GIMBAL_YAW, SERVO_GIMBAL_YAW_MID_POSE);
//     HCPCA9685.Servo(SERVO_GIMBAL_PITCH, SERVO_GIMBAL_PITCH_MID_POSE);

// }


// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////


// void loop()
// {

//     getPotiValues(POTI_1, POTI_2);
//     //outputAveragePotiValues();    
    
//     mapServoControlData(averagePotiValues[0], SERVO_GIMBAL_YAW);
//     mapServoControlData(averagePotiValues[1], SERVO_GIMBAL_PITCH);
//     outputServoOutData();
    
//     HCPCA9685.Servo(SERVO_GIMBAL_YAW, mappedServoOutData[0]);
//     HCPCA9685.Servo(SERVO_GIMBAL_PITCH, mappedServoOutData[1]);
    
//     //delay(10);
    
//     // for(Pos = 10; Pos < 450; Pos++)
//     // {
//     //     /* This function sets the servos position. It takes two parameters, 
//     //     * the first is the servo to control, and the second is the servo 
//     //     * position. */
//     //     HCPCA9685.Servo(0, Pos);
//     //     delay(10);
//     // }
    
//     //   for(Pos = 450; Pos >= 10; Pos--)
//     //   {
//     //     HCPCA9685.Servo(0, Pos);
//     //     delay(10);
//     //   }



// }

// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////

// void mapServoControlData(int data, int servoNum)
// {
//     switch (servoNum)
//     {
//     case 0:
//         mappedServoOutData[0] = map(data, INPUT_DEVICE_LOW_LIMIT, INPUT_DEVICE_UP_LIMIT, SERVO_GIMBAL_YAW_LOW_LIMIT, SERVO_GIMBAL_YAW_UP_LIMIT);
//         break;
//     case 1:
//         mappedServoOutData[1] = map(data, INPUT_DEVICE_LOW_LIMIT, INPUT_DEVICE_UP_LIMIT, SERVO_GIMBAL_PITCH_LOW_LIMIT, SERVO_GIMBAL_PITCH_UP_LIMIT);
//         break;
//     case 2:
//         mappedServoOutData[2] = map(data, INPUT_DEVICE_LOW_LIMIT, INPUT_DEVICE_UP_LIMIT, SERVO_STEER_LOW_LIMIT, SERVO_STEER_UP_LIMIT);
//         break;
//     default:
//         break;
//     }

// }

// void readAndAveragePotiData(int pin1, int pin2)
// {
//   unsigned int sval1 = 0;
//   unsigned int sval2 = 0;
//   for (int i = 0; i < AVERAGE_LENGTH; i++){
//     sval1 += analogRead(pin1);
//     sval2 += analogRead(pin2);
//     delay (10);
//   }
//   averagePotiValues[0] =  sval1 / AVERAGE_LENGTH;
//   averagePotiValues[1] =  sval2 / AVERAGE_LENGTH;
// }

// void outputAveragePotiValues()
// {
//     Serial.print(averagePotiValues[0]);
//     Serial.print(":");
//     Serial.println(averagePotiValues[1]);
// }

// void outputServoOutData()
// {
//     Serial.print(mappedServoOutData[0]);
//     Serial.print(":");
//     Serial.print(mappedServoOutData[1]);
//     Serial.print(":");
//     Serial.println(averagePotiValues[2]);
// }



// void getPotiValues(int pin1, int pin2)
// {   
//     readAndAveragePotiData(pin1, pin2);
// }

#define POTI_1 34
#define POTI_2 35


// float rawPotiValues[2] = {0, 0}; 
// unsigned int averagePotiValues[2] = {0,0};

// void readRawPotiValues(int pin1, int pin2);
// void getAveragePotiValues(int pin1, int pin2);
// void outputAveragePotiValues();
// void outputRawPotiValues();
// void readAndAveragePotiData(int pin1, int pin2);



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
//     Serial.println(mappedServoOutData[2]);
// }



// void getAveragePotiValues(int pin1, int pin2)
// {   
//     readAndAveragePotiData(pin1, pin2);
// }

// void readRawPotiValues(int pin1, int pin2)
// {
//     rawPotiValues[0] = (float)analogRead(pin1);
//     rawPotiValues[1] = (float)analogRead(pin2);
// }

// void outputRawPotiValues()
// {   
//     Serial.print(rawPotiValues[0]);
//     Serial.print(":");
//     Serial.println(rawPotiValues[1]);
// }
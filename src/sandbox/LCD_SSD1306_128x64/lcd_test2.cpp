// #include <Adafruit_GFX.h>
// #include <Adafruit_SH110X.h>
// #include <SPI.h>
// #include "Wire.h"
// #include "WiFi.h"
// #include <Arduino.h>
// #include <elapsedMillis.h>
// #include "Images/DGCLogo_BW.h"
// #include "Images/AvalonLogo.h"


// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define OLED_RESET -1   //   QT-PY / XIAO
// #define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

// #define I2C2_SDA 25
// #define I2C2_SCL 26

// elapsedMillis ledTimerSendON;
// elapsedMillis ledTimerSendOFF;
// const int ledTimerSendDelay = 50;


// TwoWire I2C_LCD = TwoWire(0);
// Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &I2C_LCD, OLED_RESET);

// int cursor[2] = {0,0};

// typedef struct struct_message {
//     int id; // must be unique for each sender board
//     int motor_mode;
//     int motor1_amp;
//     int motor2_amp;
//     int motor3_amp;
//     int motor4_amp;
//     int motor1_frq;
//     int motor2_frq;
//     int motor3_frq;
//     int motor4_frq;
// } struct_message;

// // Create a struct_message 
// struct_message dataOut;


// //////////////////////////////////////////////////////////////////////////////////////


// void initDisplay();
// void drawOnDisplay(int cursorPos[2], int offset, const char* label, const char* state);
// char *concatenateCharArrays(char array1[], char array2[],  char *concateArray);
// void debugOutputDisplay(int dataOffset);




// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////

// void setup()
// {
//     Serial.begin(9600);

//     I2C_LCD.begin(I2C2_SDA, I2C2_SCL, 400000);

//     initDisplay();

// }

// //////////////////////////////////////////////////////////////////////////////////////

// void loop()
// {

   
//     debugOutputDisplay(60);
//     delay(10);
// }

// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////


// char *concatenateCharArrays(char array1[], char array2[], char *concateArray)
// {
 
//   strcpy(concateArray, array1);
//   strcat(concateArray, ":");
//   strcat(concateArray, array2);

//   return concateArray;
// }

// void debugOutputDisplay(int dataOffset)
// {
//     char cstr[5];
//     char cstr2[5];
//     char concateStr[10];

//     itoa(dataOut.motor_mode, cstr, 10);
//     cursor[0] = 0;
//     cursor[1] = 0;
//     drawOnDisplay(cursor, dataOffset, "[Mode]", cstr);
    

//     itoa(dataOut.motor1_amp, cstr, 10);
//     itoa(dataOut.motor1_frq, cstr2, 10);
    
//     cursor[0] = 0;
//     cursor[1] = 15;
//     drawOnDisplay(cursor, dataOffset, "[M1 A/F]", concatenateCharArrays(cstr,cstr2,concateStr));
    
//     itoa(dataOut.motor2_amp, cstr, 10);
//     itoa(dataOut.motor2_frq, cstr2, 10);

//     cursor[0] = 0;
//     cursor[1] = 29;
//     drawOnDisplay(cursor, dataOffset, "[M2 A/F]",concatenateCharArrays(cstr,cstr2,concateStr));

//     itoa(dataOut.motor3_amp, cstr, 10);
//     itoa(dataOut.motor3_frq, cstr2, 10);
    
//     cursor[0] = 0;
//     cursor[1] = 43;
//     drawOnDisplay(cursor, dataOffset, "[M3 A/F]", concatenateCharArrays(cstr,cstr2,concateStr));

//     itoa(dataOut.motor4_amp, cstr, 10);
//     itoa(dataOut.motor4_frq, cstr2, 10);
    
//     cursor[0] = 0;
//     cursor[1] = 57;
//     drawOnDisplay(cursor, dataOffset, "[M4 A/F]", concatenateCharArrays(cstr,cstr2,concateStr));

//     display.display();
//     display.clearDisplay();

// }

// void drawOnDisplay(int cursorPos[2], int offset, const char* label, const char* state) {

//   display.setTextSize(1);
//   display.setTextColor(SH110X_WHITE);
//   display.setCursor(cursorPos[0], cursorPos[1]);
//   display.write(label);

//   display.setCursor(cursorPos[0] + offset, cursorPos[1]);
//   display.write(state);
  
//   //display.display();
 
// }



// void initDisplay()
// {

//     delay(250); // wait for the OLED to power up


//     display.begin(i2c_Address, true); // Address 0x3C default

//     display.display();
//     delay(1000);

//     // Clear the buffer.
//     display.clearDisplay();

//     // miniature bitmap display
//     display.drawBitmap(0, 0,  image_Avalon_Logo_BW, 128, 64, 1);
//     display.display();
//     delay(1000);

//     display.display();
//     display.clearDisplay();

// }


// void initSendStruct()
// {
//     dataOut.motor_mode = 0;
//     dataOut.motor1_amp = 0;
//     dataOut.motor2_amp = 0;
//     dataOut.motor3_amp = 0;
//     dataOut.motor4_amp = 0;
//     dataOut.motor1_frq = 0;
//     dataOut.motor2_frq = 0;
//     dataOut.motor3_frq = 0;
//     dataOut.motor4_frq = 0;
// }



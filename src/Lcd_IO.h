#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SPI.h>
#include "Wire.h"

#include "Images/XRookieLogo.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define I2C2_SDA 25
#define I2C2_SCL 26


class Lcd_IO
{
    private:

        TwoWire I2C_LCD = TwoWire(0);
        Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &I2C_LCD, OLED_RESET);

        int cursor[2] = {0,0};

        char *concatenateCharArrays(char array1[], char array2[],  char *concateArray);
        void drawOnDisplay(int cursorPos[2], int offset, const char* label, const char* state);
        void initDataStruct();

    public:
        Lcd_IO(/* args */);
        ~Lcd_IO();

        void initDisplay();
        void debugOutputDisplay(int dataOffset, const char* mode, int data[4]);
};


Lcd_IO::Lcd_IO(/* args */) {}
Lcd_IO::~Lcd_IO() {}

void Lcd_IO::initDisplay()
{
    I2C_LCD.begin(I2C2_SDA, I2C2_SCL, 400000); 

    display.begin(i2c_Address, true); // Address 0x3C default

    display.display();
    delay(1000);

    // // Clear the buffer.
    // display.clearDisplay();

    // // miniature bitmap display
    // display.drawBitmap(0, 0,  image_XRookie_Logo, 128, 64, 1);
    // display.display();
    // delay(1000);

    // display.display();
    // display.clearDisplay();
}

char *Lcd_IO::concatenateCharArrays(char array1[], char array2[], char *concateArray)
{
 
  strcpy(concateArray, array1);
  strcat(concateArray, ":");
  strcat(concateArray, array2);

  return concateArray;
}

void Lcd_IO::debugOutputDisplay(int dataOffset, const char* mode, int data[4] )
{   
    char cstr[5];
    cursor[0] = 0;
    cursor[1] = 0;
    drawOnDisplay(cursor, dataOffset, "[Control]", mode);
    
    itoa(data[0], cstr, 10);
    cursor[0] = 0;
    cursor[1] = 15;
    drawOnDisplay(cursor, dataOffset, "[M1]", cstr);
    
    itoa(data[1], cstr, 10);
    cursor[0] = 0;
    cursor[1] = 29;
    drawOnDisplay(cursor, dataOffset, "[M2]",cstr);

    itoa(data[2], cstr, 10);
    cursor[0] = 0;
    cursor[1] = 43;
    drawOnDisplay(cursor, dataOffset, "[M3]", cstr);

    itoa(data[3], cstr, 10);
    cursor[0] = 0;
    cursor[1] = 57;
    drawOnDisplay(cursor, dataOffset, "[M4]", cstr);

    display.display();
    display.clearDisplay();

}

void Lcd_IO::drawOnDisplay(int cursorPos[2], int offset, const char* label, const char* state) {

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(cursorPos[0], cursorPos[1]);
  display.write(label);

  display.setCursor(cursorPos[0] + offset, cursorPos[1]);
  display.write(state);
  
  //display.display();
 
}
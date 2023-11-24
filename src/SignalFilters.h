#include <Arduino.h>

class SignalFilters
{
  private:
    
    float lp_coeff[3] = {0.969, 0.0155, 0.0155};
    float lp_bw_coeff_a[2] = {1.95558189, -0.95654717};
    float lp_bw_coeff_b[3] = {0.00024132, 0.00048264, 0.00024132};

    float lp_bw_x[3] = {0, 0, 0};
    float lp_bw_y[3] = {0, 0, 0};

    float lp_y_new = 0;
    float lp_y_last = 0;
    float lp_x_new = 0;
    float lp_x_last = 0;


  public:

    float lowPass(float signal);         // standart low pass
    float lowPass_butterworth(float signal);   // low pass second order Butterworth
    SignalFilters(/* args */);
    ~SignalFilters();
};

//////////////////////////////////////////////////////////////////////////////////////

SignalFilters::SignalFilters(/* args */){}

SignalFilters::~SignalFilters(){}


float SignalFilters::lowPass(float signal)
{
  float lp_y_new = lp_coeff[0]*lp_y_last + lp_coeff[1]*signal + lp_coeff[2]*lp_y_last;
  lp_x_last = signal;
  lp_y_last = lp_y_new;

  return lp_y_new;
}

float SignalFilters::lowPass_butterworth(float signal)
{
  float outSignal;
  lp_bw_x[0] = signal;

  lp_bw_y[0] =  lp_bw_coeff_a[0]*lp_bw_y[1] + lp_bw_coeff_a[1]*lp_bw_y[2] +
          lp_bw_coeff_b[0]*lp_bw_x[0] + lp_bw_coeff_b[1]*lp_bw_x[1] + lp_bw_coeff_b[2]*lp_bw_x[2];

  outSignal = lp_bw_y[0];
  delay(1); // Wait 1ms
  
  for(int i = 1; i >= 0; i--){
    lp_bw_x[i+1] = lp_bw_x[i]; // store xi
    lp_bw_y[i+1] = lp_bw_y[i]; // store yi
  }

  return outSignal;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////

// // This file shows an example implementation of a 
// // second order low-pass Butterworth filter on an Arduino. 
// // Note that there are many possible improvements to this code.

// float x[] = {0,0,0};
// float y[] = {0,0,0};
// int k = 0;

// void setup() {
//   Serial.begin(115200);
// }

// void loop() {
//   // Test signal
//   float t = micros()/1.0e6;
//   x[0] = sin(2*PI*2*t) + 0.5*sin(2*PI*25*t);

//   // Compute the filtered signal
//   // (second order Butterworth example)
//   float b[] = {0.00024132, 0.00048264, 0.00024132};
//   float a[] = {1.95558189, -0.95654717};
//   y[0] = a[0]*y[1] + a[1]*y[2] +
//                b[0]*x[0] + b[1]*x[1] + b[2]*x[2];

//   if(k % 3 ==0)
//   {
//     // This extra conditional statement is here to reduce
//     // the number of times the data is sent through the serial port
//     // because sending data through the serial port
//     // messes with the sampling frequency
    
//     // For the serial monitor
//     Serial.print(2*x[0]);
//     Serial.print(" ");
//     Serial.println(2*y[0]);
//   }

//   delay(1); // Wait 1ms
//   for(int i = 1; i >= 0; i--){
//     x[i+1] = x[i]; // store xi
//     y[i+1] = y[i]; // store yi
//   }
  
//   k = k+1;
// }



// // This file shows an example implementation of a low-pass filter on an Arduino.
// // Note that there are many potential improvements to this code.

// float xn1 = 0;
// float yn1 = 0;
// int k = 0;

// void setup() {
//   Serial.begin(115200);
// }

// void loop() {
//   // Test signal
//   float t = micros()/1.0e6;
//   float xn = sin(2*PI*2*t) + 0.2*sin(2*PI*50*t);

//   // Compute the filtered signal
//   float yn = 0.969*yn1 + 0.0155*xn + 0.0155*xn1;

//   delay(1);
//   xn1 = xn;
//   yn1 = yn;

//   if(k % 3 == 0){
//     // This extra conditional statement is here to reduce
//     // the number of times the data is sent through the serial port
//     // because sending data through the serial port
//     // messes with the sampling frequency
  
//     // Output
//     Serial.print(2*xn);
//     Serial.print(" ");
//     Serial.println(2*yn);
//   }
//   k = k+1;
// }

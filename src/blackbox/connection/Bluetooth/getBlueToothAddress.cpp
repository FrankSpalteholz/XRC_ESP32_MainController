//  #include <Dependencies.h>


// // char str[100];

// // void setup() 
// // {
// //   Serial.begin(9600);
// //   //PS4.begin();
// //   const uint8_t* address = esp_bt_dev_get_address();
 
// //   sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x", address[0],address[1],address[2],address[3],address[4],address[5]);
// //   Serial.println(str);
// // }
 
// // void loop() 
// // {
// //    //Serial.println(str);
// // }

// // // //98:cd:ac:61:5b:ca

// // // //30:c6:f7:2f:ef:a2

// // //30:c6:f7:31:0e:96

// #include "esp_bt_main.h"
// #include "esp_bt_device.h"
 
// bool initBluetooth()
// {
//   if (!btStart()) {
//     Serial.println("Failed to initialize controller");
//     return false;
//   }
 
//   if (esp_bluedroid_init() != ESP_OK) {
//     Serial.println("Failed to initialize bluedroid");
//     return false;
//   }
 
//   if (esp_bluedroid_enable() != ESP_OK) {
//     Serial.println("Failed to enable bluedroid");
//     return false;
//   }
 
// }
 
// void printDeviceAddress() {
 
//   const uint8_t* point = esp_bt_dev_get_address();
 
//   for (int i = 0; i < 6; i++) {
 
//     char str[3];
 
//     sprintf(str, "%02X", (int)point[i]);
//     Serial.print(str);
 
//     if (i < 5){
//       Serial.print(":");
//     }
 
//   }
//   Serial.println();
// }
 
// void setup() {
//   Serial.begin(9600);
 
//   initBluetooth();
//   printDeviceAddress();
// }
 
// void loop() {

//      printDeviceAddress();
// }
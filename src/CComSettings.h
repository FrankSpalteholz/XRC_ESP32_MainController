//#define SERIAL2_RX 16
//#define SERIAL2_TX 17

#define ARTEFACT_RELAY_PIN1 17 
#define ARTEFACT_RELAY_PIN2 18 
#define ARTEFACT_RELAY_PIN3 22 

#define MOTOR_DATA_OUT_COUNT 8
#define PLATFORM_DATA_OUT_COUNT 2

#define DATA_IN_COUNT 8

#define DRIVING_MOTORS_COUNT 2 // we are using 4 but sending only 2 values seperating left / right
#define SEND_DELAY 50

#define START_MARKER    '<'
#define END_MARKER      '>'

const char* SEPERATOR = ":";

//const char* BLUETOOTH_MAC_ADDRESS = "30:c6:f7:30:de:42";

const char* BLUETOOTH_MAC_ADDRESS = "30:c6:f7:31:0e:96";

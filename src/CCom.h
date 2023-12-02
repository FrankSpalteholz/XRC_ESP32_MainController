#include <Arduino.h>
#include <Wire.h>

#define MOTOR_DATA_OUT_COUNT 4
#define DATA_IN_COUNT 4

#define SEND_DELAY 50

#define START_MARKER    '<'
#define END_MARKER      '>'
const char* SEPERATOR = ":";

class CCom
{
    private:
    
        boolean _newData = false;
        const byte _numChars = 30;
        char _receivedChars[30];
        char _tempChars[30];
        int _dataCount = DATA_IN_COUNT;
        int dataIN[DATA_IN_COUNT] = {0,0,0,0};

        bool isConnected = false;

    public:
        
        CCom();
        ~CCom();
        
        void parseData();
        void reveiceDataSerial(Stream &stream);

        inline void resetDataIN(uint8_t index) {dataIN[index] = 0;};
        inline int getDataIN(uint8_t index) {return dataIN[index];};

        void logData(const char *logHeader);
        inline bool getIsNewData() {return _newData;}
        inline bool getIsConnected() {return isConnected;};
};

CCom::CCom(){}
CCom::~CCom(){}

void CCom::reveiceDataSerial(Stream &stream)
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char rc;
    int index = 0;

    if(stream.available())
        isConnected = true;
    else
        isConnected = false;

    while (stream.available()) 
    {
        rc = stream.read();
        //Serial.print(rc);
        
        if (recvInProgress == true) 
        {
            if (rc != END_MARKER) 
            {
                _receivedChars[ndx] = rc;
                index++;
                ndx++;
                if (ndx >= _numChars) 
                {
                    ndx = _numChars - 1;
                }
            }
            else 
            {
                _receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                _newData = true;
            }
        }
        else if (rc == START_MARKER) 
        {
            recvInProgress = true;
        }
    } 
}

void CCom::parseData()
{
    strcpy(_tempChars, _receivedChars);

    char * strtokIndx;                              // this is used by strtok() as an index
    strtokIndx = strtok(_tempChars, SEPERATOR);     // get the first part - the string
    dataIN[0] = atoi(strtokIndx);

    for(int i = 1; i < DATA_IN_COUNT; i++)
    {
        strtokIndx = strtok(NULL, SEPERATOR);
        dataIN[i] = atoi(strtokIndx);
    }
    _newData = false;
}


void CCom::logData(const char* logHeader)
{
    Serial.print(logHeader);
    for(int i = 0; i < DATA_IN_COUNT; i++)
    {
      Serial.print(dataIN[i]);
      Serial.print(":");
    }

    Serial.println();
}


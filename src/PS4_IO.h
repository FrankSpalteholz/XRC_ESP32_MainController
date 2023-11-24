#include <PS4Controller.h>

#define PS4_THUMBSTICK_THRESH 45

int PS4_THUMBSTICK_LEFTX_MINMAX_LIMITS[2] = {-128, 127};
int PS4_THUMBSTICK_LEFTY_MINMAX_LIMITS[2] = {-128, 127};

int PS4_THUMBSTICK_RIGHTX_MINMAX_LIMITS[2] = {-128, 127};
int PS4_THUMBSTICK_RIGHTY_MINMAX_LIMITS[2] = {-128, 127};

int PS4_THUMBSTICK_LEFTX_MAP_LIMITS[2] = {-50, 50};
int PS4_THUMBSTICK_LEFTY_MAP_LIMITS[2] = {-50, 50};

int PS4_THUMBSTICK_RIGHTX_MAP_LIMITS[2] = {-50, 50};
int PS4_THUMBSTICK_RIGHTY_MAP_LIMITS[2] = {-50, 50};


class PS4_IO
{
    public:
    
        PS4_IO();
        ~PS4_IO();
        
        void initPS4(const char* macAdress);

        bool isConnected(){return PS4.isConnected();};
        bool isTouchPadPressed(){return PS4.Touchpad();};
        bool isPS4ButtonPressed(){return PS4.PSButton();};
        bool isR2Pressed(){return PS4.R2();};
        uint8_t getBatteryState(){return PS4.Battery();};


        void setThumbStickMidThresh(int stickMidThresh){thumbStickMidTresh = stickMidThresh;};
        void setThumbStickMapLimits(uint8_t thumbStickNum, int mapLimitsX[2],  int mapLimitsY[2]); // num 0 = left right = 1; limits 0 = x 1 = y
        void setThumbStickMinMaxLimits(uint8_t thumbStickNum, int minMaxLimitsX[2], int minMaxLimitsY[2]); // num 0 = left right = 1; limits 0 = x 1 = y

        void getThumbStickValues(uint8_t thumbStickNum);

        int getThumbStickLeftValuesX(){return thumbStickRawLeft[0];}; 
        int getThumbStickLeftValuesY(){return thumbStickRawLeft[1];}; 
        int getThumbStickRightValuesX(){return thumbStickRawRight[0];}; 
        int getThumbStickRightValuesY(){return thumbStickRawRight[1];};

        bool isThumbStickIdle(uint8_t thumbStickNum);
        bool isThumbStickMovedLeft(uint8_t thumbStickNum);
        bool isThumbStickMovedRight(uint8_t thumbStickNum);
        bool isThumbStickMovedUp(uint8_t thumbStickNum);
        bool isThumbStickMovedDown(uint8_t thumbStickNum);

        void outputThumbStickRawValues(Stream &stream, int thumbStickNum);
        void outputThumbStickMappedValues(Stream &stream, int thumbStickNum);
        void outputThumbStickMoveStates(Stream &stream, int thumbStickNum);

        void mapThumbStickValues(uint8_t thumbStickNum);

    private:

    int thumbStickMidTresh = 0;
    
    int thumbStickRawLeft[2] = {0,0}; // index 0/1 = x/y
    int thumbStickRawRight[2] = {0,0};
    
    int thumbStickLeftXMapLimits[2] = {0,0};
    int thumbStickLeftYMapLimits[2] = {0,0};
    int thumbStickRightXMapLimits[2] = {0,0};
    int thumbStickRightYMapLimits[2] = {0,0};


    int thumbStickLeftXMaxMin[2] = {0,0};
    int thumbStickLeftYMaxMin[2] = {0,0};  
    int thumbStickRightXMaxMin[2] = {0,0};
    int thumbStickRightYMaxMin[2] = {0,0};

    int thumbStickMappedLeft[2] = {0,0};
    int thumbStickMappedRight[2] = {0,0};

};

PS4_IO::PS4_IO()
{
}

PS4_IO::~PS4_IO(){}

void PS4_IO::initPS4(const char* macAdress)
{

    setThumbStickMidThresh(PS4_THUMBSTICK_THRESH);

    setThumbStickMinMaxLimits(0, PS4_THUMBSTICK_LEFTX_MINMAX_LIMITS, PS4_THUMBSTICK_LEFTY_MINMAX_LIMITS);
    setThumbStickMinMaxLimits(1, PS4_THUMBSTICK_RIGHTX_MINMAX_LIMITS, PS4_THUMBSTICK_RIGHTY_MINMAX_LIMITS);

    setThumbStickMapLimits(0, PS4_THUMBSTICK_LEFTX_MAP_LIMITS, PS4_THUMBSTICK_LEFTY_MAP_LIMITS);
    setThumbStickMapLimits(1, PS4_THUMBSTICK_RIGHTX_MAP_LIMITS, PS4_THUMBSTICK_RIGHTY_MAP_LIMITS);
    
    PS4.begin(macAdress);

}

inline void PS4_IO::setThumbStickMapLimits(uint8_t thumbStickNum, int mapLimitsX[2], int mapLimitsY[2])
{
    switch (thumbStickNum)
    {
    case 0:
           thumbStickLeftXMapLimits[0] = mapLimitsX[0]; 
           thumbStickLeftXMapLimits[1] = mapLimitsX[1]; 
           thumbStickLeftYMapLimits[0] = mapLimitsY[0]; 
           thumbStickLeftYMapLimits[1] = mapLimitsY[1]; 
        break;
    case 1:
           thumbStickRightXMapLimits[0] = mapLimitsX[0]; 
           thumbStickRightXMapLimits[1] = mapLimitsX[1];
           thumbStickRightYMapLimits[0] = mapLimitsY[0]; 
           thumbStickRightYMapLimits[1] = mapLimitsY[1]; 
        break;
    }
}

inline void PS4_IO::setThumbStickMinMaxLimits(uint8_t thumbStickNum, int minMaxLimitsX[2], int minMaxLimitsY[2])
{
    switch (thumbStickNum)
    {
    case 0:
           thumbStickLeftXMaxMin[0] = minMaxLimitsX[0]; 
           thumbStickLeftXMaxMin[1] = minMaxLimitsX[1]; 
           thumbStickLeftYMaxMin[2] = minMaxLimitsY[0]; 
           thumbStickLeftYMaxMin[3] = minMaxLimitsY[1]; 
        break;
    case 1:
           thumbStickRightXMaxMin[0] = minMaxLimitsX[0]; 
           thumbStickRightXMaxMin[1] = minMaxLimitsX[1];
           thumbStickRightYMaxMin[2] = minMaxLimitsY[0]; 
           thumbStickRightYMaxMin[3] = minMaxLimitsY[1]; 
        break;
    }
}

bool PS4_IO::isThumbStickIdle(uint8_t thumbStickNum)
{
    switch (thumbStickNum)      
    {
    case 0:
        if((thumbStickRawLeft[0] < thumbStickMidTresh && thumbStickRawLeft[0] > -thumbStickMidTresh) &&
            (thumbStickRawLeft[1] < thumbStickMidTresh && thumbStickRawLeft[1] > -thumbStickMidTresh))
            return true;
        else
            return false;
        break;    
    case 1:
        if((thumbStickRawRight[0] < thumbStickMidTresh && thumbStickRawRight[0] > -thumbStickMidTresh) &&
            (thumbStickRawRight[1] < thumbStickMidTresh && thumbStickRawRight[1] > -thumbStickMidTresh))
            return true;
        else
            return false;
        break;
    }
    return false;
}

bool PS4_IO::isThumbStickMovedLeft(uint8_t thumbStickNum)
{   
    switch (thumbStickNum)      
    {
        case 0:
            if(thumbStickRawLeft[0] < -thumbStickMidTresh)
                return true;
            else
                return false;
            break;
        case 1:
            if(thumbStickRawRight[0] < -thumbStickMidTresh)
                return true;
            else
                return false;
            break;
    }
    return false;
}

bool PS4_IO::isThumbStickMovedRight(uint8_t thumbStickNum)
{
    switch (thumbStickNum)      
    {
        case 0:
            if(thumbStickRawLeft[0] > thumbStickMidTresh)
                return true;
            else
                return false;
            break;
        case 1:
            if(thumbStickRawRight[0] > thumbStickMidTresh)
                return true;
            else
                return false;
            break;
    }
    return false;
}

bool PS4_IO::isThumbStickMovedUp(uint8_t thumbStickNum)
{
    switch (thumbStickNum)      
    {
        case 0:
            if(thumbStickRawLeft[1] > thumbStickMidTresh)
                return true;
            else
                return false;
            break;
        case 1:
            if(thumbStickRawRight[1] > thumbStickMidTresh)
                return true;
            else
                return false;
            break;
    }
    return false;
}

bool PS4_IO::isThumbStickMovedDown(uint8_t thumbStickNum)
{
    switch (thumbStickNum)      
    {
        case 0:
            if(thumbStickRawLeft[1] < -thumbStickMidTresh)
                return true;
            else
                return false;
            break;
        case 1:
            if(thumbStickRawRight[1] < -thumbStickMidTresh)
                return true;
            else
                return false;
            break;
    }
    return false;
}

void PS4_IO::getThumbStickValues(uint8_t thumbStickNum)
{   
    switch (thumbStickNum)
    {
    case 0:
        thumbStickRawLeft[0] = PS4.LStickX();
        thumbStickRawLeft[1] = PS4.LStickY();    
        break;
    case 1:
        thumbStickRawRight[0] = PS4.RStickX();
        thumbStickRawRight[1] = PS4.RStickY();    
        break;
    }
}

void PS4_IO::mapThumbStickValues(uint8_t thumbStickNum)
{   
    switch (thumbStickNum)
    {
    case 0:
        thumbStickMappedLeft[0] = map(  thumbStickRawLeft[0], 
                                        thumbStickLeftXMaxMin[0],
                                        thumbStickLeftXMaxMin[1],
                                        thumbStickLeftXMapLimits[0],
                                        thumbStickLeftXMapLimits[1]);  
        thumbStickMappedLeft[1] = map(  thumbStickRawLeft[1], 
                                        thumbStickLeftYMaxMin[0],
                                        thumbStickLeftYMaxMin[1],
                                        thumbStickLeftYMapLimits[0],
                                        thumbStickLeftYMapLimits[1]);                
        break;
    case 1:
        thumbStickMappedRight[0] = map( thumbStickRawRight[0], 
                                        thumbStickRightXMaxMin[0],
                                        thumbStickRightXMaxMin[1],
                                        thumbStickRightXMapLimits[0],
                                        thumbStickRightXMapLimits[1]);  
        thumbStickMappedRight[1] = map( thumbStickRawRight[1], 
                                        thumbStickRightYMaxMin[0],
                                        thumbStickRightYMaxMin[1],
                                        thumbStickRightYMapLimits[0],
                                        thumbStickRightYMapLimits[1]);
        break;
    }

}

void PS4_IO::outputThumbStickRawValues(Stream &stream, int thumbStickNum)
{   
    switch (thumbStickNum)
    {
    case 0:
        stream.print("[ThumbStickRawData]");
        stream.print(" [Lx] ");stream.print(thumbStickRawLeft[0]);
        stream.print(" [Ly] ");stream.println(thumbStickRawLeft[1]);    
        break;
    case 1:
        stream.print("[ThumbStickRawData] ");
        stream.print(" [Rx] ");stream.print(thumbStickRawRight[0]);
        stream.print(" [Ry] ");stream.println(thumbStickRawRight[1]);    
        break;
    default:
        break;
    }
}

void PS4_IO::outputThumbStickMappedValues(Stream &stream, int thumbStickNum)
{   
    switch (thumbStickNum)
    {
    case 0:
        stream.println("[ThumbStickMappedData]");
        stream.print(" [Lx] ");stream.print(thumbStickMappedLeft[0]);
        stream.print(" [Ly] ");stream.println(thumbStickMappedLeft[1]);    
        break;
    
    case 1:
        stream.println("[ThumbStickMappedData]");
        stream.print(" [Rx] ");stream.print(thumbStickMappedRight[0]);
        stream.print(" [Ry] ");stream.println(thumbStickMappedRight[1]);    
        break;
    default:
        break;
    }
}

void PS4_IO::outputThumbStickMoveStates(Stream &stream, int thumbStickNum)
{
    if(!isThumbStickIdle(0))
        {
            if(isThumbStickMovedLeft(0))
                Serial.println("Thumbstick left moved left");
            if(isThumbStickMovedRight(0))
                Serial.println("Thumbstick left moved right");
            if(isThumbStickMovedUp(0))
                Serial.println("Thumbstick left moved up");
            if(isThumbStickMovedDown(0))
                Serial.println("Thumbstick left moved down");
        }
        if(!isThumbStickIdle(1))
        {
            if(isThumbStickMovedLeft(1))
                Serial.println("Thumbstick right moved left");
            if(isThumbStickMovedRight(1))
                Serial.println("Thumbstick right moved right");
            if(isThumbStickMovedUp(1))
                Serial.println("Thumbstick right moved up");
            if(isThumbStickMovedDown(1))
                Serial.println("Thumbstick right moved down");
        }
}


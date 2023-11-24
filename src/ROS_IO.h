#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

class ROS_IO
{
    private:
    
        
        char hello[13] = "hello world!";

    public:
        ROS_IO(/* args */);
        ~ROS_IO();

        void initRos();
        void helloWorld();

};

ROS_IO::ROS_IO(/* args */)
{
}

ROS_IO::~ROS_IO()
{
}

void ROS_IO::initRos()
{
    nh.initNode();
    
    nh.advertise(chatter);

}

void ROS_IO::helloWorld()
{
    str_msg.data = hello;
    chatter.publish( &str_msg );
    nh.spinOnce();
    delay(1000);

}
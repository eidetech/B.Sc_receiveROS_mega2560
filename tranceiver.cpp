#include <ros/ros.h>
#include "std_msgs/Int32.h"
#include "std_msgs/Float32MultiArray.h"
#include "sensor_msgs/Joy.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_ = n_.advertise<std_msgs::Float32MultiArray>("/ps4data", 1);

    //Topic you want to subscribe
    sub_ = n_.subscribe("/j0/joy", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const sensor_msgs::Joy& input)
  {
    std_msgs::Float32MultiArray output;
    output.data.resize(8);
    output.data[0] = input.axes[0];
    output.data[1] = input.axes[1];
    output.data[2] = input.axes[2];
    output.data[3] = input.axes[5];
    output.data[4] = input.buttons[0];
    output.data[5] = input.buttons[1];
    output.data[6] = input.buttons[2];
    output.data[7] = input.buttons[3];
    //.... do something with the input and generate the output...
    pub_.publish(output);
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "tranceiver");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish tranceiver;

  ros::spin();

  return 0;
}
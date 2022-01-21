/*
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

// Arduino – ROS headers
#include <ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Int32.h>


//Creating a Nodehandle object
ros::NodeHandle nh;

//sensor_msgs::Joy ps4Buttons;

// Creating a callback for the topic toggle_led, whenever a value come through this topic, this callback will execute
// The callback will toggle the state of LED which is on PIN 13

void messageCb( const std_msgs::Int32& ps4Buttons){
  if(ps4Buttons.data == 1)
  {
    digitalWrite(13, HIGH); // blink the led
  }else
  {
    digitalWrite(13, LOW);
  }
}

//Creating a subscriber with a name toggle_led, and its callback
ros::Subscriber<std_msgs::Int32> sub("/buttons", &messageCb);

//Setting PIN 13 as output and initializing ROS node and subscriber object
void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}

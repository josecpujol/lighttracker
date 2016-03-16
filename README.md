# Lighttracker
## Description
The main objective is to have fun with arduino by building a device that follows the brightest source of light present. It consists of a software part that implements a control loop feedback algorithm and a hardware part, with two servo motors and photoresistors.

There are two independent servo motors that are controlled by the feedback obtained by two different inputs. These inputs are the result of a voltage divider with photoresistors.

## Hardware
The hardware consists of a structure where 4 photoresistors, forming two independent voltage dividers. They are mounted in a 4 face pyramid, so when the pyramid is facing the brightest source of light, we will obtain a (theoretically) perfect half voltage in both voltage dividers.

![alt tag] https://raw.githubusercontent.com/josecpujol/lighttracker/master/lighttracker.png

The voltage read points are connected to A0 and A1 in the arduino board

The two servo motors are mounted such as they control the pan and tilt of the pyramid 

## Software
The main loop consists of
* Read voltage
* Compute servo motor position update
* Update the servo position

This is done for the two servos independently.

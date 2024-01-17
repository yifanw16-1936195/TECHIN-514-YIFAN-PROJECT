# Product: PostureGuard - Smart Posture Monitoring System

## Description: A desk display device that uses a sensor device placed on a chair's backrest to monitor sitting posture. It alerts users through a display device with a needle when their posture deviates from an initially calibrated 'correct' position. The users will use the button on the display device to to set the correct position.

<img width="657" alt="image" src="https://github.com/yifanw16-1936195/TECHIN-514-YIFAN-PROJECT/assets/77317334/f4601b4f-678e-4b95-afb0-6faf6987ed20">

### Components:
- esp32 s3 xiao sensor * 2
- 3.7V Lipo Polymer Rechargeable Battery * 2
- Ultrasonic Sensor HC-SR04 * 1
- 5050 SMD RGB LED * 1
- X27 Stepper Motor
- KSMC6 Tactile Switches 6mm×6mm Top Push


# Sensor
## The sensor device
Attach ultrasonic sensors to the device to monitor the user-chair gap(calculation), triggering a display alert if the user leans too far forward or too close. 

### Components:
- esp32 s3 xiao sensor 
- Ultrasonic Sensors: Ultrasonic Sensor HC-SR04
- Battery

<img width="658" alt="image" src="https://github.com/yifanw16-1936195/TECHIN-514-YIFAN-PROJECT/assets/77317334/64149ef1-ed3f-4ad5-a1f8-320a2a90cfa8">

# Display
## The display device
When the user's posture is correct, the needle points to a specific 'Good' position, and the green LED is lit. As the user's posture begins to deviate, the needle moves away from this position, and the  RGB LED color changes (from green to yellow to red) based on the severity of the deviation.

### Component: 
- esp32 s3 xiao sensor
- RGB LED
- Tactile Tact Push Button
- Battery

<img width="656" alt="image" src="https://github.com/yifanw16-1936195/TECHIN-514-YIFAN-PROJECT/assets/77317334/a1699b53-0425-457c-a44a-84d80a15182f">

# System Diagram
<img width="656" alt="image" src="https://github.com/yifanw16-1936195/TECHIN-514-YIFAN-PROJECT/assets/77317334/7334913b-86d6-432f-b859-b5bcb75700b8">
<img width="658" alt="image" src="https://github.com/yifanw16-1936195/TECHIN-514-YIFAN-PROJECT/assets/77317334/95fad71a-0839-4794-abda-1c26311a89c8">


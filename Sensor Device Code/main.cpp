// #include <Arduino.h>

// // Define the Trigger and Echo pins of the HC-SR04 sensor
// const int trigPin = A1; // Corresponds to D1 on the board
// const int echoPin = A2; // Corresponds to D2 on the board

// // Define variables for the duration and the distance
// long duration;
// float distance;

// void setup() {
//   // Starts the serial communication
//   Serial.begin(9600);
//   // Defines the trigPin as an Output and the echoPin as an Input
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
// }

// void loop() {
//   // Clears the trigPin condition
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   // Reads the echoPin, returns the sound wave travel time in microseconds
//   duration = pulseIn(echoPin, HIGH);
//   // Calculating the distance
//   distance= duration*0.034/2; // Speed of sound wave divided by 2 (go and return)
//   // Prints the distance on the Serial Monitor
//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.println(" cm");
//   // Delay 1 second before the next measurement
//   delay(1000);
// }


// // Define the analog pin the sensor is connected to
// const int sensorPin = A3; 

// // Threshold value to detect pressure
// // This should be adjusted according to your specific sensor and desired sensitivity
// const int threshold = 2000;

// void setup() {
//   Serial.begin(115200); // Start the serial communication
//   pinMode(sensorPin, INPUT); // Initialize the sensorPin as an input
// }

// void loop() {
//   // Read the sensor value
//   double sensorValue = analogRead(sensorPin);
//   Serial.println(sensorValue);
  
//   // Check if the sensor value exceeds the threshold
//   if (sensorValue > threshold) {
//     // If the sensor value is above the threshold, it means pressure is detected
//     Serial.println("Detected someone sitting on it.");
//   } else {
//     // If the sensor value is below the threshold, it means no pressure is detected
//     Serial.println("No pressure detected.");
//   }
  
//   // Adding a small delay to avoid spamming the serial output
//   delay(1000);
// }
#include <Arduino.h>

// Define the Trigger and Echo pins of the HC-SR04 sensor
const int trigPin = A1; // Corresponds to D1 on the board
const int echoPin = A2; // Corresponds to D2 on the board

// Define the analog pin for the pressure sensor
const int sensorPin = A3; 

// Threshold value to detect pressure
const int pressureThreshold = 2000;

// Define variables for the duration and the distance
long duration;
float distance;

void setup() {
  // Starts the serial communication
  Serial.begin(115200);
  // Defines the trigPin as an Output and the echoPin as an Input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Initialize the sensorPin as an input for the pressure sensor
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and return)
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Read the pressure sensor value
  double sensorValue = analogRead(sensorPin);
  
  // Check if the sensor value exceeds the threshold
  if (sensorValue > pressureThreshold) {
    // If the sensor value is above the threshold, it means pressure is detected
    Serial.println("Detected someone sitting on it.");
  } else {
    // If the sensor value is below the threshold, it means no pressure is detected
    Serial.println("No pressure detected.");
  }
  
  // Adding a delay to avoid spamming the serial output
  delay(1000);
}

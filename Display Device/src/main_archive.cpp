// // #include <Wire.h>
// // #include <Adafruit_GFX.h>
// // #include <Adafruit_SSD1306.h>
// // #include <SwitecX25.h>
// #include <Arduino.h>
// #include <SwitecX25.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// #define STEPS 945 // Standard X25.168 ranges from 0 to 315 degrees, at 1/3 degree increments

// // Motor connected to D1, D2, D3, D4 (ESP32 GPIOs)
// const int motorPin1 = 1;
// const int motorPin2 = 2;
// const int motorPin3 = 3;
// const int motorPin4 = 4;
// SwitecX25 motor(STEPS, motorPin1, motorPin2, motorPin3, motorPin4);

// // Define the RGB LED pins
// const int ledPinR = 7; // Red LED pin connected to GPIO7
// const int ledPinG = 9; // Green LED pin connected to GPIO9
// const int ledPinB = 8; // Blue LED pin connected to GPIO8

// void setup() {
//   Serial.begin(115200);
//   while (!Serial); // Wait for Serial to be ready

//   pinMode(ledPinR, OUTPUT);
//   pinMode(ledPinG, OUTPUT);
//   pinMode(ledPinB, OUTPUT);
  
//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;);
//   }

//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(0,0);

//   motor.zero(); // Initialize the stepper motor
// }

// String messages[5] = {"good posture", "leaning forward", "leaning backward", "sitting at front", "sitting at back"};
// int currentMessageIndex = 0;
// unsigned long lastMessageChange = 0;
// const long messageInterval = 10000; // Change message every 10000 ms (10 seconds)

// void loop() {
//   unsigned long currentTime = millis();

//   // Change message every 10 seconds
//   if (currentTime - lastMessageChange >= messageInterval) {
//     currentMessageIndex = (currentMessageIndex + 1) % 5; // Cycle through messages
//     lastMessageChange = currentTime;

//     // Display current message on OLED
//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.println(messages[currentMessageIndex]);
//     display.setTextSize(2.5);
//     display.display();

//     // If the current message is not "good posture", activate LED and motor
//     if (currentMessageIndex != 0) {
//       // Example to light up LED with multiple colors
//       digitalWrite(ledPinR, HIGH);
//       delay(200);
//       digitalWrite(ledPinR, LOW);
//       digitalWrite(ledPinG, HIGH);
//       delay(200);
//       digitalWrite(ledPinG, LOW);
//       digitalWrite(ledPinB, HIGH);
//       delay(200);
//       digitalWrite(ledPinB, LOW);

//       // Activate stepper motor to make noise as a reminder
//       motor.setPosition(STEPS - 1); // Move motor to make noise
//       delay(500); // Short delay to allow motor to spin
//       motor.zero(); // Reset motor position
//     } else {
//       // If "good posture", ensure LED is off and motor is not moving
//       digitalWrite(ledPinR, LOW);
//       digitalWrite(ledPinG, LOW);
//       digitalWrite(ledPinB, LOW);
//       // Ensure motor is stopped or in default position
//       motor.zero();
//     }
//   }

//   motor.update(); // Continuously update motor position without waiting
// }



// #include <Arduino.h>
// #include <SwitecX25.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// #define STEPS 945 // Standard X25.168 ranges from 0 to 315 degrees, at 1/3 degree increments

// const int motorPin1 = 1; // Motor connected to D1, D2, D3, D4 (ESP32 GPIOs)
// const int motorPin2 = 2;
// const int motorPin3 = 3;
// const int motorPin4 = 4;
// SwitecX25 motor(STEPS, motorPin1, motorPin2, motorPin3, motorPin4);

// const int ledPinR = 7; // Define the RGB LED pins
// const int ledPinG = 9;
// const int ledPinB = 8;

// String messages[5] = {"good posture", "leaning forward", "leaning backward", "sitting at front", "sitting at back"};
// int currentMessageIndex = 0;
// unsigned long lastMessageChange = 0;
// const long messageInterval = 10000; // Change message every 10000 ms (10 seconds)

// void setup() {
//   Serial.begin(115200);
//   while (!Serial); // Wait for Serial to be ready

//   pinMode(ledPinR, OUTPUT);
//   pinMode(ledPinG, OUTPUT);
//   pinMode(ledPinB, OUTPUT);
  
//   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;); // Loop forever
//   }

//   display.clearDisplay();
//   display.setTextSize(2); // Increase text size for larger display messages
//   display.setTextColor(SSD1306_WHITE);

//   motor.zero(); // Initialize the stepper motor
// }

// void loop() {
//   unsigned long currentTime = millis();

//   if (currentTime - lastMessageChange >= messageInterval) {
//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.println(messages[currentMessageIndex]);
//     display.display();

//     if (currentMessageIndex != 0) {
//       // Light up LED with multiple colors
//       digitalWrite(ledPinR, HIGH);
//       delay(200);
//       digitalWrite(ledPinR, LOW);
//       digitalWrite(ledPinG, HIGH);
//       delay(200);
//       digitalWrite(ledPinG, LOW);
//       digitalWrite(ledPinB, HIGH);
//       delay(200);
//       digitalWrite(ledPinB, LOW);

//       // Rapidly move the stepper motor for a noticeable effect
//       motor.setPosition(STEPS / 4); // Move to a quarter of its total steps for a quick spin
//       delay(100); // A short delay to allow for quick response
//       motor.setPosition(0); // Immediately return to the starting position for the next cycle
//     } else {
//       // Deactivate LED when showing "good posture"
//       digitalWrite(ledPinR, LOW);
//       digitalWrite(ledPinG, LOW);
//       digitalWrite(ledPinB, LOW);
//       motor.zero(); // Ensure motor is reset to starting position
//     }
//     currentMessageIndex = (currentMessageIndex + 1) % 5; // Move to the next message
//     lastMessageChange = currentTime;
//   }

//   motor.update(); // Continuously update motor position
// }






// void loop() {
//   static int color = 0;
//   static unsigned long lastUpdateTime = 0; // Track the last update time
//   unsigned long currentTime = millis();

//   // Cycle through RGB colors more quickly
//   if (currentTime - lastUpdateTime >= 200) { // Change LED color every 200 milliseconds
//     digitalWrite(ledPinR, color != 0);
//     digitalWrite(ledPinG, color != 1);
//     digitalWrite(ledPinB, color != 2);
//     color = (color + 1) % 3;
//     lastUpdateTime = currentTime;
    
//     // Toggle the motor's target position each time we change the color
//     if (motor.currentStep == motor.targetStep) {
//       if (motor.targetStep == STEPS / 2) {
//         motor.setPosition(STEPS - 1);
//         Serial.println("Moving motor to max position...");
//       } else {
//         motor.setPosition(STEPS / 2);
//         Serial.println("Moving motor to middle position...");
//       }
//     }
//   }

//   motor.update(); // Continuously update motor position without waiting

//   // Update OLED display less frequently to maintain responsiveness
//   static unsigned long lastDisplayUpdate = 0;
//   if (currentTime - lastDisplayUpdate >= 1000) { // Update display every 1000 milliseconds
//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.println(F("Testing LED, OLED, Stepper"));
//     display.print(F("Motor Pos: "));
//     display.println(motor.currentStep);
//     display.print(F("LED Color: "));
//     display.println(color == 0 ? "Red" : color == 1 ? "Green" : "Blue");
//     display.display();
//     lastDisplayUpdate = currentTime;
//   }
// }


// #include <Arduino.h>
// #include <WiFi.h>
// #include <Firebase_ESP_Client.h>
// #include <addons/TokenHelper.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #include <SwitecX25.h>
// #include <ArduinoJson.h>

// // WiFi network settings
// #define WIFI_SSID "ChocoLuna"
// #define WIFI_PASSWORD "20190929"

// // Firebase credentials
// #define API_KEY "AIzaSyBv3VISnijb9p1HwbtUMjp8YBggXMDjT9I"
// #define DATABASE_URL "https://techin514-final-default-rtdb.firebaseio.com/"
// #define USER_EMAIL "wyf_testing@gmail.com"
// #define USER_PASSWORD "Wyf123456"


// // OLED display settings
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels
// #define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// // Define the Firebase objects
// FirebaseData db;
// FirebaseAuth auth;
// FirebaseConfig config;

// // Define the RGB LED pins
// const int ledPinR = 7;
// const int ledPinG = 9;
// const int ledPinB = 8;

// // Initialize the stepper motor pins
// const int motorPin1 = 1;
// const int motorPin2 = 2;
// const int motorPin3 = 3;
// const int motorPin4 = 4;

// // Motor settings
// #define STEPS 945 // Number of steps for SwitecX25 motor
// SwitecX25 motor(STEPS, motorPin1, motorPin2, motorPin3, motorPin4);

// String messages[5] = {"Good posture", "Leaning forward", "Leaning backward", "Sitting at front", "Sitting at back"};

// void setup() {
//   Serial.begin(115200);
//   // Wait for serial port to connect
//   while (!Serial);

//   // Initialize WiFi
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   Serial.print("Connecting to Wi-Fi");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print(".");
//     delay(300);
//   }
//   Serial.println("Connected with IP: ");
//   Serial.println(WiFi.localIP());

//   // Initialize Firebase
//   config.api_key = API_KEY;
//   config.database_url = DATABASE_URL;
//   config.token_status_callback = tokenStatusCallback;
//   auth.user.email = USER_EMAIL;
//   auth.user.password = USER_PASSWORD;
//   Firebase.begin(&config, &auth);
//   Firebase.reconnectWiFi(true);

//   // Initialize OLED display
//   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for (;;);
//   }
//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(0, 0);

//   // Initialize LED pins
//   pinMode(ledPinR, OUTPUT);
//   pinMode(ledPinG, OUTPUT);
//   pinMode(ledPinB, OUTPUT);

//   // Initialize motor
//   motor.zero();

//   Serial.println("Setup complete");
// }

// void loop() {
//   // Fetch the latest prediction from Firebase
//   FirebaseJson json;
//   FirebaseJsonData jsonData;
  
//   // Get the last prediction entry
//   auto result = db.child("predictions").orderByKey().limitToLast(1).get();

//   if (result.errorReason() == "") { // Check if the fetch was successful
//     FirebaseJson& json = result.value().as<FirebaseJson>(); // Get the JSON object
//     FirebaseJsonData jsonData;

//     // Assuming each child has 'prediction' and 'timestamp', we extract 'prediction'
//     if (json.get(jsonData, "/prediction")) { // Modify the path if necessary
//       int predictionIndex = jsonData.intValue; // Extracted prediction index
      
//       // Update display with the corresponding message
//       display.clearDisplay();
//       display.setCursor(0, 0);
//       display.println(messages[predictionIndex]);
//       display.display();

//       // Update LEDs based on prediction
//       digitalWrite(ledPinR, predictionIndex == 1 ? HIGH : LOW);
//       digitalWrite(ledPinG, predictionIndex == 2 ? HIGH : LOW);
//       digitalWrite(ledPinB, predictionIndex == 3 ? HIGH : LOW);

//       Serial.println(messages[predictionIndex]);
//     } else {
//       Serial.println("Failed to parse prediction");
//     }
//   } else {
//     Serial.println("Failed to fetch prediction");
//     Serial.println(result.errorReason());
//   }

//   delay(10000); // Check for new predictions every 10 seconds
// }
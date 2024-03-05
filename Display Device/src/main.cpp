#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SwitecX25.h>
#include <ArduinoJson.h>

// WiFi network settings
#define WIFI_SSID "xxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxx"

// Firebase credentials
#define API_KEY "xxxxxxxxxxxx"
#define DATABASE_URL "xxxxxxxxxxxx"
#define USER_EMAIL "xxxxxxxxxxxx"
#define USER_PASSWORD "xxxxxxxxxxxx"

// OLED display settings
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the Firebase objects
FirebaseData db;
FirebaseAuth auth;
FirebaseConfig config;

// Define the RGB LED pins
const int ledPinR = 7;
const int ledPinG = 9;
const int ledPinB = 8;

// Initialize the stepper motor pins
const int motorPin1 = 1;
const int motorPin2 = 2;
const int motorPin3 = 3;
const int motorPin4 = 4;

// Motor settings
#define STEPS 945 // Number of steps for SwitecX25 motor
SwitecX25 motor(STEPS, motorPin1, motorPin2, motorPin3, motorPin4);

String messages[5] = {"Good posture", "Leaning forward", "Leaning backward", "Sitting at front", "Sitting at back"};

int lastPredictionIndex = -1;

void setup() {
  Serial.begin(115200);
  // Wait for serial port to connect
  while (!Serial);

  // Initialize WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Initialize LED pins
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);

  // Initialize motor
  motor.zero();

  Serial.println("Setup complete");
}

void updateDisplay(int prediction) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  // Display the prediction or related message
  display.println(messages[prediction]);
  display.display();
}

void updateLEDs(int prediction) {
  // Turn off all LEDs initially
  digitalWrite(ledPinR, LOW);
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinB, LOW);

  // Only blink red LED if the prediction is not "Good posture"
  if (prediction != 0) {
    digitalWrite(ledPinB, HIGH);
    delay(200);
    digitalWrite(ledPinB, LOW);
  } else {
    // Blink green LED if the prediction indicates "Good posture"
    digitalWrite(ledPinG, HIGH);
    delay(200);
    digitalWrite(ledPinG, LOW);
  }
}

void updateMotor(int prediction) {
  // Move the motor only if the predictionIndex has changed
  if (prediction != lastPredictionIndex) {
    if (prediction == 0) {
      int motorPosition = (STEPS / 5) * prediction;
      motor.setPosition(motorPosition);
      delay(100);
    } else {
      motor.zero();
    }
    lastPredictionIndex = prediction;
  }
}

void loop() {
  // Path where the current latest prediction is stored
  String path = "predictions/current_prediction/prediction";
  db.clear(); // Clear previous data

  // Fetch the current latest prediction
  if (Firebase.RTDB.getString(&db, path)) {
    String predictionIndexStr = db.stringData();
    int predictionIndex = predictionIndexStr.toInt() - 1;

    // Display update based on the prediction
    updateDisplay(predictionIndex);
    updateLEDs(predictionIndex);
    updateMotor(predictionIndex);

    Serial.print("Latest prediction: ");
    Serial.println(messages[predictionIndex]);
  } else {
    Serial.println("Failed to fetch the latest prediction");
  }

  delay(1000); // Fetch every 1 second
}
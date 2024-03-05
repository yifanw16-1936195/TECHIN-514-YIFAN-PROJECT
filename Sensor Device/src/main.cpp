#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <time.h> // Include the time library

// WiFi network settings
#define WIFI_SSID "xxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxx"

// Firebase credentials
#define API_KEY "xxxxxxxxxxxx"
#define DATABASE_URL "xxxxxxxxxxxx"
#define USER_EMAIL "xxxxxxxxxxxx"
#define USER_PASSWORD "xxxxxxxxxxxx"

// Define the Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Sensor pins
const int trigPin = A1;
const int echoPin = A2;
const int sensorPin = A3;

// Define threshold
const int pressureThreshold = 2000;

// Variables for sensor data
long duration;
float distance;
double pressure;
bool isSitting;

// NTP server details
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -28800;
const int daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);

  // Initialize sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sensorPin, INPUT);

  // Initialize WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Initialize time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Wait for time to be set
  delay(1000); // Delay to allow time to be fetched
  while (!time(nullptr)){
    Serial.println("Fetching time...");
    delay(1000);
  }

  Serial.print("Firebase ready: ");
  Serial.println(Firebase.ready());
}

String formatTimestamp() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return String();
  }

  char strftime_buf[64];
  strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d_%H:%M", &timeinfo);
  return String(strftime_buf);
}

void loop() {

  // Sensor reading
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2
  pressure = analogRead(sensorPin);
  isSitting = pressure > pressureThreshold;

  String timestamp = formatTimestamp(); // Use the synchronized time
  if (timestamp.length() == 0) {
    Serial.println("Skipping Firebase update due to time error.");
    delay(1000); // Wait a bit before trying again
    return; // Skip this loop iteration if time couldn't be obtained
  }
  timestamp.replace('_', ' ');

  String path = String("/sensor_data/") + timestamp;
  FirebaseJson data;
  data.set("timestamp", timestamp); // Format for Firebase
  data.set("distance", distance);
  data.set("pressure", pressure);
  data.set("isSitting", isSitting);

  // Print the pressure
  Serial.print("Pressure: ");
  Serial.println(pressure);

  // Print the distance
  Serial.print("Distance: ");
  Serial.println(distance);

  // Print the isSitting
  Serial.print("isSitting: ");
  Serial.println(isSitting);

  // Print the timestamp
  Serial.print("Timestamp: ");
  Serial.println(timestamp);

  // Send data to Firebase
  if (Firebase.RTDB.setJSON(&fbdo, path.c_str(), &data)) {
    Serial.println("Data sent to Firebase");
  } else {
    Serial.println("Failed to send data to Firebase");
    Serial.println(fbdo.errorReason());
  }

  delay(1000); // Delay to avoid spamming Firebase
}
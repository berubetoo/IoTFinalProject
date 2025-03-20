#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Servo.h>

#define WIFI_SSID "P2410"
#define WIFI_PASSWORD "03052003"

#define FIREBASE_HOST "smartlocker-8413c-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "lAxt8cqIyeGL0KvrtBqWGdZtpgjTkiG0tIp0mbqw"

FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

#define SERVO_PIN D4

Servo servo;

void setup() {
  // Khởi tạo Serial
  Serial.begin(115200);

  // Kết nối WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Cấu hình Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);


  // Cài đặt servo
  servo.attach(SERVO_PIN);
  servo.write(0); // Ban đầu đóng cửa
}

void loop() {
  // Đọc trạng thái từ Firebase
  if (Firebase.getInt(firebaseData, "/doorStatus")) {
      if (firebaseData.dataType() == "int") {
        int doorStatus = firebaseData.intData();

        if (doorStatus == 1) {
          servo.write(90);
          Serial.println("OPEN");
        } else if (doorStatus == 0) {
          servo.write(0);
          Serial.println("CLOSE");
        }
      }
  } else {
    Serial.println("Can not read data from Firebase!");
  }
  delay(1000);
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "joo";      // Replace with your Wi-Fi network name (SSID)
const char *password = "#2021#Yy";  // Replace with your Wi-Fi network password

ESP8266WebServer server(80);

// Define pins and other variables for car control
const int leftMotorPin1 = 2;  
const int leftMotorPin2 = 3;  
const int rightMotorPin1 = 4; 
const int rightMotorPin2 = 5; 

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](){
    if (server.hasArg("command")) {
      String command = server.arg("command");
      Serial.print("Received command: ");
      Serial.println(command);

      if (command == "L") {

        digitalWrite(leftMotorPin1, HIGH); 
        digitalWrite(leftMotorPin2, LOW);

      } else if (command == "R") {
        
        digitalWrite(rightMotorPin1, HIGH); 
        digitalWrite(rightMotorPin2, LOW);
      
      } else if (command == "F") {
        
        digitalWrite(leftMotorPin1, HIGH); 
        digitalWrite(rightMotorPin1, HIGH); 
      
      } else if (command == "S") {
        
        digitalWrite(leftMotorPin1, LOW); 
        digitalWrite(leftMotorPin2, LOW);
        
      }
      server.send(200, "text/plain", "Command received");
    } else {
      server.send(400, "text/plain", "Invalid command");
    }
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

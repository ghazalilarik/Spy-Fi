#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>

// Wi-Fi repeater configuration
const char* primarySSID = "Primary_WiFi_SSID";       // Replace with your primary Wi-Fi network SSID
const char* primaryPassword = "Primary_WiFi_Password"; // Replace with your primary Wi-Fi network password
const char* repeaterSSID = "Repeater_SSID";           // Replace with the SSID for the repeater network
const char* repeaterPassword = "Repeater_Password";   // Replace with the password for the repeater network

// Variables for deauthentication detection
volatile int deauthPackets = 0;
const int alertThreshold = 5; // Threshold for triggering alert (number of deauth packets)
ESP8266WebServer server(80); // Web server on port 80
int ledPin = D4;              // LED pin for visual notification

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to primary Wi-Fi network
  WiFi.begin(primarySSID, primaryPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to primary network!");

  // Start Wi-Fi repeater
  WiFi.softAP(repeaterSSID, repeaterPassword);
  Serial.println("Repeater active!");

  // Set promiscuous mode to monitor packets
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(promiscuousCallback);

  // Setup web server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started!");
}

// Callback function for promiscuous mode
void promiscuousCallback(uint8_t* buf, uint16_t len) {
  // Check if the packet is a deauthentication frame (Type 0xC0)
  if (buf[0] == 0xC0) {
    deauthPackets++;
  }
}

void handleRoot() {
  String html = "<html><head><title>Wi-Fi Repeater + Jammer Detector</title></head><body>";
  html += "<h1>Wi-Fi Repeater + Jammer Detector</h1>";
  html += "<p>Deauthentication Packets Detected: " + String(deauthPackets) + "</p>";
  html += "<p>Primary Network: " + String(primarySSID) + "</p>";
  html += "<p>Repeater Network: " + String(repeaterSSID) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void sendEmailAlert() {
  WiFiClientSecure client;
  client.setInsecure(); // Use this for testing purposes; replace with certificate validation in production

  if (!client.connect("smtp.your-email-provider.com", 465)) {
    Serial.println("Connection to email server failed.");
    return;
  }

  client.println("EHLO smtp.your-email-provider.com");
  // Add SMTP authentication and email sending commands here based on your SMTP provider’s details

  client.stop();
}

void loop() {
  server.handleClient();

  // LED and alert for jammer detection
  if (deauthPackets >= alertThreshold) {
    Serial.printf("Warning: Detected %d deauth attack(s)!\n", deauthPackets);
    digitalWrite(ledPin, HIGH); // Turn on LED as an alert
    sendEmailAlert();           // Send email alert
    deauthPackets = 0;          // Reset counter after alert
    delay(500);                 // Pause for a moment before next check
    digitalWrite(ledPin, LOW);  // Turn off LED
  }

  delay(1000); // Check every second
}

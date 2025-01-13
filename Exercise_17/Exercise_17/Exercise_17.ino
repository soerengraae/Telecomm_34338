/**
 * @file Exercise_17.ino
 * @brief Demonstration of connecting to WiFi and sending data to ThingSpeak.
 * 
 * This sketch connects the ESP32 to the specified WiFi, then periodically sends 
 * two fields of data (RSSI and a digital pin reading) to a ThingSpeak channel. 
 * It also demonstrates reading back from the channel.
 */

#include <WiFi.h>
#include <ThingSpeak.h>

/**
 * @brief WiFi credentials.
 */
const char* ssid = "GN-Hotspot";  ///< SSID of the WiFi network.
const char* pass = "Denc@2022110"; ///< Password of the WiFi network.

/**
 * @brief WiFi client object for ThingSpeak.
 */
WiFiClient client;

/**
 * @brief ThingSpeak API information.
 */
const char* APIKey = "20205149I9EPB0ZF";    ///< Your ThingSpeak API key.
const char* server = "api.thingspeak.com";  ///< ThingSpeak server.
unsigned long channelID = 2808263;          ///< Your ThingSpeak channel ID.

/**
 * @brief Variables to store measured data.
 */
float data1; ///< Measured data field 1.
float data2; ///< Measured data field 2.

/**
 * @brief Post delay in milliseconds (send data every 5 seconds).
 */
#define postDelay 5 * 1000

/**
 * @brief Arduino setup function. Connects to WiFi and starts serial communication.
 */
void setup() {
  pinMode(4, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  Serial.println("");
  Serial.println(WiFi.localIP());
}

/**
 * @brief Arduino main loop. Reads data, checks WiFi connection, sends data to ThingSpeak, and reads back.
 */
void loop() {
  // Gather your data (example: RSSI and digital pin read)
  data1 = WiFi.RSSI();
  data2 = digitalRead(4);

  // Ensure WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Connect to ThingSpeak server
  client.connect(server, 80);

  // Set fields and write them
  ThingSpeak.setField(1, data1);
  ThingSpeak.setField(2, data2);
  Serial.println("Writing to ThingSpeak");
  ThingSpeak.writeFields(channelID, APIKey);

  // Read data back from ThingSpeak
  Serial.println("Reading from ThingSpeak");
  data1 = ThingSpeak.readIntField(channelID, 1, APIKey);
  Serial.print("Read RSSI: ");
  Serial.println(data1);

  client.stop();

  // Delay before the next post
  delay(postDelay);
}
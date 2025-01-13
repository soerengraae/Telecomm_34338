#include <WiFi.h>
#include <WiFiMulti.h> // ESP32 version of WiFiMulti
#include <WebServer.h> // ESP32 version of the WebServer library
#include <ESPmDNS.h>   // mDNS library for ESP32

WiFiMulti wifiMulti; 
WebServer server(80); // Create a WebServer instance

const int led = 4; // Change to the GPIO pin connected to your LED (e.g., 2 for the built-in LED on many ESP32 boards)

void handleRoot();
void handleLED();
void handleNotFound();

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH); // Ensure LED is off initially (ESP32 uses HIGH for off by default)

  // Connect to WiFi networks
  Serial.println();
  wifiMulti.addAP("GN-Hotspot", "Denc@2022110"); // Add Wi-Fi networks you want to connect to
  

  Serial.println();
  Serial.print("Connecting ...");

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected to:");
  Serial.println(WiFi.SSID());
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());

  // Start mDNS responder
  if (MDNS.begin("iot")) {
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  // Set up HTTP routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/LED", HTTP_POST, handleLED);
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "<html><title>Internet of Things - Demonstration</title><meta charset=\"utf-8\" \/> \
      <head></head><body><h1>Velkommen til denne WebServer</h1> \
      <p>Internet of Things (IoT) er \"tingenes Internet\" - dagligdags ting kommer på nettet og får ny værdi. Det kan løse mange udfordringer.</p> \
      <p>Her kommunikerer du med en webserver på en lille microcontroller af typen ESP32, som i dette tilfælde styrer en digital udgang, som du så igen kan bruge til at styre en lampe, en ventilator, tænde for varmen eller hvad du lyster</p> \
      <p>Klik på nedenstående knap for at tænde eller slukke LED på port GPIO2</p> \
      <form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Skift tilstand på LED\" style=\"width:500px; height:100px; font-size:24px\"></form> \
      <p>Med en ESP32 kan du lave sjove projekter</p> \
      <p>Vil du vide mere: Kig på hjemmesiden for uddannelsen : <a href=\"www.dtu.dk/net\">Netværksteknologi og it</a></p> \
      </body></html>");
}

void handleLED() {
  digitalWrite(led, !digitalRead(led)); // Toggle the LED state
  server.sendHeader("Location", "/");  // Redirect to the home page
  server.send(303);                    // HTTP 303 See Other
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}
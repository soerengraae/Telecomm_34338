/**
 * @file main.ino
 * @brief Demonstration of an ESP32 acting as a web server to toggle an LED.
 *
 * This sketch sets up a WiFi connection (using WiFiMulti to handle multiple
 * networks), starts an HTTP server, and serves a simple webpage. The user can
 * toggle an LED via a POST request.
 */

#include <WiFi.h>
#include <WiFiMulti.h> // ESP32 version of WiFiMulti
#include <WebServer.h> // ESP32 version of the WebServer library
#include <ESPmDNS.h>   // mDNS library for ESP32

/** 
 * @brief WiFiMulti instance to manage multiple networks.
 */
WiFiMulti wifiMulti; 

/** 
 * @brief Web server instance listening on port 80.
 */
WebServer server(80);

/** 
 * @brief GPIO pin used to drive the LED.
 * 
 * Change to the GPIO pin connected to your LED (e.g., 2 for built-in LED on many ESP32 boards).
 */
const int led = 4;

/**
 * @brief Handles the root ("/") HTTP GET request.
 * 
 * Sends an HTML page with information about IoT and a button to toggle the LED.
 */
void handleRoot();

/**
 * @brief Handles the "/LED" HTTP POST request.
 * 
 * Toggles the state of the LED and redirects back to the root page.
 */
void handleLED();

/**
 * @brief Handles requests for non-existent pages.
 * 
 * Sends a 404 Not Found response.
 */
void handleNotFound();

/**
 * @brief Arduino setup function.
 * 
 * Initializes serial communication, configures the LED pin, 
 * connects to WiFi using WiFiMulti, starts the mDNS responder, 
 * sets up HTTP routes, and starts the web server.
 */
void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH); // Ensure LED is off initially

  // Connect to WiFi networks
  Serial.println();
  wifiMulti.addAP("GN-TOP-SECRET", "TOP-SECRET"); // Add Wi-Fi networks you want to connect to
  
  Serial.println();
  Serial.print("Connecting ...");

  // Attempt to connect to one of the WiFi networks
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

/**
 * @brief Arduino main loop.
 * 
 * Continuously handles client requests coming in on the web server.
 */
void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", 
    "<html><title>Internet of Things - Demonstration</title><meta charset=\"utf-8\"/> \
     <body><h1>Velkommen til denne WebServer</h1> \
     <p>Internet of Things (IoT) er \"tingenes Internet\" - dagligdags ting kommer på nettet og får ny værdi. Det kan løse mange udfordringer.</p> \
     <p>Her kommunikerer du med en webserver på en lille microcontroller af typen ESP32, som i dette tilfælde styrer en digital udgang, som du så igen kan bruge til at styre en lampe, en ventilator, tænde for varmen eller hvad du lyster.</p> \
     <p>Klik på nedenstående knap for at tænde eller slukke LED på port GPIO2</p> \
     <form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Skift tilstand på LED\" style=\"width:500px; height:100px; font-size:24px\"></form> \
     <p>Med en ESP32 kan du lave sjove projekter</p> \
     <p>Vil du vide mere: Kig på hjemmesiden for uddannelsen : <a href=\"www.dtu.dk/net\">Netværksteknologi og it</a></p> \
     </body></html>"
  );
}

void handleLED() {
  // Toggle the LED
  digitalWrite(led, !digitalRead(led));

  // Redirect to the home page
  server.sendHeader("Location", "/");
  server.send(303); // HTTP 303 See Other
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}
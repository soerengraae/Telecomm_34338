/**
* @brief Connect the legs of the LM35 as described below. Connect to ATmega328P via USART.
*/

// Connect VDD to 5V
#define tempPin 0 // The output of the sensor is connected to A0
// Connect GND to GND

uint16_t sensorReading;
float temp;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorReading = analogRead(tempPin);

  // Convert reading to degrees Celcius
  temp = ((float)sensorReading * (5000 / 1024.0)) / 10;

  Serial.print(temp);
  Serial.write(176);
  Serial.println("C");

  delay(1000); // So we can actually read the output
}
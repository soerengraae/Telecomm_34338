/**
* @brief Connect the legs of the LM35 as described below. Connect to ATmega328P via USART.
* Connect three LEDs as described by their defines.
*/

// Connect VDD to 5V
#define tempPin 0 // The output of the sensor is connected to A0
// Connect GND to GND

#define greenLED 8  // The green LED is connected to D8
#define yellowLED 9  // The yellow LED is connected to D9
#define redLED 10  // The red LED is connected to D10

uint16_t sensorReading;
float temp;

void cold() {
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}

void warm() {
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(redLED, LOW);
}

void hot() {
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH);
}

void updateLEDS() {
  if (temp < 25)
    cold();
  else if (temp < 30)
    warm();
  else
    hot();
}

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  sensorReading = analogRead(tempPin);

  // Convert reading to degrees Celcius
  temp = ((float)sensorReading * (5000.0f / 1024.0f)) / 10.0f;

  Serial.print(temp);
  Serial.write(176);
  Serial.println("C");

  updateLEDS();

  delay(1000); // So we can actually read the output
}
/**
* @brief Connect the legs of the RGB LED and potentiometer as described below. Connect to ATmega328P via USART.
* Turn the potentiometer to fade between red and purple.
*/

#define potPin 0  // Output pin of the pot is connected to A0.
// Connect the two other legs to VDD and GND. Order doesn't matter.

#define bluePin 9 // The pin must be analog '~'
// Connect the pin for red to VDD
// Connect the pin for green to GND

uint16_t blue = 0;
float voltage;

void updateRGB() {
  analogWrite(bluePin, blue);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(bluePin, OUTPUT);

  analogReference(EXTERNAL);
  updateRGB();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  blue = analogRead(potPin);
  blue = map(blue, 0, 1023, 0, 255);

  Serial.print("Analog: ");
  Serial.print(blue);
  Serial.print(", ");
  voltage = ((float)blue/255.0f) * 3.3f;  // Convert the analog value to a voltage by following standard conversion formula
  Serial.print("Voltage: ");
  Serial.println(voltage, 3);

  updateRGB();
}

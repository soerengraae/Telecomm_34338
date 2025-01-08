#define potPin 0
#define bluePin 9

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
  voltage = ((float)blue/255.0f) * 3.3f;
  Serial.print("Voltage: ");
  Serial.println(voltage, 3);

  updateRGB();
}

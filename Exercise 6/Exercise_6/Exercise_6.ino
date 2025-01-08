#define aPin 6  // LED for character 'a' is connected to D6.
#define bPin 7  // LED for character 'b' is connected to D7.
#define cPin 8  // LED for character 'c' is connected to D8.
#define dPin 9  // LED for character 'd' is connected to D9.
#define ePin 10 // LED for character 'e' is connected to D10.

uint8_t rxbyte;

void setup() {
  // put your setup code here, to run once:
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(ePin, OUTPUT);

  digitalWrite(aPin, LOW);
  digitalWrite(bPin, LOW);
  digitalWrite(cPin, LOW);
  digitalWrite(dPin, LOW);
  digitalWrite(ePin, LOW);

  Serial.begin(9600);
}

void updateLEDS() {
  switch (rxbyte) {
    case 'A': case 'a':
        digitalWrite(aPin, HIGH);
        digitalWrite(bPin, LOW);
        digitalWrite(cPin, LOW);
        digitalWrite(dPin, LOW);
        digitalWrite(ePin, LOW);
        break;

    case 'B': case 'b':
        digitalWrite(aPin, LOW);
        digitalWrite(bPin, HIGH);
        digitalWrite(cPin, LOW);
        digitalWrite(dPin, LOW);
        digitalWrite(ePin, LOW);
        break;

    case 'C': case 'c':
        digitalWrite(aPin, LOW);
        digitalWrite(bPin, LOW);
        digitalWrite(cPin, HIGH);
        digitalWrite(dPin, LOW);
        digitalWrite(ePin, LOW);
        break;

    case 'D': case 'd':
        digitalWrite(aPin, LOW);
        digitalWrite(bPin, LOW);
        digitalWrite(cPin, LOW);
        digitalWrite(dPin, HIGH);
        digitalWrite(ePin, LOW);
        break;

    case 'E': case 'e':
        digitalWrite(aPin, LOW);
        digitalWrite(bPin, LOW);
        digitalWrite(cPin, LOW);
        digitalWrite(dPin, LOW);
        digitalWrite(ePin, HIGH);
        break;

    default:
        digitalWrite(aPin, LOW);
        digitalWrite(bPin, LOW);
        digitalWrite(cPin, LOW);
        digitalWrite(dPin, LOW);
        digitalWrite(ePin, LOW);
        break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    rxbyte = Serial.read();
    updateLEDS();
  }
}

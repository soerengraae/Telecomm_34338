#define redPin 9    // Pin used must be analog '~'
#define greenPin 10 // Pin used must be analog '~'
#define bluePin 11  // Pin used must be analog '~'

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

void updateRGB() {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  updateRGB();

  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    red = Serial.parseInt();
    green = Serial.parseInt();
    blue = Serial.parseInt();

    updateRGB();
  }
}

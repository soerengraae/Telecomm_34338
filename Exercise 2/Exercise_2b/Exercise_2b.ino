#define greenLED  8
#define yellowLED 9
#define redLED    10
#define delayTime 2000

void red() {
  Serial.println("STOP!");
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
}

void redyellow() {
  Serial.println("GET READY!");
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
}

void green() {
  Serial.println("GO!");
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
}

void yellow() {
  Serial.println("STOP-ISH!");
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
}

void sequence() {
  red();
  delay(delayTime);
  redyellow();
  delay(delayTime);
  green();
  delay(delayTime);
  yellow();
  delay(delayTime);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Serial.begin(115200);
  red();
}

void loop() {
  // put your main code here, to run repeatedly:
  sequence();
}

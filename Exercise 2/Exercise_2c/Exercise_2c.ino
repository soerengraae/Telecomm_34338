#define LED0 8
#define LED1 9
#define LED2 10

void updateCounter(uint8_t value) {
  Serial.print(value);
  Serial.print(", ");
  Serial.println((value >> 2) & 1);
  Serial.print((value >> 1) & 1);
  Serial.print(value & 1);

  digitalWrite(LED0, value & 1);
  digitalWrite(LED1, (value >> 1) & 1);
  digitalWrite(LED2, (value >> 2) & 1);
}

uint8_t num;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);
  num = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  updateCounter(num);

  num++;
  num = num % 8;

  delay(1000);
}

/**
  @brief Connect to ATmega328P via USART.
/*

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int incomingByte = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println((char)incomingByte);
  }
}

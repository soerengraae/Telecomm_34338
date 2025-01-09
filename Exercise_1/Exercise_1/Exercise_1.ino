#define ledPin    8
#define unitTime  250 // ms
#define dotTime   unitTime
#define dashTime  unitTime * 3
#define letterTime  unitTime * 3
#define wordTime    unitTime * 7

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(dotTime);
  digitalWrite(ledPin, LOW);
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(dashTime);
  digitalWrite(ledPin, LOW);
}

void S() {
  dot();
  delay(unitTime);
  dot();
  delay(unitTime);
  dot();
}

void O() {
  dash();
  delay(unitTime);
  dash();
  delay(unitTime);
  dash();
}

void E() {
  dot();
  delay(unitTime);
}

void R() {
  dot();
  delay(unitTime);
  dash();
  delay(unitTime);
  dot();
}

void N() {
  dash();
  delay(unitTime);
  dot();
}

void outputLetter(char letter) {
  switch (letter) {
    case 'S': case 's':
      S();
      break;
    case 'O': case 'o':
      O();
      break;
    case 'E': case 'e':
      E();
      break;
    case 'R': case 'r':
      R();
      break;
    case 'N': case 'n':
      N();
      break;
    default:
      break;
  }
}

void outputWord(char *str) {
  for(; *str; str++) { // Just a while-loop in disguise
    outputLetter(*str);
    delay(letterTime);
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);

  char name[] = "Soeren";
  
  outputWord(name);
}

void loop() {

}
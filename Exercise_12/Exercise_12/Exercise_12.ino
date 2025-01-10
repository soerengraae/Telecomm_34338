/**
 * @file main.ino
 * @brief Demonstration of an Arduino game using an LCD, LEDs, and a button.
 * 
 * The game cycles LEDs in a snake sequence (except at level 8; that's random), and the user must press 
 * the button at the correct time. Hitting it at the right LED increments a score;
 * missing it increments a miss counter. The game ends at 10 hits.
 */

#include <LiquidCrystal.h>

/** 
 * @brief Assign pins for the LCD interface (RS, EN, D4, D5, D6, D7).
 */
#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2

/** 
 * @brief Instantiate LCD using selected pins.
 */
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/** 
 * @brief LED pins.
 */
#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9
#define LED5 10

/** 
 * @brief Pin for the game button.
 */
#define buttonPin 13

/** 
 * @brief Array of LED pins for iteration.
 */
uint8_t LEDS[] = {LED1, LED2, LED3, LED4, LED5};

/** 
 * @brief Index of the current LED.
 */
uint8_t LED = 0;

/** 
 * @brief Flag indicating whether the user has already hit a successful press this cycle.
 */
uint8_t hitFlag = 0;

/** 
 * @brief Delay time in increments of 10ms (50 => 500ms).
 */
uint8_t delayTime = 50;

/** 
 * @brief Total number of hits.
 */
uint16_t hits = 0;

/** 
 * @brief Total misses so far.
 */
uint16_t misses = 0;

/** 
 * @brief Used as timekeeper.
 */
uint16_t counter = 0;

/**
 * @brief Arduino setup function. Initializes LCD, input pins, and LED pins.
 */
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);  
  lcd.print("Hits: ");
  lcd.print(hits);
  lcd.setCursor(0, 1);
  lcd.print("Misses: ");
  lcd.print(misses);

  pinMode(buttonPin, INPUT_PULLUP);
  for (size_t i = 0; i < 5; i++) {
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], LOW);
  }
}

/**
 * @brief Lights one random LED and turns off the others.
 */
void randomSequence() {
  uint8_t LED = random(0, 4);

  for (size_t i = 0; i < 5; i++) {
    digitalWrite(LEDS[i], (i == LED) ? HIGH : LOW);
  }
}

/**
 * @brief "Snake" sequence: turns off the previous LED and turns on the new one.
 * Cycles through the array of LEDs in a linear pattern.
 */
void snakeSequence() {
  if (LED == 0) {
    // Edge case: If the new LED is index 0, previous is index 4
    digitalWrite(LEDS[4], 0);
    digitalWrite(LEDS[LED], 1);
  } else {
    digitalWrite(LEDS[LED - 1], 0);
    digitalWrite(LEDS[LED], 1);
  }

  LED++;
  LED %= 5;  // Wrap around to index 0 after the last LED
}

/**
 * @brief Displays a winning message and rapidly flashes the LEDs indefinitely.
 */
void win() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Winner Winner");
  lcd.setCursor(0, 1);
  lcd.print("Eat your dinner");

  while (1) {
    // Turn all LEDs off
    for (size_t i = 0; i < 5; i++) {
      digitalWrite(LEDS[i], LOW);
    }

    delay(500);

    // Turn all LEDs on
    for (size_t i = 0; i < 5; i++) {
      digitalWrite(LEDS[i], HIGH);
    }

    delay(500);
  }
}

/**
 * @brief Process a successful hit.
 * Increments hits, applies fancy LED flashing, and eventually triggers win().
 */
void hit() {
  hits++;
  if (hits == 10) {
    win();
  }
  
  // Speed things up a bit each time
  delayTime -= 5;

  hitFlag = 1;
  lcd.setCursor(6, 0);
  lcd.print(hits);

  // Turn all LEDs off
  for (size_t i = 0; i < 5; i++) {
    digitalWrite(LEDS[i], LOW);
  }

  // Animate a forward wave
  for (size_t i = 0; i < 5; i++) {
    digitalWrite(LEDS[i], HIGH);
    delay(75);
  }

  // Turn them off again
  for (size_t i = 0; i < 5; i++) {
    digitalWrite(LEDS[i], LOW);
  }

  // Animate a reverse wave
  for (size_t i = 0; i < 5; i++) {
    digitalWrite(LEDS[4 - i], HIGH);
    delay(75);
  }

  // Flash all LEDs on/off
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      digitalWrite(LEDS[j], LOW);
    }
    delay(100);
    for (size_t i = 0; i < 5; i++) {
      digitalWrite(LEDS[i], HIGH);
    }
    delay(100);
  }

  // Finally, turn them all off
  for (size_t i = 0; i < 5; i++) {
    digitalWrite(LEDS[i], LOW);
  }
}

/**
 * @brief Process a miss. Increments misses and pauses briefly.
 */
void miss() {
  misses++;
  lcd.setCursor(8, 1);
  lcd.print(misses);

  // Turn all LEDs off
  for (size_t i = 0; i < 5; i++) {
    digitalWrite(LEDS[i], LOW);
  }

  delay(1000);
}

/**
 * @brief Arduino loop function, repeatedly updates LED sequences and checks for button presses.
 */
void loop() {
  // Update LED sequence every "delayTime" intervals (each interval is 10ms)
  if (!(counter % delayTime)) {
    counter = 0;
    hitFlag = 0;

    // At 8 hits, switch to random sequence
    if (hits == 8) {
      randomSequence();
    } else {
      snakeSequence();
    }

    Serial.println(delayTime);
  }

  // Check LED and button press
  if (LED == 3) {
    if (!digitalRead(buttonPin) && !hitFlag) {
      hit();
    }
  } else {
    // Wrong LED
    if (!digitalRead(buttonPin) && !hitFlag) {
      miss();
    }
  }

  counter++;
  delay(10);
}
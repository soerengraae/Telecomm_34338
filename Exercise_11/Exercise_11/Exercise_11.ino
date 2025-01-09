#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Connect VDD to 5V
#define tempPin 0 // The output of the sensor is connected to A0
// Connect GND to GND

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

uint16_t sensorReading;
float temp;
uint8_t warningFlag = 0;

void setup()
{
  lcd.init();

  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp in Celcius:");
  lcd.setCursor(0,1);
}

void loop()
{
  sensorReading = analogRead(tempPin);

  // Convert reading to degrees Celcius
  temp = ((float)sensorReading * (5000.0f / 1024.0f)) / 10.0f;

  // Print hot warning if temperature gets too high - only if it's not already printed
  if (temp > 27 && warningFlag == 0) {
    lcd.setCursor(10, 1);
    lcd.print("!!!");
    lcd.setCursor(0, 1);

    warningFlag = 1;
  }

  // Clear hot warning if temperature drops
  if (temp < 27 && warningFlag == 1) {
    lcd.setCursor(10, 1);
    lcd.print("   ");
    lcd.setCursor(0, 1);

    warningFlag = 0;
  }

  lcd.setCursor(0, 1);
  lcd.print(temp, 2);

  /**
   * Instead of using delay(1000) for a stable temperature we could use a e.g. a low-pass filter or a moving average filter to make the temperature stable.
   * If a low-pass filter is to be used, a delay between each display update should still be implemented however seen fit.
   * For a moving average filter, the display would just update at the end of data collection.
   */
  delay(1000);
}

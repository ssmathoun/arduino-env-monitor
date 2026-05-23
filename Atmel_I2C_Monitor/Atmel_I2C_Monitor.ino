#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE); 
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600); // Opens the USB connection to my device at 9600 bits per second.

  dht.begin(); // Wakes up sensor

  lcd.init(); // Wakes up the screen
  lcd.backlight();

}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature(); // Reads temperature in Celsius.

  // Sends humidity and temperature to Computer's Serial Monitor.
  Serial.print(F("Humidity: "));
  Serial.println(humidity);

  Serial.print(F("Temp(C): "));
  Serial.println(tempC);

  // Sends humidity and temperature to physical LCD Screen.
  lcd.setCursor(0,0); // Move cursor to Column 0, Row 0 in first row and top-left
  lcd.print("Temp(C): ");
  lcd.print(tempC);

  lcd.setCursor(0,1); // Move cursor to Column 0, Row 1 in second row and bottom-left.
  lcd.print("Hum: ");
  lcd.print(humidity);

}

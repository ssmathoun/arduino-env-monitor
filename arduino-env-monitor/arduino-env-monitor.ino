#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// The 8-Bit Parallel Constructor
// Format: LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)
LiquidCrystal lcd(3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);

unsigned long previousMillis = 0; // Stores the last time the sensor was updated.
const long interval = 2000; // Interval at which to read sensor data (2000 milliseconds).

void setup() {
  Serial.begin(9600); // Opens the USB connection to my device at 9600 bits per second.
  dht.begin(); // Wakes up sensor
  lcd.begin(16, 2); // Initializes the 16x2 screen in 8-bit mode

}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if 2 seconds have passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

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
    lcd.print(tempC, 1); // 1 for 1 decimal place

    lcd.setCursor(0,1); // Move cursor to Column 0, Row 1 in second row and bottom-left.
    lcd.print("Hum: ");
    lcd.print(humidity, 1); // 1 for 1 decimal place
  }

}

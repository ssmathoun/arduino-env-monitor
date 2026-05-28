#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define TRIG_PIN A0
#define ECHO_PIN A1

DHT dht(DHTPIN, DHTTYPE);

// The 8-Bit Parallel Constructor
// Format: LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)
LiquidCrystal lcd(3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);

unsigned long previousMillis = 0; // Stores the last time the sensor was updated.
const long interval = 2000; // Interval at which to read sensor data (2000 milliseconds).

void setup() {
  Serial.begin(9600); // Opens the USB connection to my device at 9600 bits per second.
  dht.begin(); // Wakes up Temp/Humidity DHT 11 sensor

  // Initilize Ultrasonic Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.begin(16, 2); // Initializes the 16x2 screen in 8-bit mode

}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if 2 seconds have passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Fires Ultrasonic Pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10); // 10 microsecond trigger pulse
    digitalWrite(TRIG_PIN, LOW);

    // Read the Echo
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    int distance;

    if (duration == 0) {
      distance = -1; // -1 means timeout/out of range
    }
    else {
      distance = duration * 0.0343 / 2; // Convert time to centimeters
    }

    // Read DHT11
    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature(); // Reads temperature in Celsius.

    // Sends sensor data to Computer's Serial Monitor.
    Serial.print(F("Humidity: "));
    Serial.println(humidity);

    Serial.print(F("Temp(C): "));
    Serial.println(tempC);

    Serial.print(F("Distance(cm): "));
    Serial.println(distance);

    // Send to Physical LCD Screen
    lcd.clear(); // Clear old data to prevent overlapping ghost characters

    // Row 0 (Top): Temp and Humidity combined
    lcd.setCursor(0,0); 
    lcd.print("T:");
    lcd.print(tempC, 1); 
    lcd.print("C H:");
    lcd.print(humidity, 1); 
    lcd.print("%");

    // Row 1 (Bottom): Distance
    lcd.setCursor(0,1); 
    lcd.print("Dist: ");
    if (distance == -1) {
      lcd.print("MAX RANGE");
    } else {
      lcd.print(distance);
      lcd.print(" cm");
    }
  }
}

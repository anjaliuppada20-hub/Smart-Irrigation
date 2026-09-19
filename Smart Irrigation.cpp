#include <DHT.h>

#define SOIL_SENSOR A0
#define DHT_PIN 2
#define DHT_TYPE DHT11

#define RELAY_PIN 8
#define GREEN_LED 9
#define RED_LED 10

DHT dht(DHT_PIN, DHT_TYPE);

// Adjust this value after testing your soil sensor
const int DRY_THRESHOLD = 600;

void setup() {
  Serial.begin(9600);

  pinMode(SOIL_SENSOR, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  dht.begin();

  Serial.println("Smart Irrigation System");
  Serial.println("System Starting...");

  delay(2000);
}

void loop() {
  int soilValue = analogRead(SOIL_SENSOR);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.println("------------------------");

  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  }

  if (!isnan(humidity)) {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Dry soil
  if (soilValue >= DRY_THRESHOLD) {

    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("Soil is DRY");
    Serial.println("Water Pump: ON");

  } else {

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    Serial.println("Soil is MOIST");
    Serial.println("Water Pump: OFF");
  }

  delay(2000);
}

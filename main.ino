#include "DHT.h"

/* Change these values based on your observations */
#define WET_SOIL 277   // Define max value we consider soil 'wet'
#define DRY_SOIL 380   // Define min value we consider soil 'dry'

// Define sensor pins and power 
#define SOIL_MOISTURE_SENSOR_PIN A0
#define WATER_LEVEL_SENSOR_PIN A1
#define DHT_SENSOR_PIN 6
#define WATER_LEVEL_SENSOR_POWER 7

// Define DHT object
#define DHTTYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHTTYPE);

void setup() {  
  // Set sensor power pin as OUTPUT
  pinMode(WATER_LEVEL_SENSOR_POWER, OUTPUT);
  // Set power pin to LOW initially
  digitalWrite(WATER_LEVEL_SENSOR_POWER, LOW);

  // Initialize DHT sensor and serial communication
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int moisture = analogRead(SOIL_MOISTURE_SENSOR_PIN);
  int waterLevel = readWaterLevelSensor();

  // Print sensor values
  printMoisture(moisture);
  printWaterLevel(waterLevel);
  printTemperatureAndHumidity();

  // Delay for three seconds before next reading
  delay(3000);
}

void printTemperatureAndHumidity(){
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  Serial.println("Temperature = " + String(temperature) + " °C");
  Serial.println("Humidity = " + String(humidity) + " %");
}

void printMoisture(int moisture){
  Serial.print("Analog output: ");
  Serial.println(moisture);
  
  // Determine status of the soil
  if (moisture < WET_SOIL) {
    Serial.println("Status: Soil is too wet");
  } else if (moisture >= WET_SOIL && moisture < DRY_SOIL) {
    Serial.println("Status: Soil moisture is perfect");
  } else {
    Serial.println("Status: Soil is too dry - time to water!");
  }
  Serial.println();
}

void printWaterLevel(int waterLevel){
  Serial.print("Water level: ");
  Serial.println(waterLevel);
}

int readWaterLevelSensor() {
  // Turn the sensor ON
  digitalWrite(WATER_LEVEL_SENSOR_POWER, HIGH);
  // Wait for the sensor to stabilize
  delay(10);
  // Read the analog value from sensor
  int val = analogRead(WATER_LEVEL_SENSOR_PIN);
  // Turn the sensor OFF
  digitalWrite(WATER_LEVEL_SENSOR_POWER, LOW);
  
  return val;
}

#include "humidity.hpp"
#include "globals.hpp"
#include "CO2.hpp"

DHT dht(DHTPIN, DHTTYPE);
MG811 co2Sensor(CO2PIN);
float v400 = 1.016;
float v40000 = 3.93;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  co2Sensor.begin(v400, v40000);
  //co2Sensor.calibrate();  co2Sensor.calibrate();
}

void loop() {
  std::vector<float> dhtValue = dhtValues(dht);
  float CO2Value = getCO2Value(co2Sensor);
  Serial.println(CO2Value);
  // put your main code here, to run repeatedly:

}

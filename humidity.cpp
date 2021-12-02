#include "humidity.hpp"

std::vector<float> dhtValues(DHT dht){
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return{-1.0, -1.0};
  }
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print ("Humidity: ");
  Serial.print (h);
  Serial.print (" % ");
  Serial.print ("Temperature: ");
  Serial.print (t);
  Serial.print (" *C ");

  return {h, t};
}

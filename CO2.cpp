#include "CO2.hpp"
float getCO2Value(MG811 co2Sensor){
  return co2Sensor.read();
}

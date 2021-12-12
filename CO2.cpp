#include "CO2.hpp"
//Measures CO2
float getCO2Value(MG811 co2Sensor){
  return co2Sensor.read();
}

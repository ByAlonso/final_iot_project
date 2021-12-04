#include "humidity.hpp"
#include "globals.hpp"
#include "CO2.hpp"
#include "window.hpp"
#include "communications.hpp"
#include <string>

DHT dht(DHTPIN, DHTTYPE);
MG811 co2Sensor(CO2PIN);
float v400 = 1.016;
float v40000 = 3.93;
SoftwareSerial mySerial(RX, TX);
rn2xx3 myLora(mySerial);
std::string deviceId = ""

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupWindow();
  dht.begin();
  co2Sensor.begin(v400, v40000);
  //co2Sensor.calibrate();  co2Sensor.calibrate();
  mySerial.begin(9600);
  
  //reset rn2483
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(RST, HIGH);

  //initialise the rn2483 module
  myLora.autobaud();

  //print out the HWEUI so that we can register it via ttnctl
  Serial.println("When using OTAA, register this DevEUI: ");
  deviceId = myLora.hweui();
  Serial.println("appeui: " + myLora.appeui());
  Serial.println("deveui: " + myLora.deveui());
}

void loop() {
  /*std::vector<float> dhtValue = dhtValues(dht);

  std::string humidity = std::to_string(dhtValue.get(0)).c_str();
  std::string temperature = std::to_string(dhtValue.get(1)).c_str();
  std::string CO2Value = std::to_string(getCO2Value(co2Sensor)).c_str();
  std::string windowStatus = getWindowStatus(); // We have to check when we receive the signal of changing led and call setWindowStatus
  //timestamp should be retrieved in server each time a message is receiver

  delay(10000);*/
}

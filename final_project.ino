#include "humidity.hpp"
#include "globals.hpp"
#include "CO2.hpp"
#include "communications.hpp"
#include <ESP8266WiFi.h>

void setupWindow(){
  pinMode(WINDOWPIN, OUTPUT);
  digitalWrite(WINDOWPIN, LOW); 
}
String getWindowStatus(){
  return windowStatus;
}
void setWindowStatus(){
  if(windowStatus == "0"){
    digitalWrite(WINDOWPIN, HIGH); 
    windowStatus = "1";
  }else{
    digitalWrite(WINDOWPIN, LOW);
     windowStatus = "0"; 
  }
}

DHT dht(DHTPIN, DHTTYPE);
MG811 co2Sensor(CO2PIN);
float v400 = 1.016;
float v40000 = 3.93;
SoftwareSerial mySerial(TX, RX);
rn2xx3 myLora(mySerial);
String deviceId = "";

void setup() {
  Serial.begin(57600);
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

  delay(100); //wait for the RN2xx3's startup message
  mySerial.flush();

  //initialise the rn2483 module
  myLora.autobaud();

  //print out the HWEUI so that we can register it via ttnctl
  deviceId = String( myLora.hweui() );
}

void loop() {
  std::vector<float> dhtValue = dhtValues(dht);

  String humidity = String(dhtValue[0]);
  String temperature = String(dhtValue[1]);
  String CO2Value = String(getCO2Value(co2Sensor));
  String windowStatus = getWindowStatus(); // We have to check when we receive the signal of changing led and call setWindowStatus
  //timestamp should be retrieved in server each time a message is receiver
  Serial.println(deviceId);
  Serial.println(humidity);
  Serial.println(temperature);
  Serial.println(CO2Value);
  Serial.println(windowStatus);
  String finalData = deviceId  + "," + humidity + "," + temperature + "," + CO2Value + "," + windowStatus;
  Serial.println(finalData);

  delay(300);
}

#include "humidity.hpp"
#include "globals.hpp"
#include "CO2.hpp"
#include "communications.hpp"
#include <ESP8266WiFi.h>

String Asciitohex( String data ) {

  // Length (with one extra character for the null terminator)
  int str_len = data.length() + 1;

  // Prepare the character array (the buffer)
  char hex[str_len];

  // Copy it over
  data.toCharArray(hex, str_len);
  // 'clear' buffer
  char buffer[sizeof(hex) * 2 + 1];

  buffer[0] = '\0';

  // loop through character array
  for (uint8_t cnt = 0; cnt < strlen(hex); cnt++)
  {
    // conver each character to its hex representation
    itoa(hex[cnt], &buffer[cnt * 2], 16);

  }
  // return result
  return String(buffer);
}

String hexToAscii( String hex )
{
  uint16_t len = hex.length();
  String ascii = "";


  for ( uint16_t i = 0; i < len; i += 2 )
    ascii += (char)strtol( hex.substring( i, i + 2 ).c_str(), NULL, 16 );

  return ascii;
}

void setupWindow() {
  pinMode(WINDOWPIN, OUTPUT);
  digitalWrite(WINDOWPIN, LOW);
}
String getWindowStatus() {
  return windowStatus;
}
void setWindowStatus() {
  if (windowStatus == "0") {
    digitalWrite(WINDOWPIN, HIGH);
    windowStatus = "1";
  } else {
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
String humidity = "";
String temperature = "";
String CO2Value = "";
String str = "";
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
  setupMySerial();

  deviceId = String( myLora.hweui() );
}

String finalData = "";

void loop() {
  std::vector<float> dhtValue = dhtValues(dht);

  humidity = String(dhtValue[0]);
  temperature = String(dhtValue[1]);
  CO2Value = String(getCO2Value(co2Sensor));
  windowStatus = getWindowStatus(); // We have to check when we receive the signal of changing led and call setWindowStatus
  //timestamp should be retrieved in server each time a message is receiver
  Serial.println(deviceId);
  Serial.println(humidity);
  Serial.println(temperature);
  Serial.println(CO2Value);
  Serial.println(windowStatus);
  finalData = Asciitohex(deviceId  + "," + humidity + "," + temperature + "," + CO2Value + "," + windowStatus);
  
  mySerial.println("radio tx " + finalData);
  str = mySerial.readStringUntil('\n');
  Serial.println(str);
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  delay(10000);
}

void setupMySerial() {
  Serial.println("Initing LoRa");
  
  mySerial.println("mac pause");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set mod lora");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set freq 869100000");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set pwr 14");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set sf sf7");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set afcbw 41.7");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set rxbw 125");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set prlen 8");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set crc on");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set iqi off");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set cr 4/5");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  /*mySerial.println("radio set wdt 60000"); //disable for continuous reception
    str = mySerial.readStringUntil('\n');
    Serial.println(str);*/

  mySerial.println("radio set sync 12");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);

  mySerial.println("radio set bw 125");
  str = mySerial.readStringUntil('\n');
  Serial.println(str);
}

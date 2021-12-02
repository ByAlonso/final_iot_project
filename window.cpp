#include "window.hpp"
void setupWindow(){
  pinMode(WINDOWPIN, OUTPUT);
  digitalWrite(WINDOWPIN, LOW); 
}
std::string getWindowStatus(){
  return windowStatus;
}
void setWindowStatus(){
  if(windowStatus == "0"){
    digitalWrite(WINDOWPIN, HIGH); 
  }else{
    digitalWrite(WINDOWPIN, LOW); 
  }
}

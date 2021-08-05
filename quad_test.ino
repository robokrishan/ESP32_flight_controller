#include <Alpha.h>

Alpha copter;

const char* ssid = "Hasenhoeft";
const char* pwd = "21162010819665839679";
const char* pot_server = "http://192.168.178.31/pot_string";

void setup() {
  // put your setup code here, to run once:
  copter.setESCPins(16, 17, 18, 19);
  copter.attachESC();
  copter.setPOTPin(34);
  copter.setLCDAddress(39);
  copter.setLCDDimensions(16, 2);
  copter.beginLCD();
  copter.setPOTIP((char*)pot_server);
  copter.setSSID((char*)ssid);
  copter.setPWD((char*)pwd);
  copter.connect();
  copter.beginBLDC();
  copter.updateLCDRC();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  copter.updateLCDRC();
  copter.fly();
}

#include "Arduino.h"
#include "Alpha.h"

// Consructors
Alpha::Alpha() {
	// Initialize task counter
	task = 0;

	// Print Debug Info
	Serial.begin(115200);
	Serial.print("\n\n\n[");
	Serial.print(task);
	Serial.println("]\tQuadcopter object created!");
	task++;

	// Initialize Private Variables e.g. Pins, Dimensions, Addresses
	debug_pot = 0;
	pot_val = 0;
	pot_val_rc = "0";
	lcd_addr = 39;
	duty = 1000;
	lcd_width = lcd_height = 0;
	fl_esc_pin = 0;
	fr_esc_pin = 0;
	bl_esc_pin = 0;
	br_esc_pin = 0;
}

Alpha::Alpha(int esc1, int esc2, int esc3, int esc4) {
	// Create object
	Alpha();

	// Set ESC pins
	setESCPins(esc1, esc2, esc3, esc4);
}


// Public Member Functions
void Alpha::attachESC() {
	// Attach ESC objects to their pins
	fl_esc.attach(fl_esc_pin);
	fr_esc.attach(fr_esc_pin);
	bl_esc.attach(bl_esc_pin);
	br_esc.attach(br_esc_pin);

	// Print Debug Info}
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tAttached ESCs to pins\t\t\t");
	Serial.print(fl_esc_pin);
	Serial.print(", ");
	Serial.print(fr_esc_pin);
	Serial.print(", ");
	Serial.print(bl_esc_pin);
	Serial.print(", ");
	Serial.println(br_esc_pin);
	task++;
}

void Alpha::setESCPins(int pin1, int pin2, int pin3, int pin4) {
	// Update ESC pins
	fl_esc_pin = pin1;
	fr_esc_pin = pin2;
	bl_esc_pin = pin3;
	br_esc_pin = pin4;

	// Print Debug Info
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tInitialized ESCs to pins\t\t");
	Serial.print(fl_esc_pin);
	Serial.print(", ");
	Serial.print(fr_esc_pin);
	Serial.print(", ");
	Serial.print(bl_esc_pin);
	Serial.print(", ");
	Serial.println(br_esc_pin);
	task++;
}

void Alpha::setPOTPin(int pot) {
	// Set Potentiometer Pin
	debug_pot = pot;

	// Print Debug Info
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tInitialized Potentiometer on pin\t");
	Serial.println(debug_pot);
	task++;
}

void Alpha::setLCDAddress(int addr) {
	// Update LCD I2C Address (HEX)
	lcd_addr = addr;

	// Print Debug Info
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tInitialized LCD I2C Address to\t\t0x");
	Serial.println(lcd_addr, HEX);
	task++;
}

void Alpha::setLCDDimensions(int width, int height) {
	// Update LCD Dimensions
	lcd_width = width;
	lcd_height = height;

	// Print Debug Info
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tInitialized LCD Dimensions to\t\t");
	Serial.print("(");
	Serial.print(lcd_width);
	Serial.print(", ");
	Serial.print(lcd_height);
	Serial.println(")");
	task++;
}

void Alpha::beginLCD() {
	// Create LCD Object
	lcd = new LiquidCrystal_I2C(lcd_addr, lcd_width, lcd_height);
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tLCD Display object created!\t\t");
	Serial.print("("); Serial.print(lcd_width); Serial.print(", ");
	Serial.print(lcd_height);
	Serial.println(")");
	task++;

	// Turn on Display and Print Msg
	lcd->init();
	lcd->backlight();
	lcd->print("Initializing...");
	delay(2000);
	lcd->setCursor(0, 1);
	lcd->print("Display Ready!");
	delay(2000);
	lcd->clear();

	// Print Debug Info
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tStarted LCD Display on address\t\t0x");
	Serial.println(lcd_addr, HEX);
	task++;
}

void Alpha::beginBLDC() {
	// Write Duty-LOW to BLDCs
	fl_esc.writeMicroseconds(duty);
	fr_esc.writeMicroseconds(duty);
	bl_esc.writeMicroseconds(duty);
	br_esc.writeMicroseconds(duty);

	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tBLDCs initialized with PPM duty:\t");
	Serial.print(duty);
	Serial.println("μs");
	task++;
}

void Alpha::updateLCD() {
	lcd->setCursor(1, 0);
	lcd->print("POT");
	lcd->setCursor(12, 0);
	lcd->print("PWM");
	lcd->setCursor(1, 1);
	lcd->print("      ");
	lcd->setCursor(0, 1);
	lcd->print(readPotRC());
	lcd->setCursor(11, 1);
	lcd->print("      ");
	lcd->setCursor(11, 1);
	readPot();
	lcd->print(duty);
}

void Alpha::updateLCDRC() {
	lcd->setCursor(0, 0);
	lcd->print("Receiving:");
	lcd->setCursor(0, 1);
	lcd->print("    ");
	lcd->setCursor(0, 1);

	lcd->print(readPotRC());
	readPot();
}

String Alpha::readPotRC() {
	pot_val_rc = httpGETRequest(POT_SERVER);
	return pot_val_rc;
}

void Alpha::readPot() {
	duty = pot_val_rc.toInt();
	//duty = map(pot_val, POT_MIN, POT_MAX, DUTY_MIN, DUTY_MAX);
}




void Alpha::fly() {
	fl_esc.writeMicroseconds(duty);
	fr_esc.writeMicroseconds(duty);
	bl_esc.writeMicroseconds(duty);
	br_esc.writeMicroseconds(duty);
}

void Alpha::setPOTIP(char* ip) {
	POT_SERVER = ip;
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tConfigured Transmitter Addr.\t\t");
	Serial.println(POT_SERVER);
	task++;
}

String Alpha::httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "--";

  if (httpResponseCode>0) {
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void Alpha::connect() {
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, pwd);
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tConnecting to network\t\t\t");
	while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
	Serial.println();
	task++;
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tConnected to ");
	Serial.print(ssid);
	Serial.print("\t\t\t");
	Serial.println(WiFi.localIP());
	task++;
}

void Alpha::setSSID(char* ssid_in) {
	ssid = ssid_in;
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tConfigured WIFI\t\t\t\t");
	Serial.println(ssid);
	task++;
}

void Alpha::setPWD(char* pwd_in) {
	pwd = pwd_in;
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tConfigured Password\t\t\t");
	for(int i = 0; i < strlen(pwd_in); i++) {
		Serial.print("*");
	}
	Serial.println();
	task++;
}

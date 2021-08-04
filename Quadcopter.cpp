#include "Arduino.h"
#include "Quadcopter.h"

// Constructor and Parametrized Constructor

Quadcopter::Quadcopter() {
	Quadcopter(16, 17, 18, 19);
}
Quadcopter::Quadcopter(const int esc1, const int esc2, const int esc3, const int esc4) {
	debug_pot = 34;
	pot_value = analogRead(debug_pot);
	lcd_addr = 39;
	task = 0;
	duty = 1000;
	Serial.print("[");
	Serial.print(task);
	Serial.println("]\tQuadcopter object created!");
	task++;
	
	attach_esc(esc1, esc2, esc3, esc4);
	init_lcd();
	init_bldc();
	update_lcd();
}


// Public Member Functions for Initializing object instances

void Quadcopter::init_lcd() {
	lcd = LiquidCrystal_I2C(lcd_addr, 16, 2);
	Serial.print("[");
	Serial.print(task);
	Serial.println("]\tLCD Display object created.");
	task++;
	lcd->init();
	lcd->backlight();
	lcd->print("Initializing...");
	delay(2000);
	lcd->setCursor(0, 1);
	lcd->print("Display Ready!");
	delay(2000);
	lcd->clear();
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tLCD Display Initialized at address:\t");
	Serial.println(lcd_addr, HEX);
	task++;
}
void Quadcopter::attach_esc() {
	fl_esc.attach(16);
	fr_esc.attach(17);
	bl_esc.attach(18);
	br_esc.attach(19);
	Serial.print("[");
	Serial.print(task);
	Serial.println("]\tAttached ESCs to pins 16, 17, 18, 19\t(DEFAULT)");
	task++;
}
void Quadcopter::attach_esc(const int esc1, const int esc2, const int esc3, const int esc4) {
	fl_esc.attach(esc1);
	fr_esc.attach(esc2);
	bl_esc.attach(esc3);
	br_esc.attach(esc4);
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tAttached ESCs to pins ");
	Serial.print((String)esc1+", "+(String)esc2+", "+(String)esc3+", "+(String)esc4+"\n");
	task++;
}
void Quadcopter::init_bldc() {
	fl_esc.writeMicroseconds(duty);
	fr_esc.writeMicroseconds(duty);
	bl_esc.writeMicroseconds(duty);
	br_esc.writeMicroseconds(duty);
	Serial.print("[");
	Serial.print(task);
	Serial.print("]\tBLDCs initialized and caliberated.");
	task++;
}
void Quadcopter::update_lcd() {
	lcd.setCursor(1, 0);
	lcd.print("POT");
	lcd.setCursor(12, 0);
	lcd.print("PWM");
	lcd.setCursor(1, 1);
	lcd.print("      ");
	lcd.setCursor(0, 1);
	lcd.print(pot_val);
	lcd.setCursor(11, 1);
	lcd.print("      ");
	lcd.setCursor(11, 1);
	lcd.print(duty);
}
void Quadcopter::fly() {
	pot_val = analogRead(debug_pot);
	duty = map(pot_val, POT_MIN, POT_MAX, DUTY_MIN, DUTY_MAX);
	fl_esc.writeMicroseconds(duty);
	fr_esc.writeMicroseconds(duty);
	bl_esc.writeMicroseconds(duty);
	br_esc.writeMicroseconds(duty);
	update_lcd();
}
















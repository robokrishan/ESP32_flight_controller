/*
  Quadcopter.h - Library for ESP-32 based flight controller.
  Created by Harit Krishan, August 1, 2021.
  Released into the public domain.
*/

#ifndef Alpha_h
#define Alpha_h
#define POT_MIN 0
#define POT_MAX 4095
#define DUTY_MIN 1200
#define DUTY_MAX 2000
#include "Arduino.h"
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

class Alpha {
	public:
		Alpha();
		Alpha(int esc1, int esc2, int esc3, int esc4);
		void attachESC();
		void setESCPins(int pin1, int pin2, int pin3, int pin4);
		void setPOTPin(int pot);
		void setLCDAddress(int addr);
		void setLCDDimensions(int width, int height);
		int readDuty();
		int readPot();
		void beginLCD();
		void beginBLDC();
		void updateLCD();
		void fly();

	private:
		int fl_esc_pin;
		int fr_esc_pin;
		int bl_esc_pin;
		int br_esc_pin;
		Servo fl_esc;
		Servo fr_esc;
		Servo bl_esc;
		Servo br_esc;
		LiquidCrystal_I2C *lcd;
		int debug_pot;
		int task;
		int lcd_addr;
		uint16_t duty;
		int pot_val;
		int lcd_width, lcd_height;
};


#endif

/*
  Quadcopter.h - Library for ESP-32 based flight controller.
  Created by Harit Krishan, August 1, 2021.
  Released into the public domain.
*/

#ifndef Quadcopter_h
#define Quadcopter_h
#define POT_MIN 0
#define POT_MAX 4095
#define DUTY_MIN 1200
#define DUTY_MAX 2000
#include "Arduino.h"
#include <ESP32Servo.h>
#include <String>
#include <LiquidCrystal_I2C.h>

class Quadcopter {
	public:
		Quadcopter();
		Quadcopter(const int esc1, const int esc2, const int esc3, const int esc4);
		Quadcopter(const int esc1, const int esc2, const int esc3, const int esc4, const int pot);
		void init_lcd();
		void update_lcd();
		void attach_esc();
		void init_bldc();
		void fly();
		
	private:
		Servo fl_esc;
		Servo fr_esc;
		Servo bl_esc;
		Servo br_esc;
		LiquidCrystal_I2C *lcd;
		int debug_pot;
		int task;
		int lcd_addr;
		uint16_t duty;
};


#endif
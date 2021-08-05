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
#include <WiFi.h>
#include <HTTPClient.h>


class Alpha {
	public:
		// Constructors
		Alpha();
		Alpha(int esc1, int esc2, int esc3, int esc4);

		// ESC Configuration
		void attachESC();
		void setESCPins(int pin1, int pin2, int pin3, int pin4);
		void setPOTPin(int pot);
		void beginBLDC();
		void fly();

		// LCD Configuration
		void setLCDAddress(int addr);
		void setLCDDimensions(int width, int height);
		void beginLCD();
		void updateLCD();
		void updateLCDRC();

		// Web Server Configuration
		void setPOTIP(char* ip);
		void setSSID(char* ssid_in);
		void setPWD(char* pwd_in);
		void connect();
		String httpGETRequest(const char* serverName);
		void readPot();
		String readPotRC();

	private:
		// ESCs
		int fl_esc_pin;
		int fr_esc_pin;
		int bl_esc_pin;
		int br_esc_pin;
		Servo fl_esc;
		Servo fr_esc;
		Servo bl_esc;
		Servo br_esc;
		int debug_pot;
		uint16_t duty;
		int pot_val;
		String pot_val_rc;
		int task;

		// LCD Display
		LiquidCrystal_I2C *lcd;
		int lcd_width, lcd_height;
		int lcd_addr;

		// Wireless
		char* ssid;
		char* pwd;
		char* POT_SERVER;
};


#endif

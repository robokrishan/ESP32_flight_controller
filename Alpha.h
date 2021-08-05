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
		Alpha();
		Alpha(int esc1, int esc2, int esc3, int esc4);
		void attachESC();
		void setESCPins(int pin1, int pin2, int pin3, int pin4);
		void setPOTPin(int pot);
		void setLCDAddress(int addr);
		void setLCDDimensions(int width, int height);
		void setPOTIP(char* ip);
		void setSSID(char* ssid_in);
		void setPWD(char* pwd_in);
		int readDuty();
		String readPot();
		void beginLCD();
		void beginBLDC();
		void updateLCD();
		void updateLCDRC();
		String httpGETRequest(const char* serverName);
		void fly();
		void connect();

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

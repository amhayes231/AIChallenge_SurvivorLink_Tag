// --------------------------------------------------
//
// Code for control of ESP32 through MIT inventor app (Bluetooth). 
// device used for tests: ESP32-WROOM-32D
// 
// App on phone has three buttons:
// Button 1: 11 for ON and 10 for OFF
// Button 2: 21 for ON and 20 for OFF
// Button 3: 31 for ON and 30 for OFF
//
// Written by mo thunderz (last update: 20.4.2021)
//
// --------------------------------------------------

// this header is needed for Bluetooth Serial -> works ONLY on ESP32
#include "BluetoothSerial.h"
#include <Arduino.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// init Class:
BluetoothSerial ESP_BT; 

// init PINs: assign any pin on ESP32

int led_pin_1 = 15;
int led_pin_2 = 5;
int buz_pin_3 = 4;     

// Parameters for Bluetooth interface
int incoming;

void setup() {
  Serial.begin(19200);
  ESP_BT.begin("SurvivorLink_Tag"); //Name of your Bluetooth interface -> will show up on your phone
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode (led_pin_1, OUTPUT);
  pinMode (led_pin_2, OUTPUT);
  pinMode (buz_pin_3, OUTPUT);
}

void loop() {
  
  // -------------------- Receive Bluetooth signal ----------------------
  if (ESP_BT.available()) 
  {
    incoming = ESP_BT.read(); //Read what we receive 
    Serial.print("Incoming: "); Serial.println(incoming);
  }

  if (incoming == 200) {
    digitalWrite(led_pin_1, LOW);
    digitalWrite(led_pin_2, LOW);
    digitalWrite(buz_pin_3, LOW);
  }

  else if (incoming == 210) {
    digitalWrite(buz_pin_3, HIGH);
    delay(333);
    digitalWrite(buz_pin_3, LOW);
    delay(333);
    digitalWrite(led_pin_1, LOW);
    digitalWrite(led_pin_2, LOW);
  }

  else if (incoming == 220) {
    digitalWrite(led_pin_1, HIGH);
    digitalWrite(led_pin_2, HIGH);
    delay(333);
    digitalWrite(led_pin_1, LOW);
    digitalWrite(led_pin_2, LOW);
    delay(333);
    digitalWrite(buz_pin_3, LOW);
  }

  else if (incoming == 231) {
    digitalWrite(led_pin_1, HIGH);
    digitalWrite(led_pin_2, HIGH);
    digitalWrite(buz_pin_3, HIGH);
    delay(333);
    digitalWrite(led_pin_1, LOW);
    digitalWrite(led_pin_2, LOW);
    digitalWrite(buz_pin_3, LOW);
    delay(333);
  }
}
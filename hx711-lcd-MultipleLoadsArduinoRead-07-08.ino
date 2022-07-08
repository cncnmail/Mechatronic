/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 This example demonstrates basic scale output. See the calibration sketch to get the calibration_factor for your
 specific load cell setup.
 
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 
 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.

 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/
#include <LiquidCrystal_I2C.h>
#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define LOADCELL_DOUT_PIN  16
#define LOADCELL_SCK_PIN  17
#define calibration_factor -6000.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN2  18
#define LOADCELL_SCK_PIN2  19
#define calibration_factor2 -6000.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

HX711 scale;
HX711 scale2;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0


  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  scale2.set_scale(calibration_factor2); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale2.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
  lcd.begin();  
  lcd.backlight();
  lcd.print("Prop Test");
  lcd.setCursor(0,1);
  lcd.print("start");  
  delay(2000); 
}

float v;
float v2;
float vt;
void loop() {
  //Serial.print("Reading: ");
  v =  scale.get_units();
  v = v*100;

  v2 = scale2.get_units();
  v2 = v2*100;
  vt = (v+v2);
 Serial.print(v, 2); //scale.get_units() returns a float
 Serial.print("//");
 Serial.print(v2,2);
 Serial.println(""); //You can change this to kg but you'll need to refactor the calibration_factor
 Serial.print(vt,2);
  Serial.println("");
 Serial.println();
 //================================LCD code start here
 lcd.clear();// clear previous values from screen
  lcd.print("prop (gram)");
  lcd.setCursor(0,1);
  lcd.print("");
  lcd.setCursor(11,1);  
  lcd.print(vt);
 
  delay(200); 
}//when code is installed and wires connected correctly, the red LED on the esp32 should be blink regularly.

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//----- setup LCD i2C ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);     // Set the LCD address to 0x27 for a 16 chars and 2 line display
//----- setup Led and button ---
const int ledPin1 = 12;                  //led attached to this pin
const int buttonPin1 = 2; 
const int ledPin2 = 11;                  //led attached to this pin
const int buttonPin2 = 3;                //push button attached to this pin
int buttonState1 = LOW; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState1 = -1; //this variable tracks the state of the LED, negative if off, positive if on

long lastDebounceTime1 = 0;  // the last time the output pin was toggled
long debounceDelay1 = 500;    // the debounce time; increase if the output flickers

int buttonState2 = LOW; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState2 = -1; //this variable tracks the state of the LED, negative if off, positive if on

long lastDebounceTime2 = 0;  // the last time the output pin was toggled
long debounceDelay2 = 500; 

int temp_up = 0;
int temp_down = 0;
//----- setup Sensor -----------
int phao_up = 7;                        //This is the input of the upper sensor 
int phao_down = 8;                      //This is the input of the lower sensor
int val_up = 0;                         //This is the variable reading the status 
                                        // of the upper sensor 
int val_down = 0;                       //This is the variable reading the status
                                        // of the lower sensor 
int phao_state = 0;
int motor_A = 6;                        // motor(+)
int motor_B = 5;                        // motor(-)
void setup() {
//---------------------- initialize the LCD ---------------------------------
  lcd.init();
  lcd.clear();           
//-----Turn on the blacklight and print a message----
  lcd.backlight();
  lcd.setCursor(1,0);                   //Set cursor to character 2 on line 0
  lcd.print("Sensor Project!");
  lcd.setCursor(3,1);                   //Move cursor to character 2 on line 1
  lcd.print("AuTOrium");
  delay(2000);

//--------set the mode of the pins...--------------
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin2, INPUT);
//  attachInterrupt(0,buttonPressed,RISING);

//------------------- initialize the System setup ---------------------------
  Serial.begin(9600);
//  Serial.println("We are beginning to use Serial Monitor to indicate..");
//  Serial.println("..whether the sensor is working or not without using..");
//  Serial.println("..the motor right there");
  pinMode(phao_up, INPUT);                  // sets the digital pin 7 as input
  pinMode(phao_down, INPUT);                // sets the digital pin 7 as input
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT);
  temp_up = val_up;
  temp_down = val_down;
}


void loop() {
  
  CheckLed1();
  CheckLed2();
  val_up = digitalRead(phao_up);            // read the input pin
  val_down = digitalRead(phao_down);        // read the input pin

////---Checking time---

//  Serial.print(val_up);
//
//  Serial.print(val_down);
//
//  Serial.print(temp_up);
//
//  Serial.print(temp_down);  
//
//  Serial.println();  
//
  if(val_up == 0 && val_down == 1 && temp_up == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tank is FULL");
      lcd.setCursor(0,1);   
      lcd.print("press 1: ?");
      //digitalWrite(motorB,LOW);
      //digitalWrite(motorA,LOW);

   } else if(val_up == 1 && val_down == 0 && temp_down == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tank is EMPTY");;
      lcd.setCursor(0,1);   
      lcd.print("press 2: ?");
      //digitalWrite(motorB,LOW);
      //digitalWrite(motorA,LOW);

   } else if(val_up == 0 && val_down == 1 && temp_up == 1 && temp_down == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PUMP OUT");
      //digitalWrite(motorA,HIGH);
      //digitalWrite(motorB,LOW);
   } else if(val_up == 1 && val_down == 1 && temp_up == 1 && temp_down == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PUMP OUT");
      //digitalWrite(motorA,HIGH);
      //digitalWrite(motorB,LOW);
      
   } else if(val_down == 0 && val_up == 1 && temp_down == 1 && temp_up == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PUMP IN");
      //digitalWrite(motorB,HIGH);
      //digitalWrite(motorA,LOW);

   } else if(val_down == 1 && val_up == 1 && temp_down == 1 && temp_up == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PUMP IN");
      //digitalWrite(motorB,HIGH);
      //digitalWrite(motorA,LOW)
      
   } else if(temp_down == 1 && temp_up == 1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CHOOOSE 1 ONLY");
      //digitalWrite(motorA,LOW);
      //digitalWrite(motorB,LOW);
   } else if(val_down == 1 && val_up == 1 && temp_down == 0 && temp_up == 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("FILL MORE WATER");
      //digitalWrite(motorA,LOW);
      //digitalWrite(motorB,LOW);
   } else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ERROR");
      //digitalWrite(motorA,LOW);
      //digitalWrite(motorB,LOW);
   }



}// end of Void loop

void CheckLed1(){
    //sample the state of the button - is it pressed or not?
  buttonState1 = digitalRead(buttonPin1);

  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime1) > debounceDelay1) {

    //if the button has been pressed, lets toggle the LED from "off to on" or "on to off"
    if ( (buttonState1 == HIGH) && (ledState1 < 0) ) {

      digitalWrite(ledPin1, HIGH); //turn LED on
      temp_up = 1;
      ledState1 = -ledState1; //now the LED is on, we need to change the state
      lastDebounceTime1 = millis(); //set the current time
    }
    else if ( (buttonState1 == HIGH) && (ledState1 > 0) ) {

      digitalWrite(ledPin1, LOW); //turn LED off
      temp_up = 0;
      ledState1 = -ledState1; //now the LED is off, we need to change the state
      lastDebounceTime1 = millis(); //set the current time
    }
  }
}

void CheckLed2(){
      //sample the state of the button - is it pressed or not?
  buttonState2 = digitalRead(buttonPin2);
  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime2) > debounceDelay2) {

    //if the button has been pressed, lets toggle the LED from "off to on" or "on to off"
    if ( (buttonState2 == HIGH) && (ledState2 < 0) ) {

      digitalWrite(ledPin2, HIGH); //turn LED on
      temp_down = 1;
      ledState2 = -ledState2; //now the LED is on, we need to change the state
      lastDebounceTime2 = millis(); //set the current time
    }
    else if ( (buttonState2 == HIGH) && (ledState2 > 0) ) {

      digitalWrite(ledPin2, LOW); //turn LED off
      temp_down = 0;
      ledState2 = -ledState2; //now the LED is off, we need to change the state
      lastDebounceTime2 = millis(); //set the current time
    }
  }
}

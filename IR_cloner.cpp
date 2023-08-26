#include <LiquidCrystal.h>
#include <Arduino.h>
#include <IRremote.hpp> // IRremote version 4.2.0
LiquidCrystal lcd(2,3,4,5,6,7);//(rs, enable, d4, d5, d6, d7) //LED pins

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);//sets display as 16 bits long with 2 rows.
  IrReceiver.begin(13);//starts the infrared receiver on pin 13.
  pinMode(8, INPUT_PULLUP);//Emitter button on pin 8
  pinMode(9, INPUT_PULLUP);//reset button on pin 9 (pressing resets the recorded ir value
}
void loop() {
  delay(200);
  int btn1 = digitalRead(8); //checks if button pressed
  int btn2 = digitalRead(9); //checks if button pressed
  if(btn1 == 0) { //if emit button pressed do this
  IrSender.begin(12); //Starts IR emitter only when button pressed because otherwise has interference
  IrSender.sendNEC(IrReceiver.decodedIRData.address, IrReceiver.decodedIRData.command, 1); //Replays the previously recorded Infrared signal
  lcd.print("NEC sent!"); //Indicatest that signal was sent
  delay(200);
  lcd.clear();
  IrReceiver.resume(); 
}
 if(btn2 == 0) { //if emit button pressed resets IR value
  void(* resetFunc) (void) = 0;
  resetFunc();
 }
if (IrReceiver.decode()){ //if IR receiver gets value
  lcd.clear();
  IrReceiver.printIRResultShort(&Serial);//prints IR reciever collected info to serial
  IrReceiver.printIRSendUsage(&Serial);//shows usage for replaying data in serial
  Serial.println(IrReceiver.decodedIRData.decodedRawData);
  lcd.print("A:");lcd.print(IrReceiver.decodedIRData.address); //Gets IR address
  lcd.print("|C:");lcd.print(IrReceiver.decodedIRData.command); //Gets IR command
  lcd.print("|P:");lcd.print(IrReceiver.decodedIRData.protocol); //Gets IR protocol
  delay(200);
  lcd.clear();
  IrReceiver.resume();
  }
}

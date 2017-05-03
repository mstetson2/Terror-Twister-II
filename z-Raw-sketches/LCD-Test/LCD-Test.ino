#include <Arduino.h>

//For LCD:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Ignore:
struct lcdData {
    char line1[20];
    char line2[20];
    char line3[20];
    char line4[20];
};

//Define the LCD Screen, the LCD is named: lcd
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);


void setup() {
    Serial.begin(9600);

    //LCD Initialize
    lcd.begin(20,4);
    lcd.setBacklightPin(3, POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home();

}

void loop() {

    Serial.println("Printing 1:");

    lcd.setCursor(0,0);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,0);
    lcd.print("LINE 1 TEXT");     //put what you want for line 1

    lcd.setCursor(0,1);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,1);
    lcd.print("LINE 2 TEXT");     //put what you want for line 2

    lcd.setCursor(0,2);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,2);
    lcd.print("LINE 3 TEXT");     //put what you want for line 3

    lcd.setCursor(0,3);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,3);
    lcd.print("LINE 4 TEXT");     //put what you want for line 4

    delay(5000);    //delay 5 seconds

    Serial.println("Printing 2:");

    lcd.setCursor(0,0);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,0);
    lcd.print("ATTENTION:");     //put what you want for line 1

    lcd.setCursor(0,1);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,1);
    lcd.print("I LOVE PENIS");     //put what you want for line 2

    lcd.setCursor(0,2);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,2);
    lcd.print("WHITE POWER");     //put what you want for line 3

    lcd.setCursor(0,3);
    lcd.print("                    ");  //clear line
    lcd.setCursor(0,3);
    lcd.print("TRUMP 2020");     //put what you want for line 4

    delay(5000);    //delay 5 seconds
}

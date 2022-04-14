#include <LiquidCrystal_I2C.h>

#define LUX A0

volatile unsigned int digital_lux = 0;
volatile unsigned long globalTimeBufferMillis = 0;

void setup() {
	Serial.begin(9600);
	
	LiquidCrystal_I2C LCD (0x27, 20, 4);
	LCD.init();
    LCD.backlight();
    
	pinMode(LUX, INPUT);
}

void loop() {
	showLuxOnLcd();
}

// void showLuxOnLcd() {

// 	show

// }

void improvedDelay(unsigned int waitTime) {
    
    globalTimeBufferMillis = millis();
    boolean cooldownState = true;

    while (cooldownState) {
        if (millis() - globalTimeBufferMillis > waitTime) 
            cooldownState = false;
    }

}
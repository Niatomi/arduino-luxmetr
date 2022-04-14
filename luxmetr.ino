#include <LiquidCrystal_I2C.h>

#define LUX A0

volatile unsigned int analog_lux = 0;
volatile unsigned long globalTimeBufferMillis = 0;

LiquidCrystal_I2C lcd (0x27, 20, 4);

void setup() {
	Serial.begin(9600);
	
	lcd.init();
    lcd.backlight();
    
	pinMode(LUX, INPUT);
    lcd.clear();
    
}

void loop() {
    analog_lux = analogRead(LUX);
    showLuxOnLcd();
}

void showLuxOnLcd() {

    showHeadInfo();

	showValueByExpFunc();

    showValueByLogFunc();

    showValueByLinearFunc();

    improvedDelay(100);

    lcd.clear();

}

void showHeadInfo() {
    lcd.setCursor(0, 0);
    lcd.print("sensor value: ");
    lcd.print(analog_lux);
}

void showValueByExpFunc() {
    lcd.setCursor(0, 1);
    lcd.print("exp: ");

    float expLuxValue = 0.1652*exp(0.0095*analog_lux);
    lcd.print(expLuxValue);
}

void showValueByLogFunc() {
    lcd.setCursor(0, 2);
    lcd.print("ln: ");

    float lnLuxValue = 2292.1*log(analog_lux)-14969;
    lcd.print(lnLuxValue);
}

void showValueByLinearFunc() {
    lcd.setCursor(0, 3);
    lcd.print("linear: ");

    float linearLuxValue = 2.9114*analog_lux - 1978.5;
    lcd.print(linearLuxValue);
}

void improvedDelay(unsigned int waitTime) {
    globalTimeBufferMillis = millis();
    boolean cooldownState = true;

    while (cooldownState) {
        if (millis() - globalTimeBufferMillis > waitTime) 
            cooldownState = false;
    }
}
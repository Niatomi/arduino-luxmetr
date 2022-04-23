#include <LiquidCrystal_I2C.h>

#define LUX A0

volatile unsigned int analog_lux = 0;
volatile unsigned long globalTimeBufferMillis = 0;

LiquidCrystal_I2C lcd (0x27, 16, 2);

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

    // showHeadInfo();

	showValueByExpFunc();

    // showValueByLogFunc();

    // showValueByLinearFunc();

    improvedDelay(50);

    lcd.clear();

}

void showHeadInfo() {
    lcd.setCursor(0, 0);
    lcd.print("sensor value: ");
    lcd.print(analog_lux);
}

void showValueByExpFunc() {
    float expLuxValue;

    if (analog_lux <= 600) {
        expLuxValue = 0.9*exp(0.0073*analog_lux);
    } else if (analog_lux > 600 && analog_lux <= 697) {
        expLuxValue = 0*459*analog_lux - 200;
    } else if (analog_lux >= 698 && analog_lux <=  783) {
        expLuxValue = 0.3016*analog_lux - 87.258;
    } else if (analog_lux >= 784 && analog_lux <= 831) {
        expLuxValue = 2.1798*analog_lux - 1568.1;
    } else if (analog_lux >= 832 && analog_lux <= 848) {
        expLuxValue = 4.3614*analog_lux - 3409.6;
    } else if (analog_lux >= 849 && analog_lux <= 869) {
        expLuxValue = 5.6583 - 4529.1;
    } else if (analog_lux >= 870 && analog_lux <= 880) {
        expLuxValue = 5.6583*analog_lux - 4529.1;
    } else {
        expLuxValue = 500;
    }

    lcd.setCursor(0, 0);
    lcd.print("lux: ");

    lcd.print(expLuxValue);
}

void showValueByLogFunc() {
    lcd.setCursor(0, 1);
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
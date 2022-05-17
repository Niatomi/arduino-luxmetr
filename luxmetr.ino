#define LUX A0

volatile unsigned int analog_lux = 0;
volatile unsigned long globalTimeBufferMillis = 0;

/*
* Запуск serial порта
* Инициализируем ногу для люксметра
*/
void setup() {
    Serial.begin(115200);
    pinMode(LUX, INPUT);
}

/*
* Выводим значение люксметра и частоту света
*/
void loop() {
    Serial.print(getFrequency());
    Serial.println(" Hz");
    Serial.print(getLux());
    Serial.println(" лк");
    Serial.println();
}

/*
* Высчитваем люксы по высчитанному полиному в разных диапазонах
* @return значение в люксах 
*/
float getLux() {
    analog_lux = analogRead(LUX);

    float lux_value = 0;

    //0..50
    if (analog_lux <= 85) {
        lux_value = 0.6965 * analog_lux - 10.754;
    //50..200
    } else if (analog_lux > 85 && analog_lux <= 226) {
        lux_value = 1.0591 * analog_lux - 48.089 ;
    //200..300
    } else if (analog_lux > 226 && analog_lux <= 287) {
        lux_value = 1.8765 * analog_lux - 236.17;
    //300..400
    } else if (analog_lux > 287 && analog_lux <= 335) {
        lux_value = 2.1542 * analog_lux - 322.5;
    //400..1000
    } else if (analog_lux > 335 && analog_lux <= 564) {
        lux_value = 2.5933 * analog_lux - 481.88;
    //1000..2000
    } else if (analog_lux > 564 && analog_lux <= 693) {
        lux_value = 59.721*exp(0.005*analog_lux);
    } else {
        lux_value = 1;
    }

    return lux_value;

}

/*
* Высчитываем значение частоты
* Находим время двух амплитудных значений, 1000/(разница их появлений) = частота в герцах
* @return частота света
*/
double getFrequency() {

    unsigned int time[2] = {-1, -1};
    double hz = 0;
    int i = 0;

    float avarageSeries = 0;
    float avarage = 0;
    unsigned int getLuxCounter = 0;

    getLuxCounter++;
    float buffer = 0;
    avarageSeries += buffer;

    boolean permissionOnWrite = true;

    float step = 0;

    while (time[1] == -1) {
        // Serial.println(getLux());
        if (getLux() >= 40 && permissionOnWrite) {
            permissionOnWrite = false;
            time[i] = millis();
            i++;
        }

        if (getLux() <= 20) {
            permissionOnWrite = true;
        }
    }

    unsigned int mill = time[1] - time[0] + 10;
    hz = (double)1000 /(double) mill;
    return hz;
}
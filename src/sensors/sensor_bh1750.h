#include <Wire.h>
#include <ErriezBH1750.h>

BH1750 lux_sensor();
bool bh1750IsConnected = false;
void sensor_setup()
{
    //  Wire.begin(); // Do i need to do this? 
    int retrycount = 0;
    while (lux_sensor.begin() != true && retrycount < 5)
    {
        retrycount++;
        delay(1000);
    }
    if(retrycount == 5) {
        Serial.println("\n\rFailed to configure BH1750 sensor");
    } else {
        Serial.print("\n\rConnected to BH1750: ");
        Serial.println(lux_sensor.begin(ModeContinuous, ResolutionHigh));
        Serial.println(lux_sensor.startConversion());
        bh1750IsConnected = true;
    }

}

bool bh1750SensorIsConnected() {
    return bh1750IsConnected;
}

uint16_t getLux() {
    uint16_t lux;
    if(lux_sensor.isConversionCompleted()) {
        lux = lux_sensor.read();
        return lux;
    }
}
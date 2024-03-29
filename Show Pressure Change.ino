#include <Dps310.h>

Dps310 Dps310PressureSensor = Dps310();

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Dps310PressureSensor.begin(Wire);
  Serial.println("Init complete!");
}

void loop()
{
  float pressure;
  uint8_t oversampling = 7;
  int16_t ret;
  Serial.println();

  ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);

  if (ret != 0)
  {
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print(" Pascal");
    
  }
}

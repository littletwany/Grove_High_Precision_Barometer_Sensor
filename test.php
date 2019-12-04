#include <Dps310.h>

Dps310 Dps310PressureSensor = Dps310();

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Dps310PressureSensor.begin(Wire);
  Serial.println("Init complete!");
}

void loop()
{
  float pressure1[10];
  float pressure2[10];
  uint8_t oversampling = 7;
  int16_t ret;
  Serial.println();
  int i;
  int k=10;
  int value1;
  int value2;
  
  ret = Dps310PressureSensor.measurePressureOnce(pressure1[0], oversampling);
  int sum1=pressure1[0];
  for(i=1;i<9;i++)
{
  ret = Dps310PressureSensor.measurePressureOnce(pressure1[i], oversampling);
  if (pressure1[i]-pressure1[i-1]< 5)
   {sum1+=pressure1[i];}
  else
   {k-=1;}
}
  value1=sum1/k;
  delay(100);

  ret = Dps310PressureSensor.measurePressureOnce(pressure2[0], oversampling);
  int sum2 =pressure2[0];
   for(i=1;i<9;i++)
{
  ret = Dps310PressureSensor.measurePressureOnce(pressure2[i], oversampling);
  if (pressure2[i]-pressure2[i-1]< 5)
  sum2+=pressure2[i];
  else
  k-=1;
}
  value2=sum2/k;
  
  if (ret != 0)
  {
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else if(value2-value1>4)
  {
    Serial.print("You fell down. Do you need help?");
    delay(5000);
   }
  else  
    Serial.print("It's ok!");
}

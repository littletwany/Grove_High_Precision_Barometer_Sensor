/**
 * The MIT License (MIT)
 * 
 * Author: Hongtai Liu (lht856@foxmail.com)
 * 
 * Copyright (C) 2019  Seeed Technology Co.,Ltd. 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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
  float Detection_array[10];
  uint8_t oversampling = 7;
  int16_t ret;
  int i;
  int size = 10;
  int state1;
  int state2;
/*In the following two cycles, the pressure state at the pre and post time was detected respectively.
  The sampling quantity was 10. The values with large deviation were removed, and the average value was calculated.*/
      ret = Dps310PressureSensor.measurePressureOnce(Detection_array[0], oversampling);
      state1 = Detection_array[0];
 for (i = 1; i < 9; i++)
  {
     ret = Dps310PressureSensor.measurePressureOnce(Detection_array[i], oversampling);
       if (Detection_array[i] - Detection_array[i - 1] < 5)
      {
        state1 += Detection_array[i];
      }
      else
      {
        size -= 1;
      }
  } 
 state1 = state1 / size;
 delay(100);


      ret = Dps310PressureSensor.measurePressureOnce(Detection_array[0], oversampling);
      state2 = Detection_array[0];
 for (i = 1; i < 9; i++)
  {
      ret = Dps310PressureSensor.measurePressureOnce(Detection_array[i], oversampling);
      if (Detection_array[i] - Detection_array[i - 1] < 5)
      {
        state2 += Detection_array[i];
      }
      else
      {
        size -= 1;
      }
  }
  state2 = state2 / size;
  
 if (ret != 0)
   {
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
   }
/*Calculate the difference in air pressure to determine if you fall*/
    else if (state2 - state1 > 4)
     {
      Serial.println("You fell down. Do you need help?");
      delay(5000);
     }
    else
      Serial.println("It's ok!");
}

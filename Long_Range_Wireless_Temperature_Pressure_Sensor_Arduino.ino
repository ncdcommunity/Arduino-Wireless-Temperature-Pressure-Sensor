///this code is written and tested for ncd.io IoT Long Range Wireless Pressure and Temperature Sensor with arduino due
///sensor data structure can be found here https://ncd.io/long-range-iot-wireless-temperature-barometric-pressure-sensor-product-manual/
/// sensor can be found here https://store.ncd.io/product/long-range-iot-wireless-temperature-barometric-pressure-sensor/

  uint8_t data[36];
  int k = 10;
  int i;
void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("ncd.io IoT Arduino Wireless Pressure and Temperature Sensor");
}

void loop()
{
  
  if (Serial1.available())
  {
    data[0] = Serial1.read();
    delay(k);
   if(data[0]==0x7E)
    {
    while (!Serial1.available());
    for ( i = 1; i< 36; i++)
      {
      data[i] = Serial1.read();
      delay(1);
      }
    if(data[15]==0x7F)  /////// to check if the recive data is correct
      {
  if(data[22]==0x06)  //////// make sure the sensor type is correct
  {
  int cTemp = ((((data[24]) * 256) + data[25]));
  int16_t abs_pressure = ((((uint16_t)(data[26])<<8)| data[27])*0.001);
  int rlt_pressure = ((((data[28]) * 256) + data[29])*0.001);
  int16_t delta_alt = ((((uint16_t)(data[30])<<8)| data[31])*0.01);
  float battery = ((data[18] * 256) + data[19]);
  float voltage = 0.00322 * battery;
  Serial.print("Sensor Number  ");
  Serial.println(data[16]);
  Serial.print("Sensor Type  ");
  Serial.println(data[22]);
  Serial.print("Firmware Version  ");
  Serial.println(data[17]);
  Serial.print("Temperature in Celsius :");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Absolute Pressure :");
  Serial.println(abs_pressure);
  Serial.print(" mbar");
  Serial.print("Relative Pressure :");
  Serial.println(rlt_pressure);
  Serial.print(" mbar");
  Serial.print("Delta Altitude :");
  Serial.println(delta_alt);
  Serial.print(" meter");
  Serial.print("ADC value:");
  Serial.println(battery);
  Serial.print("Battery Voltage:");
  Serial.print(voltage);
  Serial.println("\n");
  if (voltage < 1)
          {
    Serial.println("Time to Replace The Battery");
          }
  
        }
      }
else
{
      for ( i = 0; i< 36; i++)
    {
      Serial.print(data[i]);
      Serial.print(" , ");
      delay(1);
    }
}
    }
  }
 
}

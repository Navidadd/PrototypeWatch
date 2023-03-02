#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Time.h>
#include <RTClib.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

DateTime oldtime;
RTC_DS3231 rtc;

#define SETUP_TIME_NO

const int batterypin = 0;
void setup()
{
  Serial.begin(9600);
  analogReference(DEFAULT);
  rtc.begin();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextColor(WHITE);

#ifdef SETUP_TIME
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
#endif

  oldtime = rtc.now(); 
}

void loop(){
    pantalla1();
}


void pantalla1()
{
    int num = analogRead(batterypin);
    
    int percent;
    
    int old_rang_min = 0;
    int old_rang_max = 646;
    int new_range_min = 0;
    int new_rang_max = 100;
    percent = ((num - old_rang_min) * (new_rang_max - new_range_min)) / (old_rang_max - old_rang_min) + new_range_min;

    DateTime fecha = rtc.now();
    DateTime newTime;
    
    newTime = rtc.now();
    if ( newTime >= oldtime+1)
    {
        display.clearDisplay();
        oldtime = rtc.now();
        
          display.setCursor(30, 28); // X ancho, Y alto
          display.setTextSize(2.5);
  
          print2digits(fecha.hour());
          display.write(':');
          print2digits(fecha.minute());
          display.setTextSize(1);
          display.write(':');
          print2digits(fecha.second());

          display.setCursor(1, 1); // X ancho, Y alto
          display.setTextSize(1.3);
          display.print(fecha.day());
          display.write('/');
          display.print(fecha.month());
          display.write('/');
          display.print(fecha.year());

          //DEBUG
          Serial.println(percent);
          Serial.println(num);
          //DEBUG
         display.setCursor(96, 1);// X ancho, Y alto
         display.print(num);
         display.println("%");

         display.display();
         display.clearDisplay();
 
       }
         
} 

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    display.write('0');
  }
  display.print(number);
}
/*void pantalla2()
{
   float TEMPERATURA;
   float HUMEDAD;
   display.clearDisplay();
   display.setTextSize(1.7);
   display.setCursor(1, 10); // X ancho, Y alto
   
   TEMPERATURA = bmp.readTemperature();
   //HUMEDAD = dht.readHumidity();

   Serial.print("Temperatura: ");
   Serial.println(TEMPERATURA);
   
   display.print("Temperatura: ");
   display.print(TEMPERATURA);
   display.println(" *C");
   
   display.setCursor(1, 40); // X ancho, Y alto
   display.print("Humedad: ");
   display.println(HUMEDAD);
   
   delay(1000);
   display.display();
   display.clearDisplay();
}*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
LiquidCrystal_I2C lcd(32,16,2); //indico que la pantalla tiene 2 lineas y cada una 16 caracteres
int pinsensor = A3; //Higrometro
int h;
float t = 0.0;
int transitor = 0;
//int motor = 7;
int valor_map;
int pintemp = 1;//DHT22
int lecturatemp = 0;
int ledrojo=2;
int led verde=3;
int ledama=4;
int ledver2=5

void setup()
{
  pinMode(motor,OUTPUT);
  pinMode(ledrojo,OUTPUT);
  pinMode(ledama,OUTPUT);
  pinMode(ledver2,OUTPUT);
  pinMode(ledverde,OUTPUT);
   // inicializo la pantalla LCD
   lcd.init();
   // Prendo la luz de la pantalla LCD
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("C.P.D.E.G");
   delay(1500);
}

void loop()
{ 
  //temp
   lcd.backlight();
   lcd.setCursor(0,0);
   t = dht.readTemperature();//en la variable t guardo la temperatura del ambiente
   //lcd.print("Temperatura: ");
   lecturatemp=analogRead(0);
   delay(2000); 
   if (t < 30)
   lcd.print("T:Inv frío");
   if (t >=30&&t<=32)
   lcd.print("T:Inv Ok");
   if (t >32) 
   lcd.print("T:Inv caliente");

}
 
  
  //humedad
  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  h=analogRead(pinsensor);
  valor_map=map(h,0,876,0,100);
  if (h < 500){
    lcd.print(valor_map);
    digitalWrite(ledver2, HIGH);
  }
  if (h >= 500){
    digitalWrite(ledver2, LOW);
    lcd.print(valor_map);
}
  lcd.print("%");
}
    

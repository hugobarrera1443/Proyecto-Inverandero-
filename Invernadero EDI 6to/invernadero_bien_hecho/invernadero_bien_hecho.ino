#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
LiquidCrystal_I2C lcd(0x27,16,2); //indico que la pantalla tiene 2 lineas y cada una 16 caracteres
int pinsensor = A3; //Higrometro
int h;
float t;
int valor_map;
const int DHTPin = 7; 
int lecturatemp = 0;
int ledrojo=2;
int ledverde=3;
int ledama=4;
int ledver2=5;
int bomb=8;
int peltier=13;
int vent1=12;
int tira_led=11;
int sensorLDR=A2;
int valor_sensorLDR;
int valormap_luz;

// genero el objeto DHT(el sensor) para poder tomar los datos de temperatura y humedad  
DHT dht(DHTPin, DHTTYPE);
void setup(){
     Serial.begin(9600);
     dht.begin();//Iniciar el sensor dht
     pinMode(ledrojo,OUTPUT);
     pinMode(ledama,OUTPUT);
     pinMode(ledver2,OUTPUT);
     pinMode(ledverde,OUTPUT);
     pinMode(vent1, OUTPUT);
     pinMode(bomb,OUTPUT);
     pinMode(peltier,OUTPUT);
     pinMode(tira_led,OUTPUT);
     // inicializo la pantalla LCD
     lcd.init();
     // Prendo la luz de la pantalla LCD
     lcd.backlight();
     lcd.setCursor(0,0);
     lcd.print("C.P.D.E.G");
     delay(1500);
}

void loop(){ 
     //TEMPERATURA 
     lcd.setCursor(0,1);
     t =dht.readTemperature();//en la variable t guardo la temperatura del ambiente
     lecturatemp=analogRead(0);
     digitalWrite(ledverde, LOW);
     digitalWrite(ledrojo, LOW);
     digitalWrite(ledama,LOW);
     //muestra en la pantalla un mensaje dependiendo la temperatura que detecta el DHT22
     if (t < 27){
        lcd.print("T:Inv frío");
        digitalWrite(ledverde, HIGH);
       }
     if (t >=27&&t<=32){
        lcd.print("T:Inv Ok");
        digitalWrite(ledama, HIGH);
   }
   if (t >32){
      lcd.print("T:Inv caliente");
      digitalWrite(ledrojo, HIGH);
   }
   lcd.setCursor(0,0);
   lcd.print("T:");
   lcd.print(t);
  //humedad
  lcd.print(" H:");
  h=analogRead(pinsensor);
  valor_map=map(h,1023,135,0,100);
  //muestra en la pantalla un mensaje dependiendo la humedad que detecta el higrometro
  if (h < 500){
    lcd.print(valor_map);
    digitalWrite(ledver2, HIGH);
  }
  if (h >= 500){
    digitalWrite(ledver2, LOW);
    lcd.print(valor_map);
}
  lcd.print("%");
  delay(2000);

 //BOMBA
  h=analogRead(pinsensor);
  valor_map=map(h,1023,135,0,100);
  //prende o apaga la bomba dependiendo de la humedad detectada por el higrometro
  if (h < 500){
    lcd.print(valor_map);
    digitalWrite(bomb, HIGH);
  }
  if (h >= 500){
    digitalWrite(bomb, LOW);
    lcd.print(valor_map);
  }
//peltier
 t =dht.readTemperature();//en la variable t guardo la temperatura del ambiente
     lecturatemp=analogRead(0);
     //prende la celda de peltier y apaga ventilador si es que la temperatura es menor a 27
     if (t < 27){
        digitalWrite(peltier, HIGH);
        digitalWrite(vent1, LOW);
     } else {
        //apaga la celda de peltier y prende ventilador si es que la temperatura es menor a 27
        digitalWrite(peltier, LOW);
        digitalWrite(vent1, HIGH);
  
     }
//LDR
valor_sensorLDR=analogRead(sensorLDR);
valormap_luz=map(valor_sensorLDR, 0,1023,0,255);
analogWrite(tira_led,valormap_luz);
  
}

    
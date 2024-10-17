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
  lcd.setCursor(0,0);
  t =dht.readTemperature();//en la variable t guardo la temperatura del ambiente
  Serial.print("Temperatura Ambiente: ");
  Serial.println(t);
  digitalWrite(ledverde, LOW);
  digitalWrite(ledrojo, LOW);
  digitalWrite(ledama,LOW);
  //temperatura
  lcd.print("T:");
  lcd.print(t);
  //humedad
  lcd.print(" H:");
  h=analogRead(pinsensor);
  valor_map=map(h,1023,135,0,100);
  lcd.print(valor_map);
  Serial.print("Humedad en Tierra: ");
  Serial.println(valor_map);
  lcd.print("%");
  lcd.setCursor(0,1);
  //muestra en la pantalla un mensaje dependiendo la temperatura que detecta el DHT22
     if (t < 27){
        lcd.print("T:Inv frio");
        digitalWrite(ledverde, HIGH);
        digitalWrite(peltier, HIGH);
        digitalWrite(vent1, LOW);
       }
     if (t >=27&&t<=32){
        lcd.print("T:Inv Ok");
        digitalWrite(ledama, HIGH);
        digitalWrite(peltier, LOW);
        digitalWrite(vent1, LOW);
   }
   if (t >32){
      lcd.print("T:Inv caliente");
      digitalWrite(ledrojo, HIGH);
      digitalWrite(peltier, LOW);
      digitalWrite(vent1, HIGH);
   }
  //prende o apaga la bomba dependiendo de la humedad detectada por el higrometro
  if (valor_map < 50){
    digitalWrite(bomb, HIGH);
    digitalWrite(ledver2, HIGH);
    Serial.println("Bomba Activada");
  }
  if (valor_map >= 50){
    digitalWrite(bomb, LOW);
    digitalWrite(ledver2, LOW);
    Serial.println("Bomba Desactivada");
  }

//peltier
t =dht.readTemperature();//en la variable t guardo la temperatura del ambiente
//prende la celda de peltier y apaga ventilador si es que la temperatura es menor a 27
     if (t < 27){
        digitalWrite(peltier, HIGH);
        digitalWrite(vent1, LOW);
        Serial.print("Calentando Invernadero");
     } else {
        //apaga la celda de peltier y prende ventilador si es que la temperatura es menor a 27
        digitalWrite(peltier, LOW);
        digitalWrite(vent1, HIGH);
        Serial.print("Enfriando el Invernadero");
     }
//LDR
valor_sensorLDR=analogRead(sensorLDR);
valormap_luz=map(valor_sensorLDR, 0,1023,0,255);
analogWrite(tira_led,valormap_luz);
Serial.print("Nivel Artificial de Iluminación");
Serial.println(valormap_luz);
delay(2000);
}

    

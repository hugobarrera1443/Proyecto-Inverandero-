#include <Wire.h>               // Libreria secundaria para hacer andar la pantalla LCD 
#include <DHT.h>                // Libreria para pode utilizar el Sensor de Temperatura 
#include <LiquidCrystal_I2C.h>  // Libreria central para utilizar la pantalla LCD  
#define DHTTYPE DHT22           // declaro el sensor que voy a usar DHT 22  (AM2302), AM2321
// Declaración de variables  //
float h;                        // Variable del tipo float para almacenar la humedad ambiente
float t;                        // Variable del tipo float para almacenar la Temperatura ambiente
const int DHTPin = 7;           // variable del tipo entera para guardar el pin donde conecto el sensor DHT
int ledrojo=2;                  // variable del tipo entera para guardar el pin donde conecto el led rojo, que voy a usar para indicar que el invernadero esta muy caliente
int ledverde=3;                 // variable del tipo entera para guardar el pin donde conecto el led verde, que voy a usar para indicar que el invernadero esta muy frío
int ledamarillo=4;              // variable del tipo entera para guardar el pin donde conecto el led rojo, que voy a usar para indicar que el invernadero esta en la temperatura correcta
int peltier=13;                 // variable del tipo entera para guardar el pin donde conecto la celda de peltier para calentar el invernadero
int ventilador=12;              // variable del tipo entera para guardar el pin donde conecto el ventilador para enfriar el invernadero

LiquidCrystal_I2C lcd(0x27,16,2);  // Creo la pantalla e indico que la pantalla tiene 2 lineas y cada una 16 caracteres
DHT dht(DHTPin, DHTTYPE);          // genero el objeto DHT(el sensor) para poder tomar los datos de temperatura y humedad  
void setup(){
     dht.begin();                  // Iniciar el sensor dht
     pinMode(ledrojo,OUTPUT);      // declaro el puerto como salida para manejar el led     
     pinMode(ledamarillo,OUTPUT);  // declaro el puerto como salida para manejar el led
     pinMode(ledverde,OUTPUT);     // declaro el puerto como salida para manejar el led
     pinMode(peltier,OUTPUT);      // declaro el puerto como salida para poder prender o apagar la celda de peltier 
     pinMode(ventilador,OUTPUT);   // declaro el puerto como salida para poder prender o apagar los ventiladores para poder enfriar el invernadero
     lcd.init();                   // inicializo la pantalla LCD
     lcd.backlight();              // Prendo la luz de la pantalla LCD
     lcd.setCursor(0,0);           // posiciono el cursor de escritura en el primer renglón y la primera posición
     lcd.print("  C.P.D.E.G");       // Imprimo en la pantalla las iniciales del colegio
     delay(4000);
}

void loop(){ 
     // RUTINA PARA MOSTAR Y COMPARAR LA TEMPERATURA
     lcd.clear();                   // Limpio siempre la pantalla
     t =dht.readTemperature();      // en la variable t guardo la temperatura del ambiente
     lcd.setCursor(0,0);            // posiciono el cursor en el primier renglon y primera posición 
     lcd.print("T:");               // imprimo en la LCD la T para hacer referencia TEMPERATURA  
     lcd.print(t);                  // imprimo la temperatura que se guardo en la variable t 
     lcd.print("G");                // imprimo G para hacer referencia a GRADOS, la LCD no puede imprimir de manera nativa °
     lcd.setCursor(9,0);            // posiciono el cursor en la posición 9 y primer renglon para escrivir el estado de la temperatura en el invernadero
     digitalWrite(ledverde, LOW);   // apago el led verde
     digitalWrite(ledrojo, LOW);    // apago el led rojo
     digitalWrite(ledamarillo,LOW); // apago el led amarillo

     //muestra en la pantalla un mensaje dependiendo la temperatura que detecta el DHT22
     if (t < 27){
        lcd.print("FRIO");             // imprimo que el invernadero está frío
        digitalWrite(ledverde, HIGH);  // prendo el led verde
        digitalWrite(peltier, HIGH);   // el invernadero está frio, prendo la celda de peltier
        digitalWrite(ventilador, LOW); // apago el ventilador
       }
     if (t >=27&&t<=32){
        
        lcd.print("TEMP Ok");            // imprimo que el invernadero está a temperatura optima
        digitalWrite(ledamarillo, HIGH); // prendo el led amarillo
        digitalWrite(peltier, LOW);      // el invernadero está en temp ok no prendo la celda
        digitalWrite(ventilador, LOW);   // el invernadero está en temp ok no prendo el ventilador
   }
   if (t >32){
      lcd.print("CALOR");              // imprimo que el invernadero está caliente
      digitalWrite(ledrojo, HIGH);     // prendo el led rojo
      digitalWrite(peltier, LOW);      // el invernadero está muy caliente apago la celda de peltier
      digitalWrite(ventilador, HIGH);  // el invernadero está muy caliente prendo los ventiladores para enfriarlo
   }
   
  delay(2000);
}
/* este simulador no cuenta con transistores, celdas de peltier y ventiladores.
   por eso resuelvo el tema con un diodo led celeste para el ventilador y con un led 
   blanco para la celda de peltier, en el momento de armar el circuito hay que reemplazarlos por el 
   componente real, en cuanto al programa queda igual.
*/   
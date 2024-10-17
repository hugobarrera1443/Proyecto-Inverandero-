#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int sensorPin = A3;
int bomba=8;
int humedad;
int valor_map_hum;

// genero el objeto Liquidcrystal(pantalla LCD) para poder mostrar información
LiquidCrystal_I2C lcd(34,16,2); //indico que la pantalla tiene 2 lineas y cada una 16 caracteres
//caracteres para representar, que ademas está en la dirección 0x3f de la memoria del arduino
//LiquidCrystal_I2C lcd(0x27,16,2);esta es la línea que tiene que ir en la realizad

void setup() {
     pinMode(bomba,OUTPUT);        // declaro el puerto como salida para poder prender o apagar los ventiladores para poder enfriar el invernadero
     lcd.init();                   // inicializo la pantalla LCD
     lcd.backlight();              // Prendo la luz de la pantalla LCD
     lcd.setCursor(0,0);           // posiciono el cursor de escritura en el primer renglón y la primera posición
     lcd.print("  C.P.D.E.G");     // Imprimo en la pantalla las iniciales del colegio
     delay(4000);       
     digitalWrite(bomba, LOW);     // me aseguro de tener apagada la bomba     
}
void loop() {
   
   humedad = analogRead(sensorPin);          // levanto la medición del igrómetro por la entrada analógica A3 del arduino, recordar que esta boca va a levantar valores enteros del 0 al 1023 en teoría
   valor_map_hum=map(humedad,0,876,0,100);   // tengo que convertir los valores del higrómetro a porcentajes, es decir del 0 al 100% para ello uso la función map, fijense que no utilizo de 0 a 1023, el sensor para tierra seca levanta 0 y para tierra muy mojada como máximo levante 876 
   lcd.setCursor(0,1);                       // posiciono el puntero en la posición 0 renglon 1 para escribir la humedad en tierra 
   lcd.print(valor_map_hum);
   lcd.print("%");
  if(valor_map_hum < 50){                    // si la humedad en tierra es menor a 50 tengo el invernadero seco y debo prender la bomba  
    lcd.setCursor(5,1);
    digitalWrite(bomba, HIGH);               // prendo la bomba
    lcd.print(" Inv Seco");                  // indico en pantalla que el invernadero está seco 
  }
  else{                                      // si entro por acá es porque tengo humedo el invernadero y lo muestro en pantalla y apago la bomba
    lcd.setCursor(5,1);
    lcd.print("Inv humedo");                 // indico en pantalla que el invernadero está humedo
    digitalWrite(bomba, LOW);                // apago la bomba
  }
   delay(1000);
}
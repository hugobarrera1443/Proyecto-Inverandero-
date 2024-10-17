// Declaración de puertos a utilizar

int tira_led=11;      // puerto del arduino donde coneto la etapa de potencia para conectar la tira led, debe se r un puerto que permita control PWM ya que tengo que modular la intensidad de las luces de la tira led
int sensorLDR=A2;     // entrada analógica donde conecto el sensor LDR

// Declaración de variables a utilizar

int valor_sensorLDR;  // Variable donde guardo el valor de intenidad de luz ambiente que lee el LDR
int valormap_luz;     // Variable donde guardo la conversión de nivel de la luz que entra por el sensor y la intensidad que debe mostrar la tira led (0 si hay mucha luz ambiente, la tira estará prácticamente apagada, y 255 si no hay luz ambiente, tira led a su maxima intensidad

void setup(){
      pinMode(tira_led,OUTPUT); // declaro el puerto como salida ya que tengo que encender o no la tira led
 
}

void loop()
{
  valor_sensorLDR=analogRead(sensorLDR);            // leo el valor del sensor LDR para rescatar el niveo de luz ambiente
  valormap_luz=map(valor_sensorLDR, 0,1023,0,255);  // convierto el nivel de luz del LDR en un nivel de intensidad para la tira led
  analogWrite(tira_led,valormap_luz);               // envío el nivel de intensidad que tiene que representar la tira led
  delay(2000);
}
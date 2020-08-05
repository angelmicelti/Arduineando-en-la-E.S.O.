/* Menú hecho con Encoder y Display LCD (I2C), partiendo del ofrecido por http://elprofegarcia.com/
 Debe instalar la libreria LiquidCrystal_I2C para que le funcione el programa
 
 Conexión del encoder al Arduino
 Encoder---->  Arduino
 CLK            2      
 DT             3
 SW             4
 +              5V
 GND            GND  
  
 Conexiones del I2C al Arduino:
 I2C ---->  Arduino
 SCL        A5      
 SDA        A4
 VCC        5V
 GND        GND  
 
Conexion del LED RGB
Pin Rojo ---> D9
Pin Verde ---> D10
Pin Azul ---> D11
 
*/

#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // dependiendo del fabricante del LCD el código 0x27 puede cambiar
                                  // 0x3F , 0x20 , 0x38 , 
#define DT  2       // DT a pin digital 2 (DT en módulo) Pin de la interrupción 
#define CLK  3      // CLK a pin digital 3 (CLK en módulo)
#define btn 4       // Switch del encoder al pin 4
#define LED_btn 13  // LED al pulsar el Switch Pin 13

char *menu1[] = {"1.Rojo ", "2.Azul ", "3.Verde","4.Amari", "5.Blanc", "6.OFF  "}; // Array del menú 1
volatile int posicion_encoder = 0; // Posición del encoder
int ant_posicion = 0;    // Valor anterior de la posición del encoder

void setup() {
  pinMode(DT, INPUT);   
  pinMode(CLK, INPUT);    
  pinMode(btn, INPUT_PULLUP);    // Entrada con resistencia Pullup para el Switch del encoder
  pinMode(LED_btn, OUTPUT);    
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
   
  lcd.init();                 // inicializa el LCD 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" SENSOR ROTACION"); // Mensaje inicial en LCD

  attachInterrupt(digitalPinToInterrupt(DT), encoder, LOW);  // Se habilita interrupción en pin 2 modo LOW
  Serial.begin(9600);   // incializa Puerto Serie a 9600 bps
  Serial.println("SENSOR ROTACION");  // Mensaje inicial en Puerto Serie
  lcd.setCursor(0,1);
  lcd.print(menu1[posicion_encoder]);
}

void loop() {
  if (digitalRead(btn) == LOW)     // Si es oprimido el Switch del Encoder
    {
      digitalWrite(LED_btn,HIGH); // Enciende el LED del Pin 13
      accion1();                  // llama a la función que enciende el LED según menú o los apaga
      Serial.println(menu1[posicion_encoder]); // Muestra el valor de la posición del menú 
      lcd.setCursor(9,1);
      lcd.print(menu1[posicion_encoder]);
      delay(700);                 // retardo para que no se lea varias veces el Switch del Encoder
      digitalWrite(LED_btn,LOW);  // apaga el LED del Pin 13
    }
    
  if (posicion_encoder != ant_posicion) { // Si la posición del menú es distinta a la anterior
    Serial.println(menu1[posicion_encoder]); // muestra la nueva posición del menú
    lcd.setCursor(0,1);
    lcd.print(menu1[posicion_encoder]);
    ant_posicion = posicion_encoder ; // actualiza la posición del menú
  }
}


void accion1()  {           // Función que enciende o apaga los LEDs
 
  if(posicion_encoder==5){
  digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
  }
  else if(posicion_encoder==0){
    digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
    digitalWrite(9,HIGH);
  }
  else if(posicion_encoder==1){
    digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
    digitalWrite(11,HIGH);
  }
  else if(posicion_encoder==2){
    digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
  }
  else if(posicion_encoder==3){
    digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
  }
  else if(posicion_encoder==4){
    digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
  }
}


void encoder()  {                //Función que determina el sentido del giro del encoder
  static unsigned long ultimaInterrupcion = 0;  // variable static con último valor de
                                                // tiempo de interrupción
  unsigned long tiempoInterrupcion = millis();  // variable almacena valor de func. millis

  if (tiempoInterrupcion - ultimaInterrupcion > 5) {  // No lee posibles rebotes en pulsos menores a 5 mseg.
    if (digitalRead(CLK) == HIGH)     // si CLK es HIGH, rotación a la derecha
    {
      posicion_encoder++ ;        // incrementa posición del menú en 1
    }
    else {          // si CLK es LOW, rotación a la izquierda
      posicion_encoder-- ;        // decrementa posición del menú en 1
    }

    posicion_encoder = min(5, max(0, posicion_encoder));  // número de opciones del menú, inferior 0 superior en 5
    ultimaInterrupcion = tiempoInterrupcion;  //actualiza valor del tiempo tiempo
  }           
}

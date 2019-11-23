#include <Servo.h>

boolean b_Barrera;

Servo servo_5;

int fnc_dynamic_analogRead(int _pin){
	pinMode(_pin,INPUT);
	return analogRead(_pin);
}

void fnc_dynamic_digitalWrite(int _pin, int _e){
	pinMode(_pin,OUTPUT);
	digitalWrite(_pin,_e);
}

void setup()
{
  Serial.begin(9600);

servo_5.attach(5);

pinMode(2, INPUT);
pinMode(3, INPUT);
pinMode(4, INPUT);
  servo_5.write(0);
  delay(0);
  b_Barrera = false;

}


void loop()
{

    if ((digitalRead(2) && (!b_Barrera))) {
      delay(1000);
      servo_5.write(90);
      delay(100);
      b_Barrera = true;
      while(!(((fnc_dynamic_analogRead(0) < 600))));
      delay(100);
      while(((fnc_dynamic_analogRead(0) < 600)));
      delay(1000);
      servo_5.write(0);
      delay(100);
      b_Barrera = false;

    }
    if (digitalRead(3)) {
      fnc_dynamic_digitalWrite(6, HIGH);
      fnc_dynamic_digitalWrite(7, LOW);

    } else {
      fnc_dynamic_digitalWrite(6, LOW);
      fnc_dynamic_digitalWrite(7, HIGH);

    }
    if (digitalRead(4)) {
      fnc_dynamic_digitalWrite(8, HIGH);
      fnc_dynamic_digitalWrite(9, LOW);

    } else {
      fnc_dynamic_digitalWrite(8, LOW);
      fnc_dynamic_digitalWrite(9, HIGH);

    }
    if (((fnc_dynamic_analogRead(0) < 600) && (!b_Barrera))) {
      delay(1000);
      servo_5.write(90);
      delay(100);
      delay(100);
      while(((fnc_dynamic_analogRead(0) < 600)));
      delay(5000);
      servo_5.write(0);
      delay(100);

    }
    delay(100);

}
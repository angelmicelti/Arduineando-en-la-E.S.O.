# Calibrando los pulsadores analógicos

En esta página vamos a ver cómo he conseguido calibrar estos dos pulsadores, lo cual nos puede llevar a interesantes actividades con nuestro alumnado de E.S.O.

## _Teclado analógico de 4 botones KC11B04_

![KC11BC04](KC11BC04.jpg)

En este teclado, [como se ha visto](TecladoAnalogico.md), tenemos cuatro botones sobre la placa, y tres pines:
- Vcc, alimentación.
- GND, masa.
- A0, que irá conectado a la entrada analógica.

Realizamos el siguiente montaje:

FOTO (TO-DO)

Y elaboramos un sencillo programa que nos envía a la consola serie la lectura del valor que tenemos en la entrada A0.
Lo tenemos disponible en [este enlace](http://www.arduinoblocks.com/web/project/174238) (Arduinoblocks), o bien en el código de aquí abajo:

~~~
double teclado;
void setup(){
    Serial.begin(9600);
    pinMode(A0, INPUT);
    teclado = 0;
}


void loop()
{
    teclado = analogRead(A0);
    Serial.println(teclado);
    delay(100);
}
~~~


Realizamos diversas pulsaciones a los botones, y observamos que se obtienen diferentes valores en la consola serie:

![LecturaKC11BC04](lecturaKC11BC04.gif)

Esto va bien.  


No obstante, vemos que al mantener una tecla pulsada (por ejemplo, la tecla K2) el valor que se obtiene en A0 no es un valor exacto, sino que oscila un poquito.  

![oscilacionKC11B04](oscilacionKC11B04.gif)

Esto nos lleva a pensar que no podremos hablar en nuestros programas de un **valor de A0**, sino de un **intervalo en el que se podrá encontrar A0**.

Para registrar los datos, he utilizado el programa Realterm que me permite, tal y como se explica en [este artículo](http://real2electronics.blogspot.com/2009/11/graficar-con-kst.html), capturarlos y guardarlos en un archivo. Incluso, como se indica en dicho artículo, podría graficar los datos con KST, si fuera necesario, pero no lo voy a hacer.

Una vez que he obtenido una muestra lo suficientemente grande de valores para cada una de las pulsaciones:
- K1
- K2
- K3
- K4
- K1+K2
- K1+K3
- K2+K3

y los he guardado en un archivo, los llevo a [esta hoja de cálculo](https://docs.google.com/spreadsheets/d/1GfoAlHANnyHcyWd9eGNL7__1PUo6nhGNXoAeHEWXHp4/edit?usp=sharing), donde los proceso.

Calculamos la media aritmética de los valores observados, así como la desviación típica de cada medida, para utilizar el criterio de las 3 sigmas, y obtener los siguientes intervalos:

   _  |   K1    |    K2   |  K3     | K4    |
:---: |  :---:  |  :---:  | :---:   | :---: |
K1    | 400-410 | 502-512 | 673-681 | >1020 |
K2    |         | 602-612 | 758-768 | >1020 |
K3    |         |         | 808-818 | >1020 |
K4    |         |         |         | >1020 |

En esta tabla de doble entrada indicamos la pulsación simultánea de dos pulsadores. Ki con Ki indica que sólo se pulsa uno.

---

## _Teclado analógico de 5 botones Keyestudio AD Key_

![KeyestudioADKey](KeyestudioADKey.jpg)

En este teclado, tenemos cinco botones sobre la placa, y ésta tiene también tres pines:
- OUT, que irá conectado a la entrada analógica
- Vcc, alimentación.
- GND, masas


Realizamos el siguiente montaje:

FOTO (TO-DO)

Utilizamos el mismo programa que con el teclado anterior para enviar los datos a la consola serie.
---

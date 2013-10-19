/*********************************************************************************************************
 * Roboduino Version 2.
 * Autor:    Jose Carlos Sosa Mejia
 * Mail:     jose_sosa@ymail.com
 * Creacion: 18/10/2013
 * Conexiones:
 * Pin  4: Reloj para sensores Infrarrojos + Led IRScan
 * Pin  5: Servomotor Izquierdo
 * Pin  6: Servomotor Derecho
 * Pin  3: Servomotor Sensor Ultrasonico 7= Derecha - 183= Izquierda - 84= Centro
 * Pin 10: Trigger Ultrasonico
 * Pin 11: Echo Ultrasonico
 * Pin A0: Sensor Infra rojo A
 * Pin A5: Sensor Infra rojo B
 * MIMICO:
 * Pin  2: Led 1: IrScan
 * Pin  8: Led 2: Motor Derecho Avanza
 * Pin  9: Led 3: Motor Derecho Retrocede
 * Pin 12: Led 4: Motor Izquierdo Retrocede
 * Pin 13: Led 5: Motor Izquierdo Avanza
 * Pin  7: Led 6: Objeto encontrado por Ultrasonido
 * 
 * 
 **********************************************************************************************************/

/*Librerias*/
#include <NewPing.h>
#include <Servo.h>

/*Servomotores*/
#define dAvanza     50
#define dRetrocede 130
#define dPara       90
#define iAvanza    130
#define iRetrocede  50
#define iPara       91
#define tGiroIzquierda 350
#define tGiroDerecha   350
Servo ruedaIzquierda;
Servo ruedaDerecha;
Servo radar;

/*Variables para indicar la forma de manejo*/
int manejo=0; /* 0 = manual 1 = automatico*/

/*Variables para la lectura de los sensores IR*/
const int trenPulsos = 16;
const int sensorIzquierda = A5;
const int sensorDerecha = A0;
int valorSensorDerecha=0;
int valorSensorIzquierda=0;
int IrAmbiente=0;             // variable para guardar la luz IR en el ambiente
int IrReflejo=0;              // Comparacion entra ambiente e IR de reflejo
int distanciaIR=0;            // Variable para almacenar el valor analogico obtenido luego de la lecura
int valoresIR[10];            // Vector para guardar lecturas
/********************************************************************************************************/
/*Variables para el Sonar*/
const int trig = 10;                       //Pin para activar la emision de ultrasonido
const int echo = 11;                       //Pin de lectura de tiempo de duracion del eco
const int distanciaMaxima = 200;           //Distancia maxima de medicion en centimetros
int distanciaCentral   = 0;
int distanciaIzquierda = 0;
int distanciaDerecha   = 0;
NewPing sonar(trig, echo, distanciaMaxima);

void setup() {                
  //Colocar todos los pines desde el 2 hasta el 11 como salidas
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  for(int i=2; i <= 9; i++)
  {
    pinMode(i, OUTPUT);
  }
  Serial1.begin(9600);
  ruedaIzquierda.attach(5);
  ruedaDerecha.attach(6);
  radar.attach(3);
  radar.write(84);
  ruedaIzquierda.write(iPara);
  ruedaDerecha.write(dPara);
  delay(1000); 
}


void loop() 
{

  while ( Serial1.available())
  {
    char tag = Serial1.read();
    switch (tag){
    case 'f':
      BtAvanzar();
      break;
    case 'b':
      BtRetroceder();
      break;
    case 'l':
      BtIzquierda();
      break;
    case 'r':
      BtDerecha();
      break;
    case 'm':
      BtManual();
      break;
    case 'a':
      BtAutomatico();
      break;
    case 's':
      BtParar();
      break;
    case 'z':
      win();
      break;
    }
  }
  if(manejo==1)
  {
    automatico();
  }
}








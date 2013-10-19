/*
  Funcion para medir distancias utilizando el sonar
 */
int medicion()
{
  delay(50);                        // Esperar 50 ms entre pings (unos 20 pings / seg). 29ms debe ser el plazo más breve entre pings.
  unsigned int uS = sonar.ping();   // Enviar ping, obtener el tiempo de ping en microsegundos (uS).
  unsigned int resultado=0;
  resultado=(uS / US_ROUNDTRIP_CM); // Convertir el tiempo de un ping a la distancia en cm.
  return(resultado);
}


/*Funcion que crea el tren de pulsos para hacer funcionar los sensores
 Y calcular luego el promedio entre las lecturas
 ENTRADAS:
 lecturas: Cantidad de veces que se leeran los sensores IR
 pinDigital: El pin que se utilizara para el tren de pulsos
 pinAnalogo: El pin en el cual ira la salida del sensor
 */
int lecturaInfrarroja(int lecturas, int pinDigital, int pinAnalogo){
  distanciaIR=0;
  for(int x=0;x<lecturas;x++){
    digitalWrite(pinDigital,LOW);     //Apaga los emisores IR para leer la IR ambiente
    digitalWrite(2,LOW);
    delay(1);                             // Retardo minimo necesario para tomar lecturas
    IrAmbiente = analogRead(pinAnalogo);  // Guardar la luz IR ambiental
    digitalWrite(pinDigital,HIGH);        //Enciende los emisores IR para leer la luz que reflejan los objetos
    digitalWrite(2,HIGH);
    delay(1);                        
    IrReflejo = analogRead(pinAnalogo);   // Guardar IR que refleja de los obstaculos
    valoresIR[x] = IrAmbiente-IrReflejo;  // Calcula los cambios IR y luego los guarda para poder promediarlos
  }

  for(int x=0;x<lecturas;x++){            // Se calcula el promedio
    distanciaIR+=valoresIR[x];
  }
  digitalWrite(2,LOW);
  digitalWrite(pinDigital,LOW);
  return(distanciaIR/lecturas);           // Valor que tomara la variable que llame a la funcion
} //Fin funcion de lectura IR

void giroIzquierda(int tiempo)
{
  ruedaIzquierda.write(iAvanza);
  ruedaDerecha.write(dRetrocede);
  digitalWrite(9,HIGH);
  digitalWrite(13,HIGH);
  delay(tiempo);
  parar();
}

void giroDerecha(int tiempo)
{
  ruedaIzquierda.write(iRetrocede);
  ruedaDerecha.write(dAvanza);
  digitalWrite(8,HIGH);
  digitalWrite(12,HIGH);
  delay(tiempo);
  parar();
}

void avanzar()
{
  ruedaIzquierda.write(iAvanza);
  ruedaDerecha.write(dAvanza);
  digitalWrite(8,HIGH);
  digitalWrite(13,HIGH);
}

void retroceder()
{
  ruedaIzquierda.write(iRetrocede);
  ruedaDerecha.write(dRetrocede);
  digitalWrite(9,HIGH);
  digitalWrite(12,HIGH);
}

void parar()
{
  ruedaIzquierda.write(iPara);
  ruedaDerecha.write(dPara);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}

void compararDistancias()
{
  if(distanciaIzquierda>distanciaDerecha)
  {
    giroIzquierda(tGiroIzquierda);
  }
  else if(distanciaDerecha>distanciaIzquierda)
  {
    giroDerecha(tGiroDerecha);
  }
  else if(distanciaDerecha<=5&&distanciaIzquierda<=5)
  {
    parar();
    retroceder();
    delay(200);
    giroIzquierda(tGiroIzquierda * 2);
    parar();
  }

}

void automatico()
{
  /*Operqciones con medicion Infrarroja*/
  valorSensorDerecha = 0;
  valorSensorIzquierda=0;
  valorSensorDerecha = lecturaInfrarroja(5,4,0);   //Asignar los valores de las lecturas IR    
  valorSensorIzquierda = lecturaInfrarroja(5,4,5); 
  /*int valorDiferencialDerecha = valorSensorDerecha-valorSensorIzquierda;
  int valorDiferencialIzquierda = valorSensorIzquierda-valorSensorDerecha;*/
  /*if (valorSensorDerecha <=0 || valorSensorIzquierda <=0)
  {
    parar();
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    delay(200);
    parar();
    delay(120);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    delay(200);
    parar();
    retroceder();
    delay(250);
    parar();
   giroIzquierda(tGiroIzquierda * 2);
  }*/


  /*Operaciones con medicion ultrasonica*/
  distanciaCentral = medicion();
  if(distanciaCentral >= 15)
  {
    digitalWrite(7,LOW);
    avanzar();
  }
  else
  {
    digitalWrite(7,HIGH);
    parar();
    radar.write(173);
    delay(300);
    distanciaDerecha = medicion();
    delay(300);
    radar.write(7);
    delay(600);
    distanciaIzquierda = medicion();
    delay(300);
    radar.write(84);
    delay(120);
    compararDistancias();
  }


}


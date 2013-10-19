void win()
{
  giroIzquierda(1000);
  delay(100);
  parar();
  retroceder();
  delay(200);
  giroDerecha(1000);
  delay(100);
  parar();
  delay(100);
  avanzar();
  delay(100);
  int hola = medicion();
  retroceder();
  delay(200);
  parar();
}

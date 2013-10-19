void BtAvanzar()
{
  ruedaIzquierda.write(iAvanza);
  ruedaDerecha.write(dAvanza);
  digitalWrite(8,HIGH);
  digitalWrite(13,HIGH);
}

void BtRetroceder()
{
  ruedaIzquierda.write(iRetrocede);
  ruedaDerecha.write(dRetrocede);
  digitalWrite(9,HIGH);
  digitalWrite(12,HIGH);
}

void BtIzquierda()
{
 ruedaIzquierda.write(iAvanza);
 ruedaDerecha.write(dRetrocede);
 digitalWrite(9,HIGH);
 digitalWrite(13,HIGH);
}

void BtDerecha()
{
  ruedaIzquierda.write(iRetrocede);
  ruedaDerecha.write(dAvanza);
  digitalWrite(8,HIGH);
  digitalWrite(12,HIGH);
}

void BtAutomatico()
{
  manejo = 1;
}

void BtManual()
{
  manejo = 0;
}
void BtParar()
{
  ruedaIzquierda.write(iPara);
  ruedaDerecha.write(dPara);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}


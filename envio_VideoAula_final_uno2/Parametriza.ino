void comando(String comand)
{
conta++;
avalia = "";
gsm.println(comand);
while(gsm.available()<=0) Serial.print("preso passo "), Serial.println(conta), delay(200);

while(gsm.available()>0)
{
  char letra = gsm.read();
  if (isAlphaNumeric(letra)) avalia += letra;
}

if (avalia=="OK") Serial.print("passo"), Serial.println(conta);
else Serial.print("avalia: "), Serial.println(avalia);
delay(200); 
}

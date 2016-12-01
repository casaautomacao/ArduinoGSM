#include <SoftwareSerial.h>
#include <Crescer.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



Tempora temp1;

LiquidCrystal_I2C lcd(0x27,16,2);

SoftwareSerial gsm(2, 3); // RX, TX

String avalia = "";
int conta = 0;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  gsm.begin(9600);
 temp1.defiSP(500);
 lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("A Casa da Automacao");

   lcd.setCursor(0,1);
  lcd.print("A0: ");

  delay(6000);

  Serial.println("Rodando");

  comando ("AT");
  comando ("AT+CMGF=1");
  comando ("ATE0");
  delay(1500);
  comando ("AT+CNMI=1,2,0,0,0");


  pinMode(4, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
}
int teste;
void loop() { // run over and over


if (temp1.Saida(1))
  {
   teste = analogRead(A0);

   if(teste>=1000) lcd.setCursor(4,1), lcd.print(teste); 
   else 
   {
    lcd.setCursor(5,1);
     lcd.print(teste);
     lcd.setCursor(4,1);
     lcd.print(" ");  
   }
 
   temp1.Saida(0);
 
  }

  String comp = "";
  if (gsm.available() > 0) {

    String msggsm = "";
    while (gsm.available() > 0)
    {
      char letra = gsm.read();
      if (isAlphaNumeric(letra)) msggsm += letra;
    }
    int tam = msggsm.length();


    comp += msggsm[tam - 2];
    comp += msggsm[tam - 1];

    Serial.print("MSG1: ");
    Serial.println(msggsm);

    Serial.print("comp: ");
    Serial.println(comp);


  lcd.setCursor(12,1);
     lcd.print(comp);


    if (comp == "L1")
    {
      digitalWrite(11, 0);
      Serial.println("Ligou1");
    }
    else if (comp == "D1")
    {
      digitalWrite(11, 1);
      Serial.println("Desligou1");
    }
    else if (comp == "L2")
    {
      digitalWrite(12, 0);
      Serial.println("ligou2");
    }
    else if (comp == "D2")
    {
      digitalWrite(12, 1);
      Serial.println("Desligou2");
    }


    delay(300);
  }


  
  int entrada = digitalRead(4);
  if (entrada == 0 or comp == "Le")
  {

    comando ("AT+CMGF=1");
    comando ("ATE0");
    comando ("AT+CNMI=1,2,0,0,0");

    gsm.print("AT+CMGS=");
    gsm.write(0x22);//aspa dupla
    gsm.print("+555198240925");
    gsm.write(0x22);//aspa dupla
    gsm.println();

    delay(1000);
    gsm.print("Valor da entrada A0: ");

    // delay(4000);
    gsm.println(teste);
    Serial.println(teste);

    //   delay(5000);

    gsm.write(0x1A);
    gsm.write(0x0D);
    gsm.write(0x0A);
    Serial.println("fim1");
    //   delay(4000);
    Serial.println("fim2");
  }

  //  Serial.print (entrada);
  //   Serial.print (" - ");
  //    Serial.println (teste);

}


#include <stdio.h>
#include <stdlib.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (9, 7, 8, 12, 10, 11);

void (*PonteiroDeFuncao)(); //ponteiro de função da máquina de estados. Ele aponta sempre para a função da máquina de estados que deve ser executada


void setup() {
  // put your setup code here, to run once:
  lcd.begin (16, 2);
  Serial.begin (9600);
  Serial.flush (); // Clear receive buffer.

}

void loop() {
  // put your main code here, to run repeatedly:
  PonteiroDeFuncao = EstadoInicial; //aponta para o estado inicial. Nunca esquecer de informar um estado inicial (senão, nesse caso em específico, pode haver um erro fatal / hard fault).
  while (1)
  {
    (*PonteiroDeFuncao)();    //chama a função apontada pelo ponteiro de função (logo, chama o estado corrente)
  }
  system("PAUSE");
  return 0;
}

void EstadoInicial(void)
{
  lcd.clear ();
  lcd.setCursor (1, 0);
  lcd.print ("Iniciando");
  delay(1000);

  char TeclaLida;
  //faz a leitura da tecla pressionada
  fflush(stdin); //limpa o buffer de teclado
  TeclaLida = Serial.read();

  if (TeclaLida == 'a') {
    TeclaLida = NULL;
    PonteiroDeFuncao = CaracterDigitadoA;
  }
  else
    lcd.print("esperado: a");
}

void CaracterDigitadoA(void)
{

  lcd.clear ();
  lcd.setCursor (1, 0);
  lcd.print ("DigitadoA");
  delay(1000);

  char TeclaLida;
  //faz a leitura da tecla pressionada
  Serial.flush(); //limpa o buffer de teclado
  if (Serial.available() > 0) {
    TeclaLida = Serial.read();

    if (TeclaLida == 'b')
      PonteiroDeFuncao = CaracterDigitadoB;
    else
    {
      PonteiroDeFuncao = EstadoInicial;
    }
  }


}

//Vai para proximo estado se for digitada a letra 'c'. Caso contrario, volta ao estado inicial (aguardar letra 'a')
void CaracterDigitadoB(void)
{
  lcd.clear ();
  lcd.setCursor (1, 0);
  lcd.print ("DigitadoB");
  delay(1000);

  char TeclaLida;
  //faz a leitura da tecla pressionada
  Serial.flush(); //limpa o buffer de teclado
  if (Serial.available() > 0) {
    TeclaLida = Serial.read();

    if (TeclaLida == 'c')
      PonteiroDeFuncao = CaracterDigitadoC;
    else
    {
      PonteiroDeFuncao = EstadoInicial;
    }
  }
}

//Valida seqüência se se for digitada a letra 'd'. Caso contrario, volta ao estado inicial (aguardar letra 'a')
void CaracterDigitadoC(void)
{

  lcd.clear ();
  lcd.setCursor (1, 0);
  lcd.print ("DigitadoC");
  delay(1000);

  char TeclaLida;
  //faz a leitura da tecla pressionada
  Serial.flush(); //limpa o buffer de teclado
  if (Serial.available() > 0) {
    TeclaLida = Serial.read();

    if (TeclaLida == 'd')
      PonteiroDeFuncao = finalizou;
    else
    {
      PonteiroDeFuncao = EstadoInicial;
    }
  }
}
void finalizou(void) {
  lcd.clear ();
  lcd.setCursor (1, 0);
  lcd.print ("finalizou");
  delay(1000);
}

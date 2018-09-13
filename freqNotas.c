#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <math.h>

  size_t count(const char * s, char c) {
    size_t r = 0;
    for (;* s; s++)
      r += * s == c;
    return r;
  }

// • #'s e b's funciona para a nota mi e si (modelo clássico)
// • Dobrado sustenido e dobrado bemol SÃO permitidos
double nota(char nota[]) {
  if (strlen(nota) < 1)
    return 0;

  double valorNota = 0;
  int posStr = 1;
  posStr += valorNota += count(nota, '#');
  valorNota -= count(nota, 'b');
  posStr += count(nota, 'b');

  switch (nota[0]) {
  case 'B':
    valorNota += 2;
  case 'A':
    valorNota += 2;
  case 'G':
    valorNota += 2;
  case 'F':
    valorNota++;
  case 'E':
    valorNota += 2;
  case 'D':
    valorNota += 2;
  case 'C':
    valorNota++;
  default:
    break;
  }

  char substr[10];
  int atual = 0;
  while (atual < strlen(nota)) {
    substr[atual] = nota[posStr + atual];
    atual++;
  }
  substr[atual] = '\0';
  int numOitavas = atoi(substr);
  if (substr[0] == '\0')
    numOitavas = 4; // padrão
  valorNota += 12 * numOitavas;

  // Calculo de frequencia:
  // nHz = f0 * (a)n 
  // a = constante
  // Usando f0 (frequencia fixa) como A4 = 440 Hz e seu valorNota como 58:
  // nHz = 440 * pow((pow(2,1/12)), variaçãoValor)
  double Hz = 440.0 * pow(pow(2.0, 1.0 / 12.0), valorNota - 58.0);
  return Hz;
}

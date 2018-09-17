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

double note(char note[]) {
  if (strlen(note) < 1)
    return 0;

  double valorNota = 0;
  int posStr = 1;
  posStr += valorNota += count(note, '#');
  valorNota -= count(note, 'b');
  posStr += count(note, 'b');

  switch (note[0]) {
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
  while (atual < strlen(note)) {
    substr[atual] = note[posStr + atual];
    atual++;
  }
  substr[atual] = '\0';
  int numOitavas = atoi(substr);
  if (substr[0] == '\0')
    numOitavas = 4; // padrão
  valorNota += 12 * numOitavas;
  double Hz = 440.0 * pow(2.0, (valorNota - 58.0)/12.0);
  return Hz;
}

char* hz(double hertz) {
  if (hertz < 16.35)
    return "";
  char nota[20];
  char oitavas[18];
  
  double valorNota = round(log10(hertz/440.0)/log10(2.0)*12.0 + 58.0);
  int numOitavas = (int) floor((valorNota)/12);
  valorNota -= numOitavas*12;
  // B C C# D D# E F F# G G# A A#
  nota[0] = ((--valorNota)>=0) ? ((--valorNota)>0) ? ((valorNota-=2)>0) ? ((valorNota-=2)>=0) ? 
            ((--valorNota)>0) ? ((valorNota-=2)>0) ? ((valorNota-=2)>0) ? '.' : 'A' : 'G' : 'F' : 'E' : 'D' : 'C' : 'B';            
  if (nota[0] == 'B')
    numOitavas--;
  itoa(numOitavas, oitavas, 10);
  strcat(nota, (valorNota==0) ? "#" : "");
  strcat(nota, oitavas);
  nota[strlen(nota)] = '\0';
  char* ret = malloc(strlen(nota));
  strcpy(ret, nota);
  return ret;
}

listNotes(int amount) {
  double n;
  for (n = 1; n <= amount; n++) {
    double Hz = 440.0 * pow(2.0, (n - 58.0)/12.0);
  	char *Nt = hz(Hz);
  	printf("%s - %.2fHz (%d)\n", hz(Hz), note(Nt), (int) n);
  }
}

main() {
  printf("%.2fHz\n", note("C0"));   // 16.35Hz
  printf("%.2fHz\n", note("Cb3"));  // 123.47Hz
  printf("%.2fHz\n", note("B##7")); // 4434.92Hz
  printf("%s\n", hz(440.00));       // "A4"
  printf("%s\n", hz(987.77));       // "B5"
  printf("%s\n", hz(2489.02));      // "D#7"
  printf("\n - Notas: -\n");
  listNotes(12);                    // List the first 12 notes
  system("PAUSE");
}

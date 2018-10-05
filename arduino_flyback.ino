#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notes.c"

#define speakerPin 5

double secsPorBeat = 0;
void bpm(int x) { secsPorBeat = 60.0 / (double)x; }

double compassos = 0;

void toca(char aNota[], double noCompasso) {
  compassos += noCompasso;
  double hrz = note(aNota);
  Serial.print("Nota [");
  Serial.print(aNota);
  Serial.print("] = ");
  Serial.print(hrz);
  Serial.println("Hz");
  double segundos = (4000.0 * (double)secsPorBeat * (double)noCompasso);
  tocaHz(hrz, segundos);
}

void tocaHz(double freq, double segundos){
  if (freq!=0)
    tone(speakerPin, freq, segundos);
  delay(segundos-5);
  noTone(speakerPin);
}

void musica(int beats, char musc[]) {
  bpm(beats);
  char copy[strlen(musc)];
  strcpy(copy, musc);
  
  char *nota = NULL;
  char *notas[100];
  
  byte index = 0;
  nota = strtok(musc, " ");
  while(nota != NULL) {
      notas[index] = nota;
      index++;
      nota = strtok(NULL, " ");
  }
    
  for(int n = 0; n < index; n++) { 
    char *token = NULL;
    char *tokens[20];

    byte index2 = 0;
    token = strtok(notas[n], "/");
    while(token != NULL) {
        tokens[index2] = token;
        index2++;
        token = strtok(NULL, "/");
    }
    int tempo = 0;
    char c[strlen(token)];
    delay(20);
    for(int o = 0; o < index2; o++) {
      if (tempo == 0)
        strcpy(c, tokens[o]);
      else {
        if (c[0] == 'P')
          toca("", (double)(1.0 / (atoi(tokens[o]))));
        else
          toca(c, (double)(1.0 / (atoi(tokens[o]))));
      }
      tempo = 1;
    }
  }
  Serial.println("LN");
}

void setup() {
  Serial.begin(9600);
}

// bobina de tesla musical
void loop() {
  bpm(100);
  // nota, compasso
  toca ("C3", 1);
  
  // musica(bpm, notas)
  musica(70, "E/8/16 G/16 A/2/4/8 C5/16 B/4/8/16 C5/32 B/32 A/4/8/16 G/4/8/16 A/4 E/4/8 E/8/16 G/16 A/2/4/8 C5/16 B/4/8/16 C5/32 A/4/8/16 G/8 A/2/4");
  
  // obs: C/4/4/8 = C/4 + C/4 + C/8
}


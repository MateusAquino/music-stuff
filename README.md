# Aplicação Musical
## Neste repositório:
* Conversor de Nota Musical para Frequência (em Hz) | freqNotas.c

## Como usar:
### freqNotas.c
```c
// Exemplo
#include "freqNotas.c"

//...
int main() {
  printf("%.2fHz\n", nota("A#0"));  // 29.14Hz
  printf("%.2fHz\n", nota("Cb3"));  // 123.47Hz
  printf("%.2fHz\n", nota("A"));    // 440.00Hz
  printf("%.2fHz\n", nota("B5"));   // 987.77Hz
  printf("%.2fHz\n", nota("B##7")); // 4434.92Hz
  system("PAUSE");
  return 0;
}
```

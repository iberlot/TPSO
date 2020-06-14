#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int arg;
  char texto[512];
  char archivo[50];
  int flagArchivo = 0;
  int flagAdd = 0;


  for (arg = 1; arg < argc; arg++) {
    if(argv[arg][0] == '-'){
      switch (argv[arg][1]) {
        case 'help':
          break;
        case 'add':
          break;
        case 'rem':
          break;
        case 'upd':
          break;
        case 'get':
          break;
        default:
          printf("Parametro %s no soportado\n", argv[arg]);
          break;
      }
    }
  }

  if(flagAdd==1){
    printf("Los datos agregados quedaron de la siguiente manera: %s\n", texto);
  }
  exit(0);
}

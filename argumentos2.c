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
        case 'i':
          printf("Programa: %s\n", argv[0]);
          break;
        case 'l':
          printf("La cantidad de opciones pasadas es de: %d\n", argc-1);
          break;
        case 'a':
          arg++;
          strcat( texto, " " );
          strcat( texto, argv[arg] );
          flagAdd = 1;
          break;
        case 'f':
          arg++;
          strcpy( archivo, argv[arg] );
          flagArchivo = 1;
          break;
        default:
          printf("Parametro %s no soportado\n", argv[arg]);
          break;
      }
    }
  }

  if(flagArchivo==1){
    printf("Se guardaria toda la informacion en: %s\n", archivo);
  }

  if(flagAdd==1){
    printf("Los datos agregados quedaron de la siguiente manera: %s\n", texto);
  }
  exit(0);
}

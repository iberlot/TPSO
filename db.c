#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(){
	printf("MENU DE AYUDA\n");
					printf("help para mostrar las opciones\n");
					printf("add: permite agregar un objeto al archivo mediante parametro o stdin.\n");
					printf("rem: permite eliminar un objeto al archivo indicando su clave.\n");
					printf("upd: permite actualizar un objeto al archivo indicando su clave.\n");
					printf("get: permite recuperar uno o varios objetos del archivo segun un filtro de busqueda o su clave.\n");
}

int main(int argc, char *argv[]) {
	int arg;
	char texto[512];
	char archivo[50];
	int flagArchivo = 0;
	int flagAdd = 0;
	int codError = 0;

	int accion = 0;

	if (accion == 1) {
		if (argv[2][0] == '-') {
			codError = 1;
		}

//		archivo = argv[2];
	}

	for (arg = 1; arg < argc; arg++) {
		if (argv[arg][0] == '-') {
			switch (argv[arg][1]) {
//			case 'help':
			case 'h':
				menu();

				break;
//			case 'add':
			case 'a':

				break;
//			case 'rem':
			case 'r':
				break;
//			case 'upd':
			case 'u':
				break;
//			case 'get':
			case 'g':
				break;
			default:
				menu();
				printf("Parametro %s no soportado\n", argv[arg]);
				break;
			}
		}
	}

	if (flagAdd == 1) {
		printf("Los datos agregados quedaron de la siguiente manera: %s\n",
				texto);
	}
	exit(0);
}

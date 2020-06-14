#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int arg;
	char texto[512];
	char archivo[50];
	int flagArchivo = 0;
	int flagAdd = 0;
	int codError = 0;

	int accion = 0;

	switch (argv[1][1]) {
	case 'help':
		accion = 66;
		break;
	case 'add':
		accion = 1;
		break;
	case 'rem':
		accion = 2;
		break;
	case 'upd':
		accion = 3;
		break;
	case 'get':
		accion = 4;
		break;
	default:
		printf("Parametro %s no soportado\n", argv[arg]);
		break;
	}

	if (accion == 1) {
		if (argv[2][0] == '-') {
			codError = 1;
		}

		archivo = argv[2];
	}
	for (arg = 2; arg < argc; arg++) {
		if (argv[arg][0] == '-') {
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

	if (flagAdd == 1) {
		printf("Los datos agregados quedaron de la siguiente manera: %s\n",
				texto);
	}
	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
	printf("MENU DE AYUDA\n\n");
	printf("help para mostrar las opciones\n");
	printf("add: permite agregar un objeto al archivo mediante parametro o stdin.\n");
	printf("rem: permite eliminar un objeto al archivo indicando su clave.\n");
	printf("upd: permite actualizar un objeto al archivo indicando su clave.\n");
	printf("get: permite recuperar uno o varios objetos del archivo segun un filtro de busqueda o su clave.\n");
	printf("\n");
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

		switch (argv[arg][1]) {
		case 'h':
			if (strcmp(argv[arg], "help") != 1) {
				codError = 2;
			}
			help();

			break;
		case 'a':
			if (strcmp(argv[arg], "add") != 1) {
				codError = 2;
			}


			// /home/user/person.dat -value '{"key":"abcd","name":"Juan
			//Perez","age": 32,"height":1.76,"hasLicence":true}'

			break;
		case 'r':
			if (strcmp(argv[arg], "rem") != 1) {
				codError = 2;
			}
			break;
		case 'u':
			if (strcmp(argv[arg], "upd") != 1) {
				codError = 2;
			}
			break;
		case 'g':
			if (strcmp(argv[arg], "get") != 1) {
				codError = 2;
			}
			break;
		default:
			codError = 2;
			printf("Parametro %s no soportado\n", argv[arg]);
			help();
			break;
		}
	}

	if (flagAdd == 1) {
		printf("Los datos agregados quedaron de la siguiente manera: %s\n", texto);
	}
	exit(0);
}
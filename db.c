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

        	print("MENU DE AYUDA");
        	print("help para mostrar las opciones");
        	print("add: permite agregar un objeto al archivo mediante par�metro o stdin.");
        	print("rem: permite eliminar un objeto al archivo indicando su clave.");
        	print("upd: permite actualizar un objeto al archivo indicando su clave.");
        	print("get: permite recuperar uno o varios objetos del archivo seg�n un filtro de b�squeda o su clave.");

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

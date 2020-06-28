#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <auxiliares.h>

char* substr(char* cadena, int comienzo, int longitud) {
	if (longitud == 0)
		longitud = strlen(cadena) - comienzo;

	char *nuevo = (char*) malloc(sizeof(char) * (longitud + 1));
	nuevo[longitud] = '\0';
	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

void help() {
	printf("MENU DE AYUDA\n\n");
	printf("help para mostrar las opciones\n");
	printf("Forma de uso de la sentencia:\n db comando archivo -nombreparam1 valorparam1 -nombreparam2 valorparam2\n");
	printf("Lista de comandos aceptados\n");
	printf("add: permite agregar un objeto al archivo mediante parametro o stdin.\n");
	printf("rem: permite eliminar un objeto al archivo indicando su clave.\n");
	printf("upd: permite actualizar un objeto al archivo indicando su clave.\n");
	printf("get: permite recuperar uno o varios objetos del archivo segun un filtro de busqueda o su clave.\n");
	printf("archivo: Los comandos add, upd,get y rem requieren el path al archivo donde se leen/escriben los datos. Si el archivo no existe y se trata de una operaci�n add, se crea el archivo y agrega el registro.\n");

	printf("\n");
}

int verificarCoincidenciaKey(char* argv[], FILE arch){ // @suppress("Type cannot be resolved")
	int valor = 0;
	char* key = substr(argv[4], 8, 4);
	char* archivoS = fgets(key, 4096, arch);
	archivoS = substr(archivoS, 8, 4);
	if (strcmp(key, archivoS) != 0) {
		valor++;
	}
	printf("Documento: %s", archivoS);
	return valor;
}


void agregarDato(char *argv[], int codError, int arg) {

	printf("Entrando al Add...\n");

	if (strcmp(argv[1], "add") != 0) {
		printf("Parametro %s no soportado %i...\n", argv[arg], strcmp(argv[arg], "add"));
		codError = 2;
	}
	if (argv[2][0] == '-') {
		codError = 1;
	}
	//char* buffer[4096];
	//'{"key":"abcd","name":"Juan Perez","age":32,"height":1.76,"hasLicence":true}'

	printf("Creando archivo...\n");

	FILE *fp; // @suppress("Type cannot be resolved")

	fp = fopen(argv[2], "a+");

	if (strcmp(argv[3], "-value") != 0) {
		printf("El parametro %s", argv[3]);
		codError = 2;
	}

	int num = verificarCoincidenciaKey(argv, fp);
	if(num != 0){
		printf("La clave coincide con una clave ya existente en el archivo!");
	}
	else{

	fputs("\n", fp);
	fputs("0", fp);
	fputs(argv[4], fp);
	printf("%s", argv[4]);
	fclose(fp);

	}
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

//	for (arg = 1; arg < argc; arg++) {

	switch (argv[1][0]) {
	case 'h':
		if (strcmp(argv[arg], "help") != 1) {
			codError = 2;
			break;
		}
		help();

		break;

	case 'a':
		agregarDato(argv, codError, arg);

		break;

	case 'r':
		if (strcmp(argv[arg], "rem") != 1) {
			codError = 2;
			break;
		}
		if (argv[2][0] == '-') {
			codError = 1;
		}

		break;

	case 'u':
		if (strcmp(argv[arg], "upd") != 1) {
			codError = 2;
			break;
		}
		if (argv[2][0] == '-') {
			codError = 1;
		}

		break;

	case 'g':
		if (strcmp(argv[arg], "get") != 1) {
			codError = 2;
			break;
		}
		if (argv[2][0] == '-') {
			codError = 1;
		}

		break;

	default:
		codError = 2;
		printf("Parametro %s no soportado\n", argv[arg]);
		help();
		break;
	}
//	}

	if (flagAdd == 1) {
		printf("Los datos agregados quedaron de la siguiente manera: %s\n", texto);
	}
	exit(0);
}


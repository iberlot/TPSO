#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <auxiliares.h>

/* Lo que esta dentro de estos comentarios debe ir a una libreria */
char* substr(char* cadena, int comienzo, int longitud) {
	if (longitud == 0)
		longitud = strlen(cadena) - comienzo;

	char *nuevo = (char*) malloc(sizeof(char) * (longitud + 1));
	nuevo[longitud] = '\0';
	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

short existe(const char* ruta) {

	FILE *archivo = fopen(ruta, "r"); // @suppress("Type cannot be resolved")

	if (archivo) {
		fclose(archivo);
		return 1; //TRUE
	} else {
		return 0; //FALSE
	}

}

int longitud(char* cadena) {
	int contador = 0;
	// Recorrer la cadena hasta encontrar el carácter NUL o de terminación
	while (cadena[contador] != 0) {
		contador++;
	}
	return contador;
}

int EncontrarPrimeraPosicion(char* palabra, char caracter) {
	for (int i = 0; i < longitud(palabra); i++) {
		char carac = palabra[i];
//		printf("|%i == %i|", carac, caracter);

		if (palabra[i] == caracter) {
			return i + 1;
		}
	}

	return 0; //No se encontro el carácter
}

/* Fin del codigo de libreria */

void help() {
	printf("\nMENU DE AYUDA\n\n");
	printf("help para mostrar las opciones\n");
	printf("Forma de uso de la sentencia:\n db comando archivo -nombreparam1 valorparam1 -nombreparam2 valorparam2\n");
	printf("\n4Lista de comandos aceptados\n");
	printf("add: permite agregar un objeto al archivo mediante parametro o stdin.\n");
	printf("rem: permite eliminar un objeto al archivo indicando su clave.\n");
	printf("upd: permite actualizar un objeto al archivo indicando su clave.\n");
	printf("get: permite recuperar uno o varios objetos del archivo segun un filtro de busqueda o su clave.\n");
	printf("archivo: Los comandos add, upd,get y rem requieren el path al archivo donde se leen/escriben los datos. Si el archivo no existe y se trata de una operaciï¿½n add, se crea el archivo y agrega el registro.\n");

	printf("\n");
}

void errores(int codError, char* extra) {
//	{"status":"error","message":"Mensaje descriptivo del error."}
	fprintf(stderr, "{\"status\":\"error\",\"message\":\"");
	fprintf(stderr, "Error %i: ", codError);
	switch (codError) {
	case 1:
		fprintf(stderr, "Falta parametro requerido...");
		fprintf(stderr, "\"}\n");
		help();
		break;
	case 2:
		fprintf(stderr, "Comando no soportado, no se reconose %s...", extra);
		fprintf(stderr, "\"}\n");
		help();
		break;
	case 3:
		fprintf(stderr, "La clave %s coincide con una clave ya existente en el archivo!", extra);
		fprintf(stderr, "\"}\n");
		break;
	default:
		fprintf(stderr, "Danger, Will Robinson...");
		fprintf(stderr, "\"}\n");
		break;
	}
	exit(0);
}

int verificarCoincidenciaKey(char* file, char* key) { // @suppress("Type cannot be resolved")
	char archivoS[4096];

	FILE *fpa; // @suppress("Type cannot be resolved")
	fpa = fopen(file, "a+");

	while (feof(fpa) == 0) {
		fgets(archivoS, 4096, fpa);

		// 48 = 0 en ascii
		if (archivoS[0] == 48) {
			char* dato = strstr(archivoS, "\"key\":");
			printf("\n|%s|\n", dato);

			int posIni = 7;
			int posFin = EncontrarPrimeraPosicion(dato, ',');
			char* voS = substr(dato, posIni, posFin);

			printf("\n|%i|\n", posFin);
			printf("\n|%s|\n", voS);

			exit(0);

			if (strcmp(key, voS) == 0) {
				return 1;
			}
		}
	}

	return 0;
}

void agregarDato(char *argv[], char *archivo) {

	printf("Realizando la carga de datos...\n");

	if (argv[2][0] == '-') {
		errores(1, "");
	}
	//char* buffer[4096];
	//'{"key":"abcd","name":"Juan Perez","age":32,"height":1.76,"hasLicence":true}'

	if (existe(archivo) == 0) {
		printf("Creando archivo...\n");
	}

	FILE *fp; // @suppress("Type cannot be resolved")

	fp = fopen(archivo, "a+");

	if (!argv[3]) {
		errores(1, "");
	}

	if (strcmp(argv[3], "-value") != 0) {
		errores(1, "");
	}

	int num = verificarCoincidenciaKey(archivo, substr(argv[4], 8, 4));

	if (num != 0) {
		errores(3, substr(argv[4], 8, 4));
	} else {

		fputs("\n", fp);
		fputs("0", fp);
		fputs(argv[4], fp);
		printf("%s", argv[4]);
		fclose(fp);

	}
}

// db comando archivo -nombreparam1 valorparam1 -nombreparam2 valorparam2
int main(int argc, char *argv[]) {
	int arg;
	char texto[512];
	char archivo[50];
	int flagArchivo = 0;
	int flagAdd = 0;

	int accion = 0;

	if (accion == 1) {
		if (argv[2][0] == '-') {
			errores(1, "");
		}

//		archivo = argv[2];
	}

//	for (arg = 1; arg < argc; arg++) {

	switch (argv[1][0]) {
	case 'h':
		if (strcmp(argv[1], "help") != 0) {
			errores(2, argv[1]);
			break;
		}
		help();

		break;

	case 'a':

		if (strcmp(argv[1], "add") != 0) {
			errores(2, argv[1]);
		}

		agregarDato(argv, argv[2]);

		break;

	case 'r':
		if (strcmp(argv[arg], "rem") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}

		break;

	case 'u':
		if (strcmp(argv[arg], "upd") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}

		break;

	case 'g':
		if (strcmp(argv[arg], "get") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}

		break;

	default:
		errores(2, argv[1]);
	}
//	}

	if (flagAdd == 1) {
		printf("Los datos agregados quedaron de la siguiente manera: %s\n", texto);
	}
	exit(0);
}


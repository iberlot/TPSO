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

char* substrHasta(char* cadena, int comienzo, char caracter) {

	char *nuevo = (char*) malloc(sizeof(char) * ((strlen(cadena) - comienzo) + 1));
	char *aux = cadena + comienzo;

	int longitud = EncontrarPrimeraPosicion(aux, caracter);

	nuevo[longitud] = '\0';
	strncpy(nuevo, cadena + comienzo, longitud - 1);

	return nuevo;
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
		fprintf(stderr, "Comando no soportado, no se reconoce %s...", extra);
		fprintf(stderr, "\"}\n");
		help();
		break;
	case 3:
		fprintf(stderr, "La clave %s coincide con una clave ya existente en el archivo!", extra);
		fprintf(stderr, "\"}\n");
		break;
	case 4:
		fprintf(stderr, "El archivo %s no existe.", extra);
		fprintf(stderr, "\"}\n");
		break;
	case 5:
		fprintf(stderr, "No se encontro la clave %s en el archivo.", extra);
		fprintf(stderr, "\"}\n");
		break;
	default:
		fprintf(stderr, "Danger, Will Robinson...");
		fprintf(stderr, "\"}\n");
		break;
	}
	exit(0);
}

char* recuperarKeyString(char* string) {

	char* dato = strstr(string, "\"key\":");

	int posIni = 7;

	char* key = substrHasta(dato, posIni, ',');
	key = substr(key, 0, longitud(key) - 1);

	return key;
}

int verificarCoincidenciaKey(char* file, char* key) {
	char archivoS[4096];
	int contador = 0;

	FILE *fpa; // @suppress("Type cannot be resolved")

	fpa = fopen(file, "a+");

	while (feof(fpa) == 0) {
		fgets(archivoS, 4096, fpa);

		if (archivoS[0] == 48) { // 48 = 0 en ascii
//			char* dato = strstr(archivoS, "\"key\":");
//
//			int posIni = 7;
//
//			char* voS = substrHasta(dato, posIni, ',');
//			voS = substr(voS, 0, longitud(voS) - 1);
			char* voS = recuperarKeyString(archivoS);

			printf("%s == %s\n", key, voS);
			if (strcmp(key, voS) == 0) {
				return contador;
			}
		}
		contador++;
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

	int num = verificarCoincidenciaKey(archivo, recuperarKeyString(argv[4]));

	if (num != 0) {
		errores(3, substr(argv[4], 8, 4));
	} else {

		fputs("\n", fp);
		fputs("0", fp);
		fputs(argv[4], fp);
		printf("%s\n", argv[4]);
		fclose(fp);

	}
}

void removerDato(char *argv[], int arg) {
	if (strcmp(argv[arg], "rem") != 1) {
		errores(2, argv[arg]);
	}
	if (argv[2][0] == '-') {
		errores(1, "");
	}
	FILE *fp; // @suppress("Type cannot be resolved")
	char archivo[4096];
	fp = fopen(argv[2], "r"); //No verifica cuando no existe el archivo

//	void* NULL;

	if (fp == 0) {
		errores(4, argv[2]);
	}
	//db rem person.dat -key abcd
	if (strcmp(argv[3], "-key") != 0) {
		errores(2, argv[3]);
	}
	int lineaNum = verificarCoincidenciaKey(argv[2], substr(argv[4], 8, 4));

	int count = 0;
	if (lineaNum != 0) {
		errores(2, argv[4]);
	} else {
		char line[256]; /* or other suitable maximum line size */
		while (fgets(line, sizeof line, fp) != 0) /* read a line */
		{
			if (count == lineaNum) {
				//Aca debe mostrar por pantalla la linea que encontro
				printf("%s", line);
				if (line[0] == 48) {
					line[0] = 49; //Es el 1 en ascii
				}
				fclose(fp);
			} else {
				count++;
			}
		}
		fclose(fp);
	}
	//db rem person.dat -key abcd
}
// db comando archivo -nombreparam1 valorparam1 -nombreparam2 valorparam2

void updateDato(char *argv[], int arg, char *archivo) { //VER *archivo
	FILE *fp; // @suppress("Type cannot be resolved")
//	char archivo[4096];
	fp = fopen(argv[2], "r"); //No verifica cuando no existe el archivo
	if (strcmp(argv[arg], "upd") != 1) {
		errores(2, argv[arg]);
	}
	if (existe(archivo) == 1) { //Si el archivo no existe
		errores(4, argv[arg]);
	}
	if (strcmp(argv[3], "-key") != 0) {
		errores(2, argv[3]);
	}

	int num = verificarCoincidenciaKey(archivo, substr(argv[4], 23, 4));

	if (num != 0) {
		errores(3, substr(argv[4], 23, 4));
	} else {
		char line[256]; /* or other suitable maximum line size */
		int count = 0;
		while (fgets(line, sizeof line, fp) != 0) /* read a line */
		{
			if (count == num) {
//				line = argv[4];
				//Aca muestra por pantalla lo que encontro ya editado
				printf("%s", argv[4]);
				fclose(fp);
			} else {
				count++;
			}
		}

	}
}
//No Aclara si quiere solo actualizar un dato por ende actualizamos todo el objeto y fin
//db upd person.dat -key abcd valorAmodificar
//{"key":"abcd","name":"Juan Perez","age":34,"height":1.76,"hasLicence":false}

void getDato(char *argv[], int arg, char *archivo) {
	FILE *fil; // @suppress("Type cannot be resolved")
//		char archivo[4096];
	if (strcmp(argv[arg], "get") != 1) {
		errores(2, argv[arg]);
	}
	if (existe(archivo) == 1) { //Si el archivo no existe
		errores(4, argv[arg]);
	}
	if (strcmp(argv[3], "-key") != 0) {
		errores(2, argv[3]);
	}

	int num = verificarCoincidenciaKey(archivo, substr(argv[4], 23, 4));
	fil = fopen(argv[2], "r"); //No verifica cuando no existe el archivo

	if (num != 0) {
		errores(3, substr(argv[4], 23, 4));
	} else {
		char line[256]; /* or other suitable maximum line size */
		int count = 0;
		while (fgets(line, sizeof line, fil) != 0) /* read a line */
		{
			if (count == num) {
				//Aca muestra por pantalla lo que encontro ya editado
				printf("%s", line);
				fclose(fil);
			} else {
				count++;
			}
		}
		///db get person.dat -key abcd
		//No se como poner el tema del filter. Mañana lo vemos
	}
}

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
		removerDato(argv, arg);
		break;

	case 'u':
		if (strcmp(argv[arg], "upd") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}
		updateDato(argv, arg, argv[2]); //TODO Faltaria el parametro file pero nse si da ponerlo en el main
		break;

	case 'g':
		if (strcmp(argv[arg], "get") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}
		getDato(argv, arg, argv[2]); //TODO Faltaria el parametro file pero nse si da ponerlo en el main
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


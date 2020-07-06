#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <auxiliares.h>
//#include "auxiliares.c"

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
	// Recorrer la cadena hasta encontrar el car�cter NUL o de terminaci�n
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

	return 0; //No se encontro el car�cter
}

char* substrHasta(char* cadena, int comienzo, char caracter) {

	char *nuevo = (char*) malloc(sizeof(char) * ((strlen(cadena) - comienzo) + 1));
	char *aux = cadena + comienzo;

	int longitud = EncontrarPrimeraPosicion(aux, caracter);

	nuevo[longitud] = '\0';

	strncpy(nuevo, cadena + comienzo, longitud - 1);

	return nuevo;
}

short formatoJson(char* cadena) {
	int llavePrincipal = 0;
	int llaveFinal = 0;
	//int verificadoTotal = 0;

	for (int i = 0; i < longitud(cadena); i++) {

//		if (cadena[i] == '{') {
		if (cadena[i] == 123) {
			llavePrincipal++;
		}

		//			if (cadena[i] == '}') {
		if (cadena[i] == 125) {
			llaveFinal++;
		}

		// FIXME esto corta el string habria que trabajarlo con substring llendo desde la posicion de la primer como hasta la de la segunda
		char* parametro = strtok(cadena, ","); //El famoso split de java

//		printf("|%s|\n", cadena);

		if (parametro) { //Si no hay coma entonces esta mal
			return 0;
		} else {
			for (int j = 0; j < longitud(parametro); j++) {
				char* verificoDosPuntos = strtok(parametro, ":");
				if (verificoDosPuntos) {
					return 0;
				} else {
					int comillas = 0;
					if (longitud(verificoDosPuntos) == 1) { //Si tiene solo dos posiciones
						for (int z = 0; z < 2; z++) {
//							if (verificoDosPuntos[z] == "\"") { //Chequear si esto es asi como java o [j][z]
							if (verificoDosPuntos[z] == 34) { //Chequear si esto es asi como java o [j][z]
								comillas++;
							}
						}
					} else {
						return 0;
					}
					if (comillas == 2 && (verificoDosPuntos[0] == 34) && (verificoDosPuntos[longitud(verificoDosPuntos) - 1] == 34)) {
						comillas = 0;
					} else { //Si no tiene la comilla inicial y final y son mas o menos de dos comillas esta mal
						return 0;
					}
				}
			}
		}
	}

	if ((llavePrincipal == 0) || (llavePrincipal >= 2)) {
		if (llaveFinal == 0 || llaveFinal > 1) {
			return 0;
		}
	}

//	if (cadena[longitud(cadena) - 1] == '}' && cadena[0] == '{') {
	if (cadena[longitud(cadena) - 1] == 125 && cadena[0] == 123) {
		return 1;
	}
	return 0; //ya si no entra al for ya directamente es que no tiene formato json
	// {"status":"error","message":"Mensaje descriptivo del error."}
	//{"key":"abcd","name":"Juan Perez","age":32,"height":1.76,"hasLicence":true}
}

// XXX toma papa esto es eda para vos =P
char* trim(char* cadena) {
	if (cadena[0] == ' ') {
		cadena = trim(cadena + 1);
	}
	return cadena;
}
/* Fin del codigo de libreria */

/* MAQUETADO DE FUNCIONES */

void help();
void errores(int codError, char* extra);
char* recuperarKeyString(char* string);
int verificarCoincidenciaKey(char* file, char* key);
void agregarDato(char *dato, char *archivo);
void removerDato(char *archivo, char* key);
void updateDato(char *dato, char *archivo);
void getDato(char *key, char *archivo);
char* buscarClaveValor(char* string, char* clave);

/* FIN DE MAQUETADO */

void help() {
	printf("\nMENU DE AYUDA\n\n");
	printf("help para mostrar las opciones\n");
	printf("Forma de uso de la sentencia:\n db comando archivo -nombreparam1 valorparam1 -nombreparam2 valorparam2\n");
	printf("\nLista de comandos aceptados\n");
	printf("add: permite agregar un objeto al archivo mediante parametro o stdin.\n");
	printf("rem: permite eliminar un objeto al archivo indicando su clave.\n");
	printf("upd: permite actualizar un objeto al archivo indicando su clave.\n");
	printf("get: permite recuperar uno o varios objetos del archivo segun un filtro de busqueda o su clave.\n");
	printf("archivo: Los comandos add, upd,get y rem requieren el path al archivo donde se leen/escriben los datos. Si el archivo no existe y se trata de una operaci�n add, se crea el archivo y agrega el registro.\n");

	printf("\n");
}

void errores(int codError, char* extra) {
	int aiuda = 0;

	fprintf(stderr, "{\"status\":\"error\",\"message\":\"");
	fprintf(stderr, "Error %i: ", codError);
	switch (codError) {
	case 1:
		fprintf(stderr, "Falta parametro requerido...");
		aiuda = 1;
		break;
	case 2:
		fprintf(stderr, "Comando no soportado, no se reconoce %s...", extra);
		aiuda = 1;
		break;
	case 3:
		fprintf(stderr, "La clave \'%s\' coincide con una clave ya existente en el archivo!", extra);
		break;
	case 4:
		fprintf(stderr, "El archivo %s no existe.", extra);
		break;
	case 5:
		fprintf(stderr, "No se encontro la clave %s en el archivo.", extra);
		break;
	case 6:
		fprintf(stderr, "Operador %s invalido.", extra);
		break;
	case 7:
		fprintf(stderr, "%s es de un tipo de dato invalido.", extra);
		break;
	case 8:
		fprintf(stderr, "Formato de JSON no voalido en %s.", extra);
		break;
	default:
		fprintf(stderr, "Danger, Will Robinson...");
		break;
	}

	fprintf(stderr, "\"}\n");

	if (aiuda == 1) {
		help();
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
			char* voS = recuperarKeyString(archivoS);
			if (strcmp(key, voS) == 0) {
				return contador;
			}
		}
		contador++;
	}

	return 0;
}

char* buscarClaveValor(char* string, char* clave) {
	char* key;
	char *str = malloc(512);

	snprintf(str, 256, "\"%s\":", clave);

	char* dato = strstr(string, str);

	int posIni = strlen(str);
	key = substrHasta(dato, posIni, ',');

	return trim(key);
}

void agregarDato(char *dato, char *archivo) {

	printf("Realizando la carga de datos...\n");

	if (existe(archivo) == 0) {
		printf("Creando archivo...\n");
	}

	FILE *fp; // @suppress("Type cannot be resolved")

	fp = fopen(archivo, "a+");

	if (verificarCoincidenciaKey(archivo, recuperarKeyString(dato)) != 0) {
		errores(3, recuperarKeyString(dato));
	} else {

		fputs("\n", fp);
		fputs("0", fp);
		fputs(dato, fp);
		printf("%s\n", dato);
		fclose(fp);
	}
}

void removerDato(char* file, char* key) {

	FILE *fp; // @suppress("Type cannot be resolved")

	fp = fopen(file, "r+"); //No verifica cuando no existe el archivo

	if (fp == 0) {
		errores(4, file);
	}
	int lineaNum = verificarCoincidenciaKey(file, key);

	int count = 0;

	if (lineaNum == 0) {
		errores(5, key);
	} else {
		char line[4096]; /* or other suitable maximum line size */
		while (fgets(line, sizeof line, fp) != 0) /* read a line */
		{
			if (count == (lineaNum - 1)) {
				if (line[0] == 48) {
					fputs("1", fp);
				}
				count++;
			} else if (count == lineaNum) {
				printf("%s", line);
				fclose(fp);
			} else {
				count++;
			}
		}
		fclose(fp);
	}
}

void updateDato(char *dato, char *archivo) { //VER *archivo
	FILE *fp; // @suppress("Type cannot be resolved")
	fp = fopen(archivo, "r+");

	if (!fp) {
		errores(4, archivo);
	}
	int lineaNum = verificarCoincidenciaKey(archivo, recuperarKeyString(dato));
	if (lineaNum == 0) {
		errores(5, recuperarKeyString(dato));
	} else {
		char line[4096]; /* or other suitable maximum line size */
		int count = 0;
		while (fgets(line, sizeof line, fp) != 0) /* read a line */
		{
			if (count == (lineaNum - 1)) {
				fputs("0", fp);
				fputs(dato, fp);
				fputs("\0", fp);
				//XXX aca debe blanquear todo lo que le siga para que no quede basura al final de la isercion

				printf("%s\n", dato);
				count++;
			} else {
				count++;
			}
		}
	}
}

void getDato(char *key, char *archivo) {
	FILE *fil; // @suppress("Type cannot be resolved")

	int num = verificarCoincidenciaKey(archivo, key);
	fil = fopen(archivo, "r"); //No verifica cuando no existe el archivo

	if (!fil) {
		errores(4, archivo);
	}

	if (num == 0) {
		errores(5, key);
	} else {
		char line[4096];
		int count = 0;
		while (fgets(line, sizeof line, fil) != 0) {
			if (count == num) {
				printf("%s", line + 1);
				fclose(fil);
			} else {
				count++;
			}
		}
	}
}

void getDatoFilter(char *campo, char *operador, char *valor, char *archivo) {
	FILE *fil; // @suppress("Type cannot be resolved")

	fil = fopen(archivo, "r"); //No verifica cuando no existe el archivo

	if (!fil) {
		errores(4, archivo);
	}

	char line[4096];
	int count = 0;

	while (!feof(fil)) {
		fgets(line, 4096, fil);
		if (line[0] == 48) { // 48 = 0 en ascii

			char *dat = buscarClaveValor(line, campo);

			if (dat) {

//			eq: igual
//			ne: distinto
//			gt : Mayor que
//			lt : Menor que
//			gte : Mayor o igual que
//			lte : Menor o o igual quevalor
//			cnt : el atributo contiene el valor.

				if (strcmp(operador, "eq") == 0) {
					// XXX ahora vamos a hacer que lo muestre por pantalla pero yo lo retornaria y que se muestre en otro lado
					if (strcmp(dat, trim(valor)) == 0) {
						printf("%s", line);
					}
				} else if (strcmp(operador, "ne") == 0) {
					if (strcmp(dat, trim(valor)) != 0) {
						printf("%s", line);
					}
				} else if (strcmp(operador, "gt") == 0) {
					double fdato = atof(dat);
					double fvalor = atof(valor);
					// esto es la mierda de dificil porque el redondeo de los floats es imprecisio y horrible
					if (fdato == 0.0) {
						errores(7, dat);
					}
					if (fvalor == 0.0) {
						errores(7, valor);
					}

					// XXX Por ahora se lo deja asi pero hay que revisarlo porque puede tirar inconsistencias con los decimales por temas de redondeo
					if (fdato > fvalor) {
						printf("%s", line);
					}
				} else if (strcmp(operador, "lt") == 0) {

					double fdato = atof(dat);
					double fvalor = atof(valor);
					// esto es la mierda de dificil porque el redondeo de los floats es imprecisio y horrible
					if (fdato == 0.0) {
						errores(7, dat);
					}
					if (fvalor == 0.0) {
						errores(7, valor);
					}

					// XXX Por ahora se lo deja asi pero hay que revisarlo porque puede tirar inconsistencias con los decimales por temas de redondeo
					if (fdato < fvalor) {
						printf("%s", line);
					}
				} else if (strcmp(operador, "gte") == 0) {

					double fdato = atof(dat);
					double fvalor = atof(valor);
					// esto es la mierda de dificil porque el redondeo de los floats es imprecisio y horrible
					if (fdato == 0.0) {
						errores(7, dat);
					}
					if (fvalor == 0.0) {
						errores(7, valor);
					}

					// XXX Por ahora se lo deja asi pero hay que revisarlo porque puede tirar inconsistencias con los decimales por temas de redondeo
					if (fdato >= fvalor) {
						printf("%s", line);
					}
				} else if (strcmp(operador, "lte") == 0) {

					double fdato = atof(dat);
					double fvalor = atof(valor);
					// esto es la mierda de dificil porque el redondeo de los floats es imprecisio y horrible
					if (fdato == 0.0) {
						errores(7, dat);
					}
					if (fvalor == 0.0) {
						errores(7, valor);
					}

					// XXX Por ahora se lo deja asi pero hay que revisarlo porque puede tirar inconsistencias con los decimales por temas de redondeo
					if (fdato <= fvalor) {
						printf("%s", line);
					}
				} else if (strcmp(operador, "cnt") == 0) {
					char* dato = strstr(dat, valor);
					if (dato) {
						printf("%s", line);
					}

				} else {
					errores(6, operador);
				}
			}
		}
		// FIXME no se por que mierda pincha aca
		// se supone que deberia recorrer el archivo completo pero si saco el exit tira error T_T
		// XXX hay que revisar porque el error lo tira cuando hay alguna linea en blanco

//		exit(0);
	}

//	fclose(fil);
}

int main(int argc, char *argv[]) {
	char *dato = malloc(4096);

	int accion = 0;

	if (accion == 1) {
		if (argv[2][0] == '-') {
			errores(1, "");
		}
	}

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

		if (argv[2][0] == '-') {
			errores(1, "");
		}

		if ((!argv[3]) || (strcmp(argv[3], "-value") != 0)) {

//			char * pepino;
//			freopen(pepino, "r", stdin);
//			printf("%s", pepino);
			errores(1, "");
			// XXX aca hay que verificar si no hay nada en el stdin
		} else {

			dato = argv[4];
//			printf("%s\n", argv[4]);
		}

		// XXX no se implementa porque hay que corregir la funcion que comprueba el JSON
//		if (formatoJson(dato) == 1) {
		agregarDato(dato, argv[2]);
//		} else {
//			printf("%s\n", dato);
//			errores(8, dato);
//		}
		break;

	case 'r':

		if (strcmp(argv[1], "rem") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}
		if (strcmp(argv[3], "-key") != 0) {
			errores(2, argv[3]);
		}
		removerDato(argv[2], argv[4]);
		break;

	case 'u':
		if (strcmp(argv[1], "upd") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}
		dato = argv[4];
		updateDato(dato, argv[2]);
		break;

	case 'g':
		if (strcmp(argv[1], "get") != 0) {
			errores(2, argv[1]);
		}
		if (argv[2][0] == '-') {
			errores(1, "");
		}

		if (strcmp(argv[3], "-key") == 0) {
			getDato(argv[4], argv[2]);
		} else if (strcmp(argv[3], "-filter") == 0) {
			getDatoFilter(argv[4], argv[5], argv[6], argv[2]);
		} else {
			errores(2, argv[3]);
		}

		break;

	default:
		errores(2, argv[1]);
	}

	exit(0);
}

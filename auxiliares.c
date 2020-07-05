char* substr(char* cadena, int comienzo, int longitud = 0) {
	if (longitud == 0)
		longitud = strlen(cadena) - comienzo;

	char *nuevo = (char*) malloc(sizeof(char) * (longitud + 1));
	nuevo[longitud] = '\0';
	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

char* substrHasta(char* cadena, int comienzo, char caracter) {

	char *nuevo = (char*) malloc(sizeof(char) * (1));

	int longitud = EncontrarPrimeraPosicion(nuevo, caracter);

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

int EncontrarPrimeraPosicion(const char* palabra, char caracter) {
	for (int i = 0; i < longitud(palabra); i++) {
		if (palabra[i] == caracter) {
			return i + 1;
		}
	}

	return 0; //No se encontro el carácter
}


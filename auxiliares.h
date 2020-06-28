/*
 * auxiliares.h
 *
 *  Created on: 28 jun. 2020
 *      Author: IVANB
 */

#ifndef AUXILIARES_H_
#define AUXILIARES_H_

char* substr(char* cadena, int comienzo, int longitud = 0) {
	if (longitud == 0)
		longitud = strlen(cadena) - comienzo;

	char *nuevo = (char*) malloc(sizeof(char) * (longitud + 1));
	nuevo[longitud] = '\0';
	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

char* substrHasta(char* cadena, int comienzo, int longitud = 0) {
	if (longitud == 0)
		longitud = strlen(cadena) - comienzo;

	char *nuevo = (char*) malloc(sizeof(char) * (longitud + 1));
	nuevo[longitud] = '\0';
	strncpy(nuevo, cadena + comienzo, longitud);

	return nuevo;
}

#endif /* AUXILIARES_H_ */

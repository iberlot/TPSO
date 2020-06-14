#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void agregarUsuarioAlJSON(int edad, char nombre, long dni) {
//	printf("Nombre: %s\n", nombre);
	printf("Edad: %d\n", edad);
	printf("Documento: %d\n", dni);
}

void pedirDatos() {
	char nombre[20];
	int edad = 0;
	long dni = 0;

	printf("Ingrese su nombre: \n");
	scanf("%s", &nombre);

	bool verificar = true;
	while (verificar == true) {
		printf("Ingrese su edad: \n");
		scanf("%d", &edad);
		if (edad <= 0) {
			printf("Esa no puede ser su edad.\nIngresela de nuevo!\n");
		} else {
			verificar = false;
		}
	}

	printf("Ingrese su documento: \n");
	scanf("%ld", &dni);

	void (*addUsuario)(int, char, long);
	addUsuario = &agregarUsuarioAlJSON;
	(*addUsuario)(edad, nombre, dni);
}

int main() {
	int opcion = 0;
	bool verificar = true;

	while (verificar == true) {
		printf(
				"Pulse 1 para agregar un nuevo usuario\n2 Para solicitar ayuda\n3 para remover un usuario\n4 para modificar un usuario\n5 leer un usuario");
		scanf("%d", &opcion);
		switch (opcion) {
		case 1:
			puts("ALTA DE USUARIO");
			verificar = false;
			void (*addUsuario)();
			addUsuario = &pedirDatos;
			(*addUsuario)();

			break;

		default:
			printf("Error!\nIntentelo de nuevo:\n");
		}
	}

	return 0;
}

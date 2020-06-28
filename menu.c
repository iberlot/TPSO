#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	int opcion = 0;
	printf("Pulse 1 para agregar un nuevo usuario\n2 Para solicitar ayuda\n3 para remover un usuario\n4 para modificar un usuario\n5 leer un usuario");
	scanf("%d", &opcion);
	return 0;
}

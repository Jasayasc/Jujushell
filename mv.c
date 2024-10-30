#include "mv.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void move_file(char *source, char *destination) {
    if (source == NULL) {
            printf("Error: Faltan argumentos para ejecutar.\n");
            return;
    }

	// Check if the source is a directory
    struct stat source_stat;
    if (stat(source, &source_stat) == 0 && S_ISDIR(source_stat.st_mode)) {
         // Move directory using mv()
         if (rename(source, destination) == -1) {
             perror("Error al mover el directorio");
             return;
            }

    	printf("Directorio movido exitosamente.\n");
    }else{
	if (rename(source, destination) == -1) {
            perror("Error al mover el fichero");
            return;
        }

        printf("Fichero movido exitosamente.\n");
    }
}

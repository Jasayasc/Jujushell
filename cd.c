
#include "cd.h"

char cwd[1024];
void change_directory(char *path){
    // Intenta cambiar el directorio
    if (chdir(path) == 0) {
        printf("Se cambio exitosamente al directorio: %s\n", path);
    } else {
        perror("Error cambiando de directorio");
    }
}

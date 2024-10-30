#include "mkdir.h"

void make_directory(const char *path) {
    // Intenta crear el directorio con permisos 0777
    if (mkdir(path, 0777) == -1) {
        perror("Error creando el directorio");
    }
}
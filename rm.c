#include "rm.h"
int rm(const char *path) {
    // Intenta eliminar el archivo
    if (unlink(path) == -1) {
        perror("Error eliminando el archivo");
        return -1;
    }
    return 0;
}
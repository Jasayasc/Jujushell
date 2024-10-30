#include "rmdir.h"

int remove_entry(const char *path) {
    struct stat statbuf;

    // Obtener información del archivo o directorio
    if (lstat(path, &statbuf) == -1) {
        perror("Error obteniendo información del archivo");
        return -1;
    }

    // Si es un directorio, llamar a la función de eliminación recursiva
    if (S_ISDIR(statbuf.st_mode)) {
        // Abrir el directorio
        DIR *dir = opendir(path);
        if (dir == NULL) {
            perror("Error abriendo directorio");
            return -1;
        }

        // Iterar sobre los elementos del directorio
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            // Ignorar las entradas "." y ".."
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Construir la ruta completa del elemento
            char entry_path[PATH_MAX];
            snprintf(entry_path, PATH_MAX, "%s/%s", path, entry->d_name);

            // Eliminar recursivamente el elemento
            if (remove_entry(entry_path) == -1) {
                // Si hay un error, cerrar el directorio y devolver el error
                closedir(dir);
                return -1;
            }
        }

        // Cerrar el directorio después de procesar todos los elementos
        closedir(dir);
    }

    // Eliminar el archivo o directorio
    if (remove(path) == -1) {
        perror("Error eliminando archivo o directorio");
        return -1;
    }

    return 0;
}

// Función para eliminar un directorio
int remove_directory(const char *path, int recursive) {
    if (recursive) {
        // Eliminar recursivamente el directorio
        return remove_entry(path);
    } else {
        // Eliminar un directorio vacío
        if (rmdir(path) == -1) {
            perror("Error eliminando directorio");
            return -1;
        }
        return 0;
    }
}
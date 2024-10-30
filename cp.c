#include "cp.h"

void copy_file(char *src, char *dst, int recursive) {
    if (is_directory(src)) {
        if (!recursive) {
            printf("Error: '%s' es un directorio (omitir '-r' para copiar directorios).\n", src);
            return;
        }
        copy_directory_recursively(src, dst);
    } else {
        FILE *source = fopen(src, "rb");
        if (source == NULL) {
            perror("Error al abrir archivo de origen");
            return;
        }
        FILE *destination = fopen(dst, "wb");
        if (destination == NULL) {
            perror("Error al abrir archivo de destino");
            fclose(source);
            return;
        }
        int byte;
        while ((byte = fgetc(source)) != EOF) {
            fputc(byte, destination);
        }
        fclose(source);
        fclose(destination);
        printf("Archivo copiado con éxito.\n");
    }
}

void copy_directory_recursively(const char *src, const char *dst) {
    mkdir(dst, 0777); // Crea el directorio destino con permisos adecuados
    DIR *dir = opendir(src);
    if (dir == NULL) {
        perror("Error al abrir directorio");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; // Ignorar directorios . y ..

        char src_path[1024];
        char dst_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dst, entry->d_name);

        if (is_directory(src_path)) {
            copy_directory_recursively(src_path, dst_path);
        } else {
            // Aquí pasamos siempre 0 para 'recursive' ya que estamos manejando archivos individuales dentro del directorio
            copy_file(src_path, dst_path, 0);
        }
    }
    closedir(dir);
}

int is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
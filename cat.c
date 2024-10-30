#include "cat.h"

void cat(const char *path) {
    int fd;
    char buffer[1024];
    ssize_t bytesRead;

    // Abre el archivo en modo lectura
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error abriendo el archivo");
        return;
    }

    // Lee el contenido del archivo y lo escribe en la salida estándar
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error escribiendo en la salida estándar");
            close(fd);
            return;
        }
    }

    if (bytesRead == -1) {
        perror("Error leyendo el archivo");
    }

    // Cierra el archivo
    close(fd);
}
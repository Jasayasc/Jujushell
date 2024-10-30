#include "echo.h"

void echo(int argc, char *argv[]) {
    int fd = STDOUT_FILENO;  // Por defecto, salida estándar
    int append = 0;
    char *message[1024];
    int i, j = 0;

    // Busca si hay un símbolo de redirección (>) en los argumentos
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], ">") == 0) {
            if (i + 1 < argc) {
                // Abre el archivo en modo de escritura (crea si no existe)
                fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("Error abriendo el archivo");
                    return;
                }
                break;
            } else {
                fprintf(stderr, "Uso: echo [mensaje] > [archivo]\n");
                return;
            }
        } else if (strcmp(argv[i], ">>") == 0) {
            if (i + 1 < argc) {
                // Abre el archivo en modo de escritura (crea si no existe) y añade al final
                fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1) {
                    perror("Error abriendo el archivo");
                    return;
                }
                append = 1;
                break;
            } else {
                fprintf(stderr, "Uso: echo [mensaje] >> [archivo]\n");
                return;
            }
        } else {
            message[j++] = argv[i];
        }
    }

    // Escribe el mensaje en la salida estándar o en el archivo
    for (i = 0; i < j; i++) {
        if (write(fd, message[i], strlen(message[i])) == -1) {
            perror("Error escribiendo en la salida");
            if (fd != STDOUT_FILENO) close(fd);
            return;
        }
        if (i < j - 1) {
            if (write(fd, " ", 1) == -1) {
                perror("Error escribiendo en la salida");
                if (fd != STDOUT_FILENO) close(fd);
                return;
            }
        }
    }
    if (write(fd, "\n", 1) == -1) {
        perror("Error escribiendo en la salida");
    }

    // Cierra el archivo si no es la salida estándar
    if (fd != STDOUT_FILENO) {
        close(fd);
    }
}

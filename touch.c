#include "touch.h"

void touch(const char *path, int modify_time) {
    int fd;
    struct stat statbuf;  // Declaraci�n de statbuf
    struct timespec times[2];

    // Intenta abrir el archivo con las banderas O_CREAT, O_WRONLY y O_NOCTTY
    fd = open(path, O_WRONLY | O_CREAT | O_NOCTTY, 0644);

    if (fd == -1) {
        perror("Error creando o abriendo el archivo");  // perror ahora reconocido por el compilador
        return;
    }

    if (modify_time) {
        // Obt�n los tiempos actuales del archivo
        if (fstat(fd, &statbuf) != -1) {
            times[0] = statbuf.st_atim;  // Mant�n el tiempo de acceso
            times[1].tv_nsec = UTIME_NOW;  // Actualiza el tiempo de modificaci�n a ahora
            utimensat(AT_FDCWD, path, times, 0);
        }
    }

    // Cierra el archivo si se abri�/cre� exitosamente
    close(fd);
}
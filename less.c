#include "less.h"

#define PAGE_SIZE 20

void less(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return;
    }

    char buffer[256];
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
        if (++line_count >= PAGE_SIZE) {
            printf("\n-- Más -- (Presiona 'q' para salir) --");

            int c;
            while ((c = getchar()) != 'q' && c != EOF && c != '\n') {
                // No hacer nada, solo esperar a que se presione 'q'
            }

            if (c == 'q' || c == EOF) {
                break;
            }

            line_count = 0;
        }
    }

    fclose(file);
}

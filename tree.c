#include "tree.h"

void print_tree(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;

    // Abrir el directorio
    if (!(dir = opendir(path))) {
        perror("opendir");
        return;
    }

    // Leer todos los elementos del directorio
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Ignorar . y ..
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            // Imprimir la entrada del directorio con la indentación adecuada
            for (int i = 0; i < depth - 1; i++) {
                printf("|   ");
            }
            printf("|-- ");
            printf("%s\n", entry->d_name);

            // Recursivamente imprimir el árbol para el subdirectorio
            char path_buf[1024];
            snprintf(path_buf, sizeof(path_buf), "%s/%s", path, entry->d_name);
            print_tree(path_buf, depth + 1);
        }
    }

    // Cerrar el directorio
    closedir(dir);
}

void tree(const char *path) {
    printf("%s\n", path);
    print_tree(path, 1);
}
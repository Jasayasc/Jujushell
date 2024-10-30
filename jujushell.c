#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ls.h"
#include "mv.h"
#include "cp.h"
#include "cd.h"
#include "touch.h"
#include "cat.h"
#include "echo.h"
#include "rm.h"
#include "mkdir.h"
#include "rmdir.h"

#include "pwd.h"
#include "less.h"
#include "clear.h"
#include "tree.h"
#include "w.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

void prompt() {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("%s$jujushell> ", cwd);
}

void execute_command(char *args[], int arg_count) {
    if (arg_count == 0) {
        // No se ingresó ningún comando
        return;
    }

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(args[0], "ls") == 0) {
        if (arg_count > 1 && strcmp(args[1], "-l") == 0) {
            if (arg_count > 2) {
                list_directory(args[2], 1);  // Listado detallado del directorio especificado
            } else {
                list_directory(".", 1);  // Listado detallado del directorio actual
            }
        } else if (arg_count > 1) {
            list_directory(args[1], 0);  // Listado simple del directorio especificado
        } else {
            list_directory(".", 0);  // Listado simple del directorio actual
        }
    } else if (strcmp(args[0], "cp") == 0) {
      int recursive = 0;
      int index = 1;
      if (arg_count > 1 && strcmp(args[1], "-r") == 0) {
          recursive = 1;
          index++; // Ajusta el índice para los siguientes argumentos
      }
      if (arg_count > index + 1) {
          copy_file(args[index], args[index + 1], recursive);
      } else {
          fprintf(stderr, "Uso: cp [-r] <fuente> <destino>\n");
      }
    } else if (strcmp(args[0], "cd") == 0) {
        if (arg_count > 1) {
            change_directory(args[1]);
        } else {
            fprintf(stderr, "Uso: cd <directorio>\n");
        }
    } else if (strcmp(args[0], "mv") == 0) {
        if (arg_count > 2) {
            move_file(args[1], args[2]);
        } else {
            fprintf(stderr, "Uso: mv <fuente> <destino>\n");
        }
    } else if (strcmp(args[0], "touch") == 0) {
      if (arg_count > 1 && strcmp(args[1], "-m") == 0) {
        if (arg_count > 2) {
            touch(args[2], 1);  // Llama a touch con modificación de tiempo
        } else {
            fprintf(stderr, "Uso: touch -m <archivo>\n");
        }
      } else if (arg_count > 1) {
        touch(args[1], 0);  // Llama a touch sin modificación de tiempo
      } else {
        fprintf(stderr, "Uso: touch <archivo>\n");
      }
    } else if (strcmp(args[0], "cat") == 0) {
        if (arg_count > 1) {
            cat(args[1]);
        } else {
            fprintf(stderr, "Uso: cat <archivo>\n");
        }
    } else if (strcmp(args[0], "echo") == 0) {
        echo(arg_count, args);
    } else if (strcmp(args[0], "pwd") == 0) {
        print_working_directory();
    } else if (strcmp(args[0], "less") == 0) {
        if (arg_count > 1) {
            less(args[1]);
        } else {
            fprintf(stderr, "Uso: less <archivo>\n");
        }
    }else if (strcmp(args[0], "rm") == 0) {
        if (arg_count > 1) {
            rm(args[1]);
        } else {
            fprintf(stderr, "Uso: less <archivo>\n");
        }
    }else if (strcmp(args[0], "clear") == 0) {
        clear_screen();
    }else if (strcmp(args[0], "tree") == 0) {
      if (arg_count > 1) {
        tree(args[1]);
      } else {
        tree(".");
      }
    }else if (strcmp(args[0], "mkdir") == 0) {
        if (arg_count > 1) {
            make_directory(args[1]);
        } else {
            fprintf(stderr, "Uso: mkdir <nombre_directorio>\n");
        }
    }else if (strcmp(args[0], "rmdir") == 0) {
           if (arg_count > 1) {
            if (strcmp(args[1], "-r") == 0 && arg_count > 2) {
                remove_directory(args[2], 1);
            } else {
                remove_directory(args[1], 0);
            }
        } else {
            fprintf(stderr, "Uso: rmdir [-r] <directorio>\n");
        }
        
    }else if (strcmp(args[0], "w") == 0) {
        who();
    } else {
        fprintf(stderr, "Comando desconocido: %s\n", args[0]);
    }
    
    
    
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    char *token;

    while (1) {
        // Mostrar el prompt
        prompt();

        // Leer la entrada del usuario
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remover el salto de línea al final de la entrada
        input[strcspn(input, "\n")] = 0;

        // Parsear la entrada en argumentos
        int arg_count = 0;
        token = strtok(input, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
                args[arg_count] = NULL;

        // Ejecutar el comando solo si se proporcionaron argumentos
        if (arg_count > 0) {
            execute_command(args, arg_count);
        }
    }

    return 0;
}
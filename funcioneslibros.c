#include <stdio.h>
#include "s11_libros_cabecera.h"

void inicializar_biblioteca(Biblioteca *biblioteca) {
    biblioteca->total_libros = 0;
}

int validar_id_unico(Biblioteca *biblioteca, int id) {
    for (int i = 0; i < biblioteca->total_libros; i++) {
        if (biblioteca->libros[i].id == id) {
            return 0;
        }
    }
    return 1;
}

int agregar_libro(Biblioteca *biblioteca) {
    if (biblioteca->total_libros >= MAX_LIBROS) {
        printf("\nError: No se pueden agregar mas libros. Limite maximo alcanzado (%d libros).\n", MAX_LIBROS);
        return 0;
    }

    Libro nuevo_libro;

    do {
        printf("\nIngrese el ID del libro: ");
        if (scanf("%d", &nuevo_libro.id) != 1 || nuevo_libro.id <= 0) {
            printf("Error: Ingrese un ID valido (numero entero positivo).\n");
            while (getchar() != '\n');
            continue;
        }

        if (!validar_id_unico(biblioteca, nuevo_libro.id)) {
            printf("Error: El ID %d ya existe. Ingrese un ID unico.\n", nuevo_libro.id);
            while (getchar() != '\n');
            continue;
        }
        break;
    } while (1);

    do {
        printf("Ingrese el titulo del libro: ");
        if (fgets(nuevo_libro.titulo, MAX_TITULO, stdin) == NULL) {
            printf("Error al leer el titulo.\n");
            continue;
        }

        nuevo_libro.titulo[strcspn(nuevo_libro.titulo, "\n")] = 0;

        if (strlen(nuevo_libro.titulo) == 0) {
            printf("Error: El titulo no puede estar vacio.\n");
            continue;
        }
        break;
    } while (1);

    do {
        printf("Ingrese el autor del libro: ");
        if (fgets(nuevo_libro.autor, MAX_AUTOR, stdin) == NULL) {
            printf("Error al leer el autor.\n");
            continue;
        }

        nuevo_libro.autor[strcspn(nuevo_libro.autor, "\n")] = 0;

        if (strlen(nuevo_libro.autor) == 0) {
            printf("Error: El autor no puede estar vacio.\n");
            continue;
        }
        break;
    } while (1);

    do {
        printf("Ingrese el anio de publicacion: ");
        if (scanf("%d", &nuevo_libro.anio_publicacion) != 1 || 
            nuevo_libro.anio_publicacion < 0 || nuevo_libro.anio_publicacion > 2025) {
            printf("Error: Ingrese un anio valido.\n");
            continue;
        }
        break;
    } while (1);

    strcpy(nuevo_libro.estado, "Disponible");

    biblioteca->libros[biblioteca->total_libros] = nuevo_libro;
    biblioteca->total_libros++;

    printf("\nLibro agregado exitosamente!\n");
    return 1;
}

void mostrar_libros(Biblioteca *biblioteca) {
    if (biblioteca->total_libros == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }

    printf("\nLISTA COMPLETA DE LIBROS\n");
    printf("| %-4s | %-30s | %-20s | %-4s | %-12s |\n", 
           "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");

    for (int i = 0; i < biblioteca->total_libros; i++) {
        printf("| %-4d | %-30.30s | %-20.20s | %-4d | %-12s |\n",
               biblioteca->libros[i].id,
               biblioteca->libros[i].titulo,
               biblioteca->libros[i].autor,
               biblioteca->libros[i].anio_publicacion,
               biblioteca->libros[i].estado);
    }
    printf("Total de libros: %d/%d\n", biblioteca->total_libros, MAX_LIBROS);
}

void buscar_libro(Biblioteca *biblioteca) {
    if (biblioteca->total_libros == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }

    int opcion;
    printf("\n BUSCAR LIBRO\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por titulo\n");
    printf("Seleccione una opcion: ");

    if (scanf("%d", &opcion) != 1) {
        printf("Opcion invalida.\n");
        return;
    }

    int encontrado = 0;

    if (opcion == 1) {
        int id_buscar;
        printf("Ingrese el ID del libro: ");
        if (scanf("%d", &id_buscar) != 1) {
            printf("ID invalido.\n");
            while (getchar() != '\n');
            return;
        }

        for (int i = 0; i < biblioteca->total_libros; i++) {
            if (biblioteca->libros[i].id == id_buscar) {
                printf("\nLIBRO ENCONTRADO:\n");
                printf("=====================================\n");
                printf("ID: %d\n", biblioteca->libros[i].id);
                printf("Titulo: %s\n", biblioteca->libros[i].titulo);
                printf("Autor: %s\n", biblioteca->libros[i].autor);
                printf("Anio: %d\n", biblioteca->libros[i].anio_publicacion);
                printf("Estado: %s\n", biblioteca->libros[i].estado);
                printf("=====================================\n");
                encontrado = 1;
                break;
            }
        }
    } else if (opcion == 2) {
        char titulo_buscar[MAX_TITULO];
        printf("Ingrese el titulo del libro: ");
        if (fgets(titulo_buscar, MAX_TITULO, stdin) == NULL) {
            printf("Error al leer el titulo.\n");
            return;
        }

        titulo_buscar[strcspn(titulo_buscar, "\n")] = 0;

        for (int i = 0; i < biblioteca->total_libros; i++) {
            if (strstr(biblioteca->libros[i].titulo, titulo_buscar) != NULL) {
                if (!encontrado) {
                    printf("\nLIBROS ENCONTRADOS:\n");
                }
                printf("ID: %d\n", biblioteca->libros[i].id);
                printf("Titulo: %s\n", biblioteca->libros[i].titulo);
                printf("Autor: %s\n", biblioteca->libros[i].autor);
                printf("Anio: %d\n", biblioteca->libros[i].anio_publicacion);
                printf("Estado: %s\n", biblioteca->libros[i].estado);
                encontrado = 1;
            }
        }
    } else {
        printf("Opcion invalida.\n");
        return;
    }
}

void actualizar_estado(Biblioteca *biblioteca) {
    if (biblioteca->total_libros == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }

    int id_libro;
    printf("\nACTUALIZAR ESTADO DE LIBRO\n");
    printf("Ingrese el ID del libro: ");

    if (scanf("%d", &id_libro) != 1) {
        printf("ID invalido.\n");
        return;
    }

    for (int i = 0; i < biblioteca->total_libros; i++) {
        if (biblioteca->libros[i].id == id_libro) {
            printf("\nLibro encontrado: %s\n", biblioteca->libros[i].titulo);
            printf("Estado actual: %s\n", biblioteca->libros[i].estado);

            if (strcmp(biblioteca->libros[i].estado, "Disponible") == 0) {
                strcpy(biblioteca->libros[i].estado, "Prestado");
                printf("Estado actualizado a: Prestado\n");
            } else {
                strcpy(biblioteca->libros[i].estado, "Disponible");
                printf("Estado actualizado a: Disponible\n");
            }
            return;
        }
    }

    printf("No se encontro un libro con ID %d.\n", id_libro);
}

void eliminar_libro(Biblioteca *biblioteca) {
    if (biblioteca->total_libros == 0) {
        printf("\nNo hay libros registrados en la biblioteca.\n");
        return;
    }

    int id_libro;
    printf("Ingrese el ID del libro a eliminar: ");

    if (scanf("%d", &id_libro) != 1) {
        printf("ID invalido.\n");
        return;
    }

    for (int i = 0; i < biblioteca->total_libros; i++) {
        if (biblioteca->libros[i].id == id_libro) {
            printf("\nLibro a eliminar: %s - %s\n", 
                   biblioteca->libros[i].titulo, biblioteca->libros[i].autor);

            char confirmacion;
            printf("Esta seguro de eliminar este libro? (s/n): ");
            scanf(" %c", &confirmacion);

            if (confirmacion == 's' || confirmacion == 'S') {
                for (int j = i; j < biblioteca->total_libros - 1; j++) {
                    biblioteca->libros[j] = biblioteca->libros[j + 1];
                }
                biblioteca->total_libros--;
                printf("Libro eliminado exitosamente.\n");
            } else {
                printf("Eliminacion cancelada.\n");
            }
            return;
        }
    }

    printf("No se encontro un libro con ID %d.\n", id_libro);
}

void mostrar_menu() {
    printf("\nSISTEMA DE GESTION DE BIBLIOTECA\n");
    printf("1. Agregar libro\n");
    printf("2. Mostrar todos los libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar estado de libro\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf("Seleccione una opcion: ");
}


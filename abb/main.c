// #include "testing.h"
// #include "pruebas_abb.c"
// #include <stdlib.h>
// #include <stdio.h>

// void pruebas_abb_estudiante(void);

// /* ******************************************************************
//  *                        PROGRAMA PRINCIPAL
//  * *****************************************************************/

// int main(int argc, char *argv[])
// {
//     printf("~~~ PRUEBAS  ESTUDIANTES~~~\n");
//     pruebas_abb_estudiante();

//     return failure_count() > 0;
// }

#include "testing.h"
#include "abb_pruebas.c"
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_abb_estudiante(void);
void pruebas_volumen_estudiante(size_t);

int main(int argc, char *argv[]) {
    // if (argc > 1) {
    //     // Asumimos que nos están pidiendo pruebas de volumen.
    //     long largo = strtol(argv[1], NULL, 10);
    //     pruebas_volumen_estudiante((size_t) largo);

    //     return failure_count() > 0;
    // }
    printf("\n~~~ PRUEBAS ~~~\n");
    pruebas_abb_estudiante();
    return 0;
}
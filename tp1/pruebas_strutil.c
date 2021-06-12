#include "testing.h"
#include "strutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>





char *splitted_example[] = {
    "asd","","", NULL
};


char *joined_example = "asd,,";


static void pruebas_split() {

    char **splitted = split(joined_example, ',');
    bool separado = true;
    for (size_t i = 0; splitted[i] != NULL; i++)
        separado &= strcmp(splitted[i], splitted_example[i]) == 0;

    print_test("El string se separo correctamente", separado);

    free_strv(splitted);
}


void pruebas_strutil() {
    pruebas_split();
}

int main(void) {
    pruebas_strutil();
    return 0;  // Indica si falló alguna prueba.
}
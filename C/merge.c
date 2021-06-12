#include <stdio.h>


FILE merge(FILE *archivo1, FILE *archivo2){

}






void main(){
    FILE *archivo1 = fopen("archivo1.txt", "r");
    FILE *archivo2 = fopen("archivo2.txt", "r");
    if (!(archivo1 || archivo2)) return;
    merge(archivo1, archivo2);
    fclose(archivo1);
    fclose(archivo2);
}
#include <stdio.h>
#include <stdlib.h>
#include "./utils/functions.h"
#include "./test/test.h"

/* FUNCTIONS */

char *obtenerParametros()
{
    char *parametros = (char *)malloc(sizeof(char) * 100);
    printf("Ingrese los parametros (Longitud maxima de 100 caracteres): ");
    scanf("%s", parametros);
    return parametros;
}

int menu()
{
    printf("\n\n");
    printf("1. Automata\n");
    printf("2. Nodos\n");
    printf("3. Correr Tests\n");
    printf("4. Salir\n");
    printf("\n\n");
    printf("Ingrese una opcion: ");
    int opcion;
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > 4)
    {
        printf("Opcion invalida\n");
        return -1;
    }
    return opcion;
}

/* MAIN FUNCTION */

int main(int argc, char **argv)
{
    int action = 0;
    char *parametro = NULL;
    while (action != 4)
    {
        action = menu();
        switch (action)
        {
        case 1:
            parametro = obtenerParametros();
            clasificarNumeros(parametro);
            free(parametro);
            break;
        case 2:
            parametro = obtenerParametros();
            int result = evaluarExpresion(parametro);
            printf("%s = %d\n", parametro, result);
            free(parametro);
            break;
        case 3:
            correrTest();
            break;
        default:
            break;
        }
    }
    return 0;
}
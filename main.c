#include <stdio.h>
#include <stdlib.h>
#include "./utils/functions.h"
#include "./test/test.h"

/* FUNCTIONS */

#define ARCHIVO 1
#define CONSOLA 2

char *obtenerParametros(int origen)
{
    char *parametros = (char *)malloc(sizeof(char) * 100);
    printf("\n\n");
    if (origen == CONSOLA)
        printf("Ingrese los parametros (Longitud maxima de 100 caracteres): ");
    else
        printf("Ingrese la ruta al archivo (Longitud maxima de 100 caracteres): ");

    scanf("%s", parametros);
    fseek(stdin, 0, SEEK_END);

    if (origen == CONSOLA)
        return parametros;

    if (origen == ARCHIVO)
    {
        // char *flujo = (char *)malloc(sizeof(char) * 100);
        FILE *archivo;
        if (archivo = fopen(parametros, "r+b"))
        {
            char *buffer = NULL;
            size_t len;
            ssize_t bytes_read = getdelim(&buffer, &len, '\n', archivo);
            fclose(archivo);
            return buffer;
        }
        else
        {
            return NULL;
        }
    }
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
    int opcion = 0;
    scanf("%d", &opcion);
    fseek(stdin, 0, SEEK_END);
    if (opcion < 1 || opcion > 4)
    {
        printf("Opcion invalida\n");
        return -1;
    }
    return opcion;
}

int submenu()
{
    printf("\n\n");
    printf("1. Ingresar por archivo\n");
    printf("2. Ingresar por consola\n");
    printf("\n\n");
    printf("Ingrese una opcion: ");
    int opcion;
    scanf("%d", &opcion);
    fseek(stdin, 0, SEEK_END);
    if (opcion != 1 && opcion != 2)
    {
        printf("Opcion invalida\n");
        return -1;
    }
    return opcion;
}

char *obtenerDatos()
{
    int origen = 0;
    char *parametro = NULL;
    origen = submenu();
    if (origen == -1)
        return NULL;
    parametro = obtenerParametros(origen);
    if (parametro == NULL)
        return NULL;
    clearConsole();
    return parametro;
}

/* MAIN FUNCTION */

int main(int argc, char **argv)
{
    int action = 0;
    int origen = 0;
    char *parametro = NULL;
    clearConsole();
    while (action != 4)
    {
        action = menu();
        switch (action)
        {
            case 1:
                parametro = obtenerDatos();
                if (parametro == NULL){
                    printf("La entrada de datos no es valida.\n");
                    break;
                }
                clasificarNumeros(parametro);
                free(parametro);
                break;
            case 2:
                parametro = obtenerDatos();
                if (parametro == NULL){
                    printf("La entrada de datos no es valida.\n");
                    break;
                }
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
        jumpLine();
        wait();
        clearConsole();
    }
    return 0;
}

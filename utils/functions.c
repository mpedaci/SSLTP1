#include "functions.h"

int clasificarTipoNumero(char *string)
{
    Automata automataTipoDeNumero = construirAutomataParserTipoDeNumero();
    int resultado = parsearString(automataTipoDeNumero, string);
    return resultado;
}

void clasificarNumeros(char *string)
{
    char **numeros = separarString(string, '&'); 
    for (int i = 0; numeros[i] != NULL; i++)
    {
        int resultado = clasificarTipoNumero(numeros[i]);
        switch (resultado)
        {
        case DECIMAL:
            printf("El numero %s fue clasificado como DECIMAL \n", numeros[i]);
            break;
        case OCTAL:
            printf("El numero %s fue clasificado como OCTAL\n", numeros[i]);
            break;
        case HEXADECIMALT1:
        case HEXADECIMALT2:
            printf("El numero %s fue clasificado como HEXADECIMAL\n", numeros[i]);
            break;
        default:
            printf("Error al parsear el numero %s\n", numeros[i]);
            break;
        }
        free(numeros[i]);
    }
    free(numeros);
}

int evaluarExpresion(char *string)
{
    Rama *rama = construirRama(string);
    if (rama == NULL)
    {
        return -1;
    }
    else
    {
        int resultado = evaluarArbol(rama);
        return resultado;
    }
    /*
    int resultado = evaluarArbol(rama);
    printf("%s = %d", string, resultado);
    return resultado;
    */
}

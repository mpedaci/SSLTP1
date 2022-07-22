#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include "./automata/automata.h"
#include "./nodo/nodo.h"
#include "./utils.h"

#define DECIMAL 5
#define OCTAL 3
#define HEXADECIMALT1 4
#define HEXADECIMALT2 6
#define ERROR -1

int clasificarTipoNumero(char *string);

void clasificarNumeros(char *string);

int evaluarExpresion(char *string);

#endif /* FUNCTIONS_H_ */
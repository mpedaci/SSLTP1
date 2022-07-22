/*
 * nodos.h
 *
 *  Created on: Jul 20, 2022
 *      Author: utnso
 */

#ifndef NODOS_H_
#define NODOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"

typedef struct Nodo
{
    struct Nodo *izquierda;
    struct Nodo *derecha;
    int (*evalFunction)(struct Nodo *, struct Nodo *, int);
    int value;
} Rama;

Rama *construirRama(char *expresion);

int evaluarArbol(Rama *ramaBase);

#endif /* NODOS_H_ */

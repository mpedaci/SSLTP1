#pragma once
#include <string.h>
#include <stdlib.h>

typedef struct Array
{
	void *vals;
	int size;
} Array;

typedef struct Automata
{
	int **matriz;
	Array estadosFinales;
	Array diccionario;
	int estadoInicial;
} Automata;

/*
 * @brief Construye un automata
 * @params:
 *  - matrizDeTransiciones :: La matriz de transiciones, cada entrada representa el estado siguiente. Las filas son estados y las columnas las transiciones
 *  - estadoInicial :: El estado inicial del automata
 *  - estadosFinales :: Los estados finales del automata
 *  - diccionario :: Permite la traduccion entre un caracter y una columna de la matriz de transiciones
 */
Automata construirAutomata(int height, int width, int matrizDeTransiciones[height][width], int estadoInicial, int sizeFinales, int estadosFinales[sizeFinales], char *diccionario);

/*
 * @brief Devuelve el estado al que se llega al mandar una cadena por el automata, o -1 si falla el parseo.
 */
int parsearString(Automata automata, char *string);

/*
 * @brief Devuelve el estado al que se llega al mandar una cadena por el autoamta, o -1 si falla el parseo. Tambien aplica un efecto secundario utilizando el caracter con el que
 * se va a transicionar.
 */
int parsearStringConSideEffect(Automata automata, char *string, void (*sideEffect)(char, void *), void *buffer);

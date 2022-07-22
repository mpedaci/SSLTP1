#include "automata.h"

Automata construirAutomata(int height, int width, int matrizDeTransiciones[height][width], int estadoInicial, int sizeFinales, int estadosFinales[sizeFinales], char *diccionario)
{
	Automata automata;

	automata.estadoInicial = estadoInicial;
	automata.matriz = malloc(sizeof(int *) * height);

	for (int i = 0; i < height; i++)
	{
		automata.matriz[i] = malloc(sizeof(int) * width);
		for (int j = 0; j < width; j++)
		{
			automata.matriz[i][j] = matrizDeTransiciones[i][j];
		}
	}

	automata.estadosFinales.vals = malloc(sizeof(int) * sizeFinales);
	automata.estadosFinales.size = sizeFinales;

	for (int i = 0; i < sizeFinales; i++)
	{
		((int *)automata.estadosFinales.vals)[i] = estadosFinales[i];
	}

	automata.diccionario.vals = (void *)diccionario;
	automata.diccionario.size = strlen(diccionario);

	return automata;
}

int siguienteEstado(Automata automata, int estadoActual, char caracter)
{
	for (int i = 0; i < automata.diccionario.size; i++)
	{
		if (((char *)automata.diccionario.vals)[i] == caracter)
		{
			return (automata.matriz)[estadoActual][i];
		}
	}

	return -1;
}

int esEstadoFinal(Automata automata, int estado)
{
	for (int i = 0; i < automata.estadosFinales.size; i++)
	{
		if (((int *)automata.estadosFinales.vals)[i] == estado)
			return 1;
	}
	return 0;
}

void id(char x, void *y) {}

int parsearStringConSideEffect(Automata automata, char *string, void (*sideEffect)(char, void *), void *buffer)
{
	int estadoActual = automata.estadoInicial;
	int index = 0;

	while (string[index] != '\0')
	{
		int estado = siguienteEstado(automata, estadoActual, string[index]);
		if (estado == -1)
			return -1;
		sideEffect(string[index], buffer);
		estadoActual = estado;
		index++;
	}

	if (!esEstadoFinal(automata, estadoActual))
		return -1;

	return estadoActual;
}

int parsearString(Automata automata, char *string)
{
	return parsearStringConSideEffect(automata, string, id, NULL);
}

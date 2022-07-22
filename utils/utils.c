/*
 * aux.c
 *
 *  Created on: Jul 19, 2022
 *      Author: utnso
 */

#include "utils.h"

char **separarString(char *string, char caracter)
{
	int counter = 1;

	for (int i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == caracter)
			counter++;
	}

	char **stringSeparada = malloc(sizeof(char *) * (counter + 1));

	int pos = 0, last = 0;

	for (int i = 0; 1; i++)
	{
		if (string[i] == caracter || string[i] == '\0')
		{
			stringSeparada[pos] = malloc((sizeof(char) * (i - last + 1)));
			for (int j = last; j < i; j++)
			{
				stringSeparada[pos][j - last] = string[j];
			}
			stringSeparada[pos][i - last] = '\0';
			pos++;
			last = i + 1;
		}
		if (string[i] == '\0')
			break;
	}

	stringSeparada[counter] = NULL;

	return stringSeparada;
}

char *quitarMarcadorOctal(char *caracter)
{
	char *sinMarcador = malloc(strlen(caracter) - 1);
	for (int i = 1; caracter[i] != '\0'; i++)
	{
		sinMarcador[i - 1] = caracter[i];
	}
	return sinMarcador;
}

char *quitarMarcadorHexa(char *caracter)
{
	char *sinMarcador = malloc(strlen(caracter) - 2);
	for (int i = 2; caracter[i] != '\0'; i++)
	{
		sinMarcador[i - 2] = caracter[i];
	}
	return sinMarcador;
}

void append(int *numero, char caracter, int potencia)
{
	*numero = (*numero * potencia) + (caracter - '0');
}

void appendDecimal(char caracterNumerico, void *datos)
{
	append((int *)datos, caracterNumerico, 10);
}

void appendHex(char caracterNumerico, void *datos)
{
	append((int *)datos, caracterNumerico, 16);
}

void appendOctal(char caracterNumerico, void *datos)
{
	append((int *)datos, caracterNumerico, 8);
}

Automata construirAutomataParserTipoDeNumero()
{
	int matriz[7][18] = {{1, 5, 5, 5, 5, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1},
						 {-1, 3, 3, 3, 3, 3, 3, 3, -1, -1, -1, -1, -1, -1, -1, -1, 2, 2},
						 {6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1, -1},
						 {3, 3, 3, 3, 3, 3, 3, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1, -1},
						 {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1},
						 {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
	char *diccionario = "0123456789ABCDEFxX";
	int estadosFinales[] = {3, 4, 5, 6};
	// 5 decimal, 3 octal , 4 y 6 hexa
	return construirAutomata(7, 18, matriz, 0, 4, estadosFinales, diccionario);
}

Automata construirAutomataParserDec()
{
	int matriz[2][10] = {{-1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	char *diccionario = "0123456789";
	int estadosFinales[] = {1};
	return construirAutomata(2, 10, matriz, 0, 1, estadosFinales, diccionario);
}

Automata construirAutomataParserOctal()
{
	int matriz[2][8] = {{-1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1}};
	char *diccionario = "01234567";
	int estadosFinales[] = {1};
	return construirAutomata(2, 8, matriz, 0, 1, estadosFinales, diccionario);
}

Automata construirAutomataParserHex()
{
	int matriz[2][16] = {{-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	char *diccionario = "0123456789ABCDEF";
	int estadosFinales[] = {1};
	return construirAutomata(2, 16, matriz, 0, 1, estadosFinales, diccionario);
}

int getNumero(char *expresion)
{
	Automata automataParser = construirAutomataParserTipoDeNumero();
	int resultado = parsearString(automataParser, expresion);
	int *buffer = malloc(sizeof(int));
	*buffer = 0;

	switch (resultado)
	{
	case 5:
		parsearStringConSideEffect(construirAutomataParserDec(), expresion, appendDecimal, buffer);
		break;
	case 3:
		parsearStringConSideEffect(construirAutomataParserDec(), quitarMarcadorOctal(expresion), appendOctal, buffer);
		break;
	case 6:
		parsearStringConSideEffect(construirAutomataParserHex(), quitarMarcadorHexa(expresion), appendHex, buffer);
		break;
	case 4:
		parsearStringConSideEffect(construirAutomataParserHex(), quitarMarcadorHexa(expresion), appendHex, buffer);
		break;
	case -1:
		return -1;
		break;
	}

	return *buffer;
}

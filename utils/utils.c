#include "utils.h"

#define DECIMAL 5
#define CERO 1
#define OCTAL 3
#define HEXA1 6
#define HEXA2 4

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
	int matriz[8][19] = {{7,1, 5, 5, 5, 5, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1},
						 {-1,-1, 3, 3, 3, 3, 3, 3, 3, -1, -1, -1, -1, -1, -1, -1, -1, 2, 2},
						 {-1,6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1, -1},
						 {-1,3, 3, 3, 3, 3, 3, 3, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {-1,4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, -1, -1},
						 {-1,5, 5, 5, 5, 5, 5, 5, 5, 5, 5, -1, -1, -1, -1, -1, -1, -1, -1},
						 {-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
						 {-1,-1,5,5,5,5,5,5,5,5,5,-1,-1,-1,-1,-1,-1,-1,-1}};
	char *diccionario = "-0123456789ABCDEFxX";
	int estadosFinales[] = {3,1, 4, 5, 6};
	return construirAutomata(8, 19, matriz, 0, 5, estadosFinales, diccionario);
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
	char* expresionBase = NULL;

	switch (resultado)
	{
	case DECIMAL:
		parsearStringConSideEffect(construirAutomataParserDec(), expresion, appendDecimal, buffer);
		break;
	case OCTAL:
		expresionBase = quitarMarcadorOctal(expresion);
		parsearStringConSideEffect(construirAutomataParserDec(), expresionBase, appendOctal, buffer);
		free(expresionBase);
		break;
	case HEXA1:
		expresionBase = quitarMarcadorHexa(expresion);
		parsearStringConSideEffect(construirAutomataParserHex(),  expresionBase, appendHex, buffer);
		free(expresionBase);
		break;
	case HEXA2:
		expresionBase = quitarMarcadorHexa(expresion);
		parsearStringConSideEffect(construirAutomataParserHex(),  expresionBase, appendHex, buffer);
		free(expresionBase);
		break;
	case CERO:
		*buffer = 0;
	case -1:
		return -1;
		break;
	}

	int numero = *buffer;
	free(buffer);
	destruirAutomata(automataParser);

	return numero;
}

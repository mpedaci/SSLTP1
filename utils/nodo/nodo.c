#include "nodo.h"

int ramaEvalFunction(Rama *ramaDer, Rama *ramaIzq, int operador)
{
	int primeraExpresion = ramaIzq->evalFunction(ramaIzq->derecha, ramaIzq->izquierda, ramaIzq->value);
	int segundaExpresion = ramaDer->evalFunction(ramaDer->derecha, ramaDer->izquierda, ramaDer->value);
	char operadorPosta = (char)operador;

	switch (operadorPosta)
	{
	case '+':
		return primeraExpresion + segundaExpresion;
		break;
	case '-':
		return primeraExpresion - segundaExpresion;
		break;
	case '*':
		return primeraExpresion * segundaExpresion;
		break;
	}
	perror("Error evaluando!");
	return 0; // nunca llega aca
}

int numeroEvalFunction(Rama *ramaDer, Rama *ramaIzq, int numero)
{
	return numero;
}

char *construirSubstring(int first, int last, char *expresion)
{
	if (first >= last)
		return "";

	char *substring = malloc(last - first + 1);

	int cnt = 0;

	for (int i = first; i < last && expresion[i] != '\0'; i++)
	{
		cnt++;
		substring[i - first] = expresion[i];
	}

	substring[cnt + 1] = '\0';

	return substring;
}

int evaluarArbol(Rama *ramaBase)
{
	if (ramaBase == NULL)
	{
		printf("Error, arbol es nulo!\n");
		return 0;
	}
	return ramaBase->evalFunction(ramaBase->derecha, ramaBase->izquierda, ramaBase->value);
}

Rama *ramaVerificada(Rama *rama)
{
	if (rama->derecha == NULL || rama->izquierda == NULL)
	{
		printf("Error generando rama!\n");
		return NULL;
	}

	return rama;
}

Rama *construirRama(char *expresion)
{
	Rama *rama = malloc(sizeof(Rama));

	if (strcmp(expresion, "") == 0)
		return NULL;

	for (int i = 0; expresion[i] != '\0'; i++)
	{
		if (expresion[i] == '+' || expresion[i] == '-')
		{
			rama->izquierda = construirRama(construirSubstring(0, i, expresion));
			rama->derecha = construirRama(construirSubstring(i + 1, strlen(expresion), expresion));
			rama->evalFunction = ramaEvalFunction;
			rama->value = expresion[i];
			return ramaVerificada(rama);
		}
	}

	for (int j = 0; expresion[j] != '\0'; j++)
	{
		if (expresion[j] == '*')
		{
			rama->izquierda = construirRama(construirSubstring(0, j, expresion));
			rama->derecha = construirRama(construirSubstring(j + 1, strlen(expresion), expresion));
			rama->evalFunction = ramaEvalFunction;
			rama->value = expresion[j];
			return ramaVerificada(rama);
		}
	}

	rama->derecha = NULL;
	rama->izquierda = NULL;
	rama->evalFunction = numeroEvalFunction;

	int numero = getNumero(expresion);

	if (numero == -1)
	{
		printf("Error parseando numero\n");
		return NULL;
	}

	rama->value = numero;

	return rama;
}

#include "nodo.h"

int ramaEvalFunction(Rama *ramaDer, Rama *ramaIzq, int operador)
{
	int primeraExpresion = ramaIzq->evalFunction(ramaIzq->derecha, ramaIzq->izquierda, ramaIzq->value);
	int segundaExpresion = ramaDer->evalFunction(ramaDer->derecha, ramaDer->izquierda, ramaDer->value);
	char operadorPosta = (char)operador;
	free(ramaDer);
	free(ramaIzq);

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

	substring[cnt] = '\0';

	return substring;
}

int evaluarArbol(Rama *ramaBase)
{
	if (ramaBase == NULL)
	{
		printf("Error, arbol es nulo!\n");
		return 0;
	}
	Rama* ramaDerecha = ramaBase->derecha;
	Rama* ramaIzquierda = ramaBase->izquierda;
	int valor = ramaBase->value;
	free(ramaBase);
	return ramaBase->evalFunction(ramaDerecha, ramaIzquierda, valor);
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

void armarPartesDeRama(int index,Rama* rama,char* expresion){
	char* primeraExpresion = construirSubstring(0, index, expresion);
	char* segundaExpresion = construirSubstring(index + 1, strlen(expresion), expresion);
	rama->izquierda = construirRama(primeraExpresion);
	rama->derecha = construirRama(segundaExpresion);
	rama->evalFunction = ramaEvalFunction;
	rama->value = expresion[index];
	free(primeraExpresion);
	free(segundaExpresion);
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
			armarPartesDeRama(i,rama,expresion);
			return ramaVerificada(rama);
		}
	}

	for (int j = 0; expresion[j] != '\0'; j++)
	{
		if (expresion[j] == '*')
		{
			armarPartesDeRama(j,rama,expresion);
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

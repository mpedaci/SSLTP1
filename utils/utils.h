/*
 * aux.h
 *
 *  Created on: Jul 19, 2022
 *      Author: utnso
 */

#ifndef AUX_H_
#define AUX_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./automata/automata.h"

char **separarString(char *string, char fraseSeparadora);

void appendDecimal(char caracterNumerico, void *datos);

void appendHex(char caracterNumerico, void *datos);

void appendOctal(char caracterNumerico, void *datos);

Automata construirAutomataParserDec();

Automata construirAutomataParserOctal();

Automata construirAutomataParserHex();

Automata construirAutomataParserTipoDeNumero();

int getNumero(char *expresion);

#endif /* AUX_H_ */

#ifndef TEST_H_
#define TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include "../utils/functions.h"
/* #include "../utils/style/console.h" */

void red();
void green();
void white();
/* void shouldBe(char *a, char *b); */
void shouldBe(int a, int b);
void correrTest();
void jumpLine();
void clearConsole();
void wait();

#endif /* TEST_H_ */
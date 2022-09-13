#include "./test.h"

/* CONSOLE STYLE FUNCTIONS */

void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[1;32m");
}

void white()
{
    printf("\033[0m");
}

void describe(char *description, int level){
    if (level == 0)
        printf("->%s\n", description);
    else
        printf("---> %s\n", description);
}

void jumpLine(){
    printf("\n");
}

void clearConsole(){
    system("cls");
}

void wait(){
    system("pause");
}

/* LOGICAL TEST FUNCTION */

void shouldBe(int a, int b)
{
    printf("%d should be %d\n", a, b);
    if (a == b)
    {
        green();
        printf("   OK\n\n");
        white();
    }
    else
    {
        red();
        printf("   FAIL\n\n");
        white();
    }
}

/* MAIN FUNCTION */

void correrTest()
{
    clearConsole();
    /* Test Clasificador */
    describe("Test Clasificador de Palabras", 0);
    describe("123 debe ser Decimal", 1);
    shouldBe(clasificarTipoNumero("123"), DECIMAL);
    describe("0123 debe ser Octal", 1);
    shouldBe(clasificarTipoNumero("0123"), OCTAL);
    describe("0x589 debe ser Hexadecimal", 1);
    shouldBe(clasificarTipoNumero("0x589"), HEXADECIMALT1);
    describe("0439 debe ser Error", 1);
    shouldBe(clasificarTipoNumero("0439"), ERROR);
    describe("-48 debe ser un numero decimal",1);
    shouldBe(clasificarTipoNumero("-48"),DECIMAL);

    jumpLine();

    describe("Test Clasificador de Palabras Multiples", 0);
    char string[40] = "548&0439&0x589&0543&548";
    char** numeros = separarString(string,'&');
    describe("548&0439&0x589&0543&548 en el primer numero debe ser Decimal", 1);
    shouldBe(clasificarTipoNumero(numeros[0]), DECIMAL);
    describe("548&0439&0x589&0543&548 en el segundo numero debe ser Error", 1);
    shouldBe(clasificarTipoNumero(numeros[1]), ERROR);
    describe("548&0439&0x589&0543&548 en el tercero numero debe ser Hexadecimal", 1);
    shouldBe(clasificarTipoNumero(numeros[2]), HEXADECIMALT1);
    describe("548&0439&0x589&0543&548 en el cuarto numero debe ser Octal", 1);
    shouldBe(clasificarTipoNumero(numeros[3]), OCTAL);
    describe("548&0439&0x589&0543&548 en el quinto numero debe ser Decimal", 1);
    shouldBe(clasificarTipoNumero(numeros[4]), DECIMAL);

    jumpLine();

    describe("Test Operaciones", 0);
    describe("1+1 debe ser 2", 1);
    shouldBe(evaluarExpresion("1+1"), 2);
    describe("1-1 debe ser 0", 1);
    shouldBe(evaluarExpresion("1-1"), 0);
    describe("2*2 debe ser 4", 1);
    shouldBe(evaluarExpresion("2*2"), 4);
    describe("3+4*7+3-5 debe ser 29", 1);
    shouldBe(evaluarExpresion("3+4*7+3-5"), 29);
    describe("(1+1)&(2+3) debe ser Error", 1);
    shouldBe(evaluarExpresion("(1+1)&(2+3)"), ERROR);

    jumpLine();
    wait();
    clearConsole();
}
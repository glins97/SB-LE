/*
Universidade de Brasília - 2020/02
Software Básico - Turma A

Alunos:
    Gabriel Lins
    Jaqueline Gontijo
    Tiago Cruz
    Carol Ferreira
    Lucas Barros

*/

#ifndef EXIBIDOR_INIT
#define EXIBIDOR_INIT

#include <stdio.h>
#include <stdlib.h>
#include "classfile.h"
#include "leitor.h"

void printClassfile(Classfile *);
void printConstantPool(Classfile *);
void printFields(Classfile *);
void printMethods(Classfile *);
void printAttrs(Classfile *);

char *decode(Cp_info *cp, u2 sizeCP, u1 *code, u4 length, instrucao *instructions);
char *searchNameTag(u1 tag);
char *decodeUTF8String(Cp_info *cp);
char *decodeInstructionOP(Cp_info *cp, u2 index, u2 sizeCP);
char *decodeNINT(Cp_info *cp, u2 index, u1 tipo);
char *decodeAccessFlags(u2 flag);
char *sortFlags(char *flagsOrdemInversa);
double decodeDoubleInfo(Cp_info *cp);
uint64_t decodeLongInfo(Cp_info *cp);
int decodeIntegerInfo(Cp_info *cp);
float decodeFloatInfo(Cp_info *cp);
int setPrintOffset(int position, u1 offset);

#endif

/*
Universidade de Brasília - 2020/02
Software Básico - Turma A
Leitor/Exibidor de arquivo .class

Alunos:
Jaqueline Gutierri Coelho - 15/0131283
Tiago Cruz Valadares - 14/0164120
Lucas de Melo Rodrigues de Barros - 18/0022539
Gabriel Lins e Nobrega - 15/0079371
Caroline Ferreira Pinto - 16/0067766

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "classFileStruct.h"
#include "instructions.h"

const int contagem_enum = jsr_w - nop;

instrucao *construirinstructions(void)
{

	instrucao *instructions = malloc(contagem_enum * sizeof(instrucao));

	for (int i = 0; i < contagem_enum; i++)
	{
		switch (i)
		{
		case nop:
			strcpy(instructions[i].inst_nome, "nop");
			instructions[i].opcode = nop;
			instructions[i].argindex = 0;
			break;
		case aconst_null:
			strcpy(instructions[i].inst_nome, "aconst_null");
			instructions[i].opcode = aconst_null;
			instructions[i].argindex = 0;
			break;
		case iconst_m1:
			strcpy(instructions[i].inst_nome, "iconst_m1");
			instructions[i].opcode = iconst_m1;
			instructions[i].argindex = 0;
			break;
		case iconst_0:
			strcpy(instructions[i].inst_nome, "iconst_0");
			instructions[i].opcode = iconst_0;
			instructions[i].argindex = 0;
			break;
		case iconst_1:
			strcpy(instructions[i].inst_nome, "iconst_1");
			instructions[i].opcode = iconst_1;
			instructions[i].argindex = 0;
			break;
		case iconst_2:
			strcpy(instructions[i].inst_nome, "iconst_2");
			instructions[i].opcode = iconst_2;
			instructions[i].argindex = 0;
			break;
		case iconst_3:
			strcpy(instructions[i].inst_nome, "iconst_3");
			instructions[i].opcode = iconst_3;
			instructions[i].argindex = 0;
			break;
		case iconst_4:
			strcpy(instructions[i].inst_nome, "iconst_4");
			instructions[i].opcode = iconst_4;
			instructions[i].argindex = 0;
			break;
		case iconst_5:
			strcpy(instructions[i].inst_nome, "iconst_5");
			instructions[i].opcode = iconst_5;
			instructions[i].argindex = 0;
			break;
		case lconst_0:
			strcpy(instructions[i].inst_nome, "lconst_0");
			instructions[i].opcode = lconst_0;
			instructions[i].argindex = 0;
			break;
		case lconst_1:
			strcpy(instructions[i].inst_nome, "lconst_1");
			instructions[i].opcode = lconst_1;
			instructions[i].argindex = 0;
			break;
		case fconst_0:
			strcpy(instructions[i].inst_nome, "fconst_0");
			instructions[i].opcode = fconst_0;
			instructions[i].argindex = 0;
			break;
		case fconst_1:
			strcpy(instructions[i].inst_nome, "fconst_1");
			instructions[i].opcode = fconst_1;
			instructions[i].argindex = 0;
			break;
		case fconst_2:
			strcpy(instructions[i].inst_nome, "fconst_2");
			instructions[i].opcode = fconst_2;
			instructions[i].argindex = 0;
			break;
		case dconst_0:
			strcpy(instructions[i].inst_nome, "dconst_0");
			instructions[i].opcode = dconst_0;
			instructions[i].argindex = 0;
			break;
		case dconst_1:
			strcpy(instructions[i].inst_nome, "dconst_1");
			instructions[i].opcode = dconst_1;
			instructions[i].argindex = 0;
			break;
		case bipush:
			strcpy(instructions[i].inst_nome, "bipush");
			instructions[i].opcode = bipush;
			instructions[i].argindex = 1;
			break;
		case sipush:
			strcpy(instructions[i].inst_nome, "sipush");
			instructions[i].opcode = sipush;
			instructions[i].argindex = 2;
			break;
		case ldc:
			strcpy(instructions[i].inst_nome, "ldc");
			instructions[i].opcode = ldc;
			instructions[i].argindex = 1;
			break;
		case ldc_w:
			strcpy(instructions[i].inst_nome, "ldc_w");
			instructions[i].opcode = ldc_w;
			instructions[i].argindex = 2;
			break;
		case ldc2_w:
			strcpy(instructions[i].inst_nome, "ldc2_w");
			instructions[i].opcode = ldc2_w;
			instructions[i].argindex = 2;
			break;
		case iload:
			strcpy(instructions[i].inst_nome, "iload");
			instructions[i].opcode = iload;
			instructions[i].argindex = 1;
			break;
		case lload:
			strcpy(instructions[i].inst_nome, "lload");
			instructions[i].opcode = lload;
			instructions[i].argindex = 1;
			break;
		case fload:
			strcpy(instructions[i].inst_nome, "fload");
			instructions[i].opcode = fload;
			instructions[i].argindex = 1;
			break;
		case dload:
			strcpy(instructions[i].inst_nome, "dload");
			instructions[i].opcode = dload;
			instructions[i].argindex = 1;
			break;
		case aload:
			strcpy(instructions[i].inst_nome, "alod");
			instructions[i].opcode = aload;
			instructions[i].argindex = 1;
			break;
		case iload_0:
			strcpy(instructions[i].inst_nome, "iload_0");
			instructions[i].opcode = iload_0;
			instructions[i].argindex = 0;
			break;
		case iload_1:
			strcpy(instructions[i].inst_nome, "iload_1");
			instructions[i].opcode = iload_1;
			instructions[i].argindex = 0;
			break;
		case iload_2:
			strcpy(instructions[i].inst_nome, "iload_2");
			instructions[i].opcode = iload_2;
			instructions[i].argindex = 0;
			break;
		case iload_3:
			strcpy(instructions[i].inst_nome, "iload_3");
			instructions[i].opcode = iload_3;
			instructions[i].argindex = 0;
			break;
		case lload_0:
			strcpy(instructions[i].inst_nome, "lload_0");
			instructions[i].opcode = lload_0;
			instructions[i].argindex = 0;
			break;
		case lload_1:
			strcpy(instructions[i].inst_nome, "lload_1");
			instructions[i].opcode = lload_1;
			instructions[i].argindex = 0;
			break;
		case lload_2:
			strcpy(instructions[i].inst_nome, "lload_2");
			instructions[i].opcode = lload_2;
			instructions[i].argindex = 0;
			break;
		case lload_3:
			strcpy(instructions[i].inst_nome, "lload_3");
			instructions[i].opcode = lload_3;
			instructions[i].argindex = 0;
			break;
		case fload_0:
			strcpy(instructions[i].inst_nome, "fload_0");
			instructions[i].opcode = fload_0;
			instructions[i].argindex = 0;
			break;
		case fload_1:
			strcpy(instructions[i].inst_nome, "fload_1");
			instructions[i].opcode = fload_1;
			instructions[i].argindex = 0;
			break;
		case fload_2:
			strcpy(instructions[i].inst_nome, "fload_2");
			instructions[i].opcode = fload_2;
			instructions[i].argindex = 0;
			break;
		case fload_3:
			strcpy(instructions[i].inst_nome, "fload_3");
			instructions[i].opcode = fload_3;
			instructions[i].argindex = 0;
			break;
		case dload_0:
			strcpy(instructions[i].inst_nome, "dload_0");
			instructions[i].opcode = dload_0;
			instructions[i].argindex = 0;
			break;
		case dload_1:
			strcpy(instructions[i].inst_nome, "dload_1");
			instructions[i].opcode = dload_1;
			instructions[i].argindex = 0;
			break;
		case dload_2:
			strcpy(instructions[i].inst_nome, "dload_2");
			instructions[i].opcode = dload_2;
			instructions[i].argindex = 0;
			break;
		case dload_3:
			strcpy(instructions[i].inst_nome, "dload_3");
			instructions[i].opcode = dload_3;
			instructions[i].argindex = 0;
			break;
		case aload_0:
			strcpy(instructions[i].inst_nome, "aload_0");
			instructions[i].opcode = aload_0;
			instructions[i].argindex = 0;
			break;
		case aload_1:
			strcpy(instructions[i].inst_nome, "aload_1");
			instructions[i].opcode = aload_1;
			instructions[i].argindex = 0;
			break;
		case aload_2:
			strcpy(instructions[i].inst_nome, "aload_2");
			instructions[i].opcode = aload_2;
			instructions[i].argindex = 0;
			break;
		case aload_3:
			strcpy(instructions[i].inst_nome, "aload_3");
			instructions[i].opcode = aload_3;
			instructions[i].argindex = 0;
			break;
		case iaload:
			strcpy(instructions[i].inst_nome, "iaload");
			instructions[i].opcode = iaload;
			instructions[i].argindex = 0;
			break;
		case laload:
			strcpy(instructions[i].inst_nome, "laload");
			instructions[i].opcode = laload;
			instructions[i].argindex = 0;
			break;
		case faload:
			strcpy(instructions[i].inst_nome, "faload");
			instructions[i].opcode = faload;
			instructions[i].argindex = 0;
			break;
		case daload:
			strcpy(instructions[i].inst_nome, "daload");
			instructions[i].opcode = daload;
			instructions[i].argindex = 0;
			break;
		case aaload:
			strcpy(instructions[i].inst_nome, "aaload");
			instructions[i].opcode = aaload;
			instructions[i].argindex = 0;
			break;
		case baload:
			strcpy(instructions[i].inst_nome, "baload");
			instructions[i].opcode = baload;
			instructions[i].argindex = 0;
			break;
		case caload:
			strcpy(instructions[i].inst_nome, "caload");
			instructions[i].opcode = caload;
			instructions[i].argindex = 0;
			break;
		case saload:
			strcpy(instructions[i].inst_nome, "saload");
			instructions[i].opcode = saload;
			instructions[i].argindex = 0;
			break;
		case istore:
			strcpy(instructions[i].inst_nome, "istore");
			instructions[i].opcode = istore;
			instructions[i].argindex = 1;
			break;
		case lstore:
			strcpy(instructions[i].inst_nome, "lstore");
			instructions[i].opcode = lstore;
			instructions[i].argindex = 1;
			break;
		case fstore:
			strcpy(instructions[i].inst_nome, "fstore");
			instructions[i].opcode = fstore;
			instructions[i].argindex = 1;
			break;
		case dstore:
			strcpy(instructions[i].inst_nome, "dstore");
			instructions[i].opcode = dstore;
			instructions[i].argindex = 1;
			break;
		case astore:
			strcpy(instructions[i].inst_nome, "astore");
			instructions[i].opcode = astore;
			instructions[i].argindex = 1;
			break;
		case istore_0:
			strcpy(instructions[i].inst_nome, "istore_0");
			instructions[i].opcode = istore_0;
			instructions[i].argindex = 0;
			break;
		case istore_1:
			strcpy(instructions[i].inst_nome, "istore_1");
			instructions[i].opcode = istore_1;
			instructions[i].argindex = 0;
			break;
		case istore_2:
			strcpy(instructions[i].inst_nome, "istore_2");
			instructions[i].opcode = istore_2;
			instructions[i].argindex = 0;
			break;
		case istore_3:
			strcpy(instructions[i].inst_nome, "istore_3");
			instructions[i].opcode = istore_3;
			instructions[i].argindex = 0;
			break;
		case lstore_0:
			strcpy(instructions[i].inst_nome, "lstore_0");
			instructions[i].opcode = lstore_0;
			instructions[i].argindex = 0;
			break;
		case lstore_1:
			strcpy(instructions[i].inst_nome, "lstore_1");
			instructions[i].opcode = lstore_1;
			instructions[i].argindex = 0;
			break;
		case lstore_2:
			strcpy(instructions[i].inst_nome, "lstore_2");
			instructions[i].opcode = lstore_2;
			instructions[i].argindex = 0;
			break;
		case lstore_3:
			strcpy(instructions[i].inst_nome, "lstore_3");
			instructions[i].opcode = lstore_3;
			instructions[i].argindex = 0;
			break;
		case fstore_0:
			strcpy(instructions[i].inst_nome, "fstore_0");
			instructions[i].opcode = fstore_0;
			instructions[i].argindex = 0;
			break;
		case fstore_1:
			strcpy(instructions[i].inst_nome, "fstore_1");
			instructions[i].opcode = fstore_1;
			instructions[i].argindex = 0;
			break;
		case fstore_2:
			strcpy(instructions[i].inst_nome, "fstore_2");
			instructions[i].opcode = fstore_2;
			instructions[i].argindex = 0;
			break;
		case fstore_3:
			strcpy(instructions[i].inst_nome, "fstore_3");
			instructions[i].opcode = fstore_3;
			instructions[i].argindex = 0;
			break;
		case dstore_0:
			strcpy(instructions[i].inst_nome, "dstore_0");
			instructions[i].opcode = dstore_0;
			instructions[i].argindex = 0;
			break;
		case dstore_1:
			strcpy(instructions[i].inst_nome, "dstore_1");
			instructions[i].opcode = dstore_1;
			instructions[i].argindex = 0;
			break;
		case dstore_2:
			strcpy(instructions[i].inst_nome, "dstore_2");
			instructions[i].opcode = dstore_2;
			instructions[i].argindex = 0;
			break;
		case dstore_3:
			strcpy(instructions[i].inst_nome, "dstore_3");
			instructions[i].opcode = dstore_3;
			instructions[i].argindex = 0;
			break;
		case astore_0:
			strcpy(instructions[i].inst_nome, "astore_0");
			instructions[i].opcode = astore_0;
			instructions[i].argindex = 0;
			break;
		case astore_1:
			strcpy(instructions[i].inst_nome, "astore_1");
			instructions[i].opcode = astore_1;
			instructions[i].argindex = 0;
			break;
		case astore_2:
			strcpy(instructions[i].inst_nome, "astore_2");
			instructions[i].opcode = astore_2;
			instructions[i].argindex = 0;
			break;
		case astore_3:
			strcpy(instructions[i].inst_nome, "astore_3");
			instructions[i].opcode = astore_3;
			instructions[i].argindex = 0;
			break;
		case iastore:
			strcpy(instructions[i].inst_nome, "iastore");
			instructions[i].opcode = iastore;
			instructions[i].argindex = 0;
			break;
		case lastore:
			strcpy(instructions[i].inst_nome, "lastore");
			instructions[i].opcode = lastore;
			instructions[i].argindex = 0;
			break;
		case fastore:
			strcpy(instructions[i].inst_nome, "fastore");
			instructions[i].opcode = fastore;
			instructions[i].argindex = 0;
			break;
		case dastore:
			strcpy(instructions[i].inst_nome, "dastore");
			instructions[i].opcode = dastore;
			instructions[i].argindex = 0;
			break;
		case aastore:
			strcpy(instructions[i].inst_nome, "aastore");
			instructions[i].opcode = aastore;
			instructions[i].argindex = 0;
			break;
		case bastore:
			strcpy(instructions[i].inst_nome, "bastore");
			instructions[i].opcode = bastore;
			instructions[i].argindex = 0;
			break;
		case castore:
			strcpy(instructions[i].inst_nome, "castore");
			instructions[i].opcode = castore;
			instructions[i].argindex = 0;
			break;
		case sastore:
			strcpy(instructions[i].inst_nome, "sastore");
			instructions[i].opcode = sastore;
			instructions[i].argindex = 0;
			break;
		case pop:
			strcpy(instructions[i].inst_nome, "pop");
			instructions[i].opcode = pop;
			instructions[i].argindex = 0;
			break;
		case pop2:
			strcpy(instructions[i].inst_nome, "pop2");
			instructions[i].opcode = pop2;
			instructions[i].argindex = 0;
			break;
		case dup:
			strcpy(instructions[i].inst_nome, "dup");
			instructions[i].opcode = dup;
			instructions[i].argindex = 0;
			break;
		case dup_x1:
			strcpy(instructions[i].inst_nome, "dup_x1");
			instructions[i].opcode = dup_x1;
			instructions[i].argindex = 0;
			break;
		case dup_x2:
			strcpy(instructions[i].inst_nome, "dup_x2");
			instructions[i].opcode = dup_x2;
			instructions[i].argindex = 0;
			break;
		case dup2:
			strcpy(instructions[i].inst_nome, "dup2");
			instructions[i].opcode = dup2;
			instructions[i].argindex = 0;
			break;
		case dup2_x1:
			strcpy(instructions[i].inst_nome, "dup2_x1");
			instructions[i].opcode = dup2_x1;
			instructions[i].argindex = 0;
			break;
		case dup2_x2:
			strcpy(instructions[i].inst_nome, "dup2_x2");
			instructions[i].opcode = dup2_x2;
			instructions[i].argindex = 0;
			break;
		case swap:
			strcpy(instructions[i].inst_nome, "swap");
			instructions[i].opcode = swap;
			instructions[i].argindex = 0;
			break;
		case iadd:
			strcpy(instructions[i].inst_nome, "iadd");
			instructions[i].opcode = iadd;
			instructions[i].argindex = 0;
			break;
		case ladd:
			strcpy(instructions[i].inst_nome, "ladd");
			instructions[i].opcode = ladd;
			instructions[i].argindex = 0;
			break;
		case fadd:
			strcpy(instructions[i].inst_nome, "fadd");
			instructions[i].opcode = fadd;
			instructions[i].argindex = 0;
			break;
		case dadd:
			strcpy(instructions[i].inst_nome, "dadd");
			instructions[i].opcode = dadd;
			instructions[i].argindex = 0;
			break;
		case isub:
			strcpy(instructions[i].inst_nome, "isub");
			instructions[i].opcode = isub;
			instructions[i].argindex = 0;
			break;
		case lsub:
			strcpy(instructions[i].inst_nome, "lsub");
			instructions[i].opcode = lsub;
			instructions[i].argindex = 0;
			break;
		case fsub:
			strcpy(instructions[i].inst_nome, "fsub");
			instructions[i].opcode = fsub;
			instructions[i].argindex = 0;
			break;
		case dsub:
			strcpy(instructions[i].inst_nome, "dsub");
			instructions[i].opcode = dsub;
			instructions[i].argindex = 0;
			break;
		case imul:
			strcpy(instructions[i].inst_nome, "imul");
			instructions[i].opcode = imul;
			instructions[i].argindex = 0;
			break;
		case lmul:
			strcpy(instructions[i].inst_nome, "lmul");
			instructions[i].opcode = lmul;
			instructions[i].argindex = 0;
			break;
		case fmul:
			strcpy(instructions[i].inst_nome, "fmul");
			instructions[i].opcode = fmul;
			instructions[i].argindex = 0;
			break;
		case dmul:
			strcpy(instructions[i].inst_nome, "dmul");
			instructions[i].opcode = dmul;
			instructions[i].argindex = 0;
			break;
		case idiv:
			strcpy(instructions[i].inst_nome, "idiv");
			instructions[i].opcode = idiv;
			instructions[i].argindex = 0;
			break;
		case inst_ldiv:
			strcpy(instructions[i].inst_nome, "ldiv");
			instructions[i].opcode = inst_ldiv;
			instructions[i].argindex = 0;
			break;
		case fdiv:
			strcpy(instructions[i].inst_nome, "fdiv");
			instructions[i].opcode = fdiv;
			instructions[i].argindex = 0;
			break;
		case ddiv:
			strcpy(instructions[i].inst_nome, "ddiv");
			instructions[i].opcode = ddiv;
			instructions[i].argindex = 0;
			break;
		case irem:
			strcpy(instructions[i].inst_nome, "irem");
			instructions[i].opcode = irem;
			instructions[i].argindex = 0;
			break;
		case lrem:
			strcpy(instructions[i].inst_nome, "lrem");
			instructions[i].opcode = lrem;
			instructions[i].argindex = 0;
			break;
		case frem:
			strcpy(instructions[i].inst_nome, "frem");
			instructions[i].opcode = frem;
			instructions[i].argindex = 0;
			break;
		case inst_drem:
			strcpy(instructions[i].inst_nome, "drem");
			instructions[i].opcode = inst_drem;
			instructions[i].argindex = 0;
			break;
		case ineg:
			strcpy(instructions[i].inst_nome, "ineg");
			instructions[i].opcode = ineg;
			instructions[i].argindex = 0;
			break;
		case lneg:
			strcpy(instructions[i].inst_nome, "lneg");
			instructions[i].opcode = lneg;
			instructions[i].argindex = 0;
			break;
		case fneg:
			strcpy(instructions[i].inst_nome, "fneg");
			instructions[i].opcode = fneg;
			instructions[i].argindex = 0;
			break;
		case dneg:
			strcpy(instructions[i].inst_nome, "dneg");
			instructions[i].opcode = dneg;
			instructions[i].argindex = 0;
			break;
		case ishl:
			strcpy(instructions[i].inst_nome, "ishl");
			instructions[i].opcode = ishl;
			instructions[i].argindex = 0;
			break;
		case lshl:
			strcpy(instructions[i].inst_nome, "lshl");
			instructions[i].opcode = lshl;
			instructions[i].argindex = 0;
			break;
		case ishr:
			strcpy(instructions[i].inst_nome, "ishr");
			instructions[i].opcode = ishr;
			instructions[i].argindex = 0;
			break;
		case lshr:
			strcpy(instructions[i].inst_nome, "lshr");
			instructions[i].opcode = lshr;
			instructions[i].argindex = 0;
			break;
		case iushr:
			strcpy(instructions[i].inst_nome, "iushr");
			instructions[i].opcode = iushr;
			instructions[i].argindex = 0;
			break;
		case lushr:
			strcpy(instructions[i].inst_nome, "lushr");
			instructions[i].opcode = lushr;
			instructions[i].argindex = 0;
			break;
		case iand:
			strcpy(instructions[i].inst_nome, "iand");
			instructions[i].opcode = iand;
			instructions[i].argindex = 0;
			break;
		case land:
			strcpy(instructions[i].inst_nome, "land");
			instructions[i].opcode = land;
			instructions[i].argindex = 0;
			break;
		case ior:
			strcpy(instructions[i].inst_nome, "ior");
			instructions[i].opcode = ior;
			instructions[i].argindex = 0;
			break;
		case lor:
			strcpy(instructions[i].inst_nome, "lor");
			instructions[i].opcode = lor;
			instructions[i].argindex = 0;
			break;
		case ixor:
			strcpy(instructions[i].inst_nome, "ixor");
			instructions[i].opcode = ixor;
			instructions[i].argindex = 0;
			break;
		case lxor:
			strcpy(instructions[i].inst_nome, "lxor");
			instructions[i].opcode = lxor;
			instructions[i].argindex = 0;
			break;
		case iinc:
			strcpy(instructions[i].inst_nome, "iinc");
			instructions[i].opcode = iinc;
			instructions[i].argindex = 2;
			break;
		case i2l:
			strcpy(instructions[i].inst_nome, "i2l");
			instructions[i].opcode = i2l;
			instructions[i].argindex = 0;
			break;
		case i2f:
			strcpy(instructions[i].inst_nome, "i2f");
			instructions[i].opcode = i2f;
			instructions[i].argindex = 0;
			break;
		case i2d:
			strcpy(instructions[i].inst_nome, "i2d");
			instructions[i].opcode = i2d;
			instructions[i].argindex = 0;
			break;
		case l2i:
			strcpy(instructions[i].inst_nome, "l2i");
			instructions[i].opcode = l2i;
			instructions[i].argindex = 0;
			break;
		case l2f:
			strcpy(instructions[i].inst_nome, "l2f");
			instructions[i].opcode = l2f;
			instructions[i].argindex = 0;
			break;
		case l2d:
			strcpy(instructions[i].inst_nome, "l2d");
			instructions[i].opcode = l2d;
			instructions[i].argindex = 0;
			break;
		case f2i:
			strcpy(instructions[i].inst_nome, "f2i");
			instructions[i].opcode = f2i;
			instructions[i].argindex = 0;
			break;
		case f2l:
			strcpy(instructions[i].inst_nome, "f2l");
			instructions[i].opcode = f2l;
			instructions[i].argindex = 0;
			break;
		case f2d:
			strcpy(instructions[i].inst_nome, "f2d");
			instructions[i].opcode = f2d;
			instructions[i].argindex = 0;
			break;
		case d2i:
			strcpy(instructions[i].inst_nome, "d2i");
			instructions[i].opcode = d2i;
			instructions[i].argindex = 0;
			break;
		case d2l:
			strcpy(instructions[i].inst_nome, "d2l");
			instructions[i].opcode = d2l;
			instructions[i].argindex = 0;
			break;
		case d2f:
			strcpy(instructions[i].inst_nome, "d2f");
			instructions[i].opcode = d2f;
			instructions[i].argindex = 0;
			break;
		case i2b:
			strcpy(instructions[i].inst_nome, "i2b");
			instructions[i].opcode = i2b;
			instructions[i].argindex = 0;
			break;
		case i2c:
			strcpy(instructions[i].inst_nome, "i2c");
			instructions[i].opcode = i2c;
			instructions[i].argindex = 0;
			break;
		case i2s:
			strcpy(instructions[i].inst_nome, "i2s");
			instructions[i].opcode = i2s;
			instructions[i].argindex = 0;
			break;
		case lcmp:
			strcpy(instructions[i].inst_nome, "lcmp");
			instructions[i].opcode = lcmp;
			instructions[i].argindex = 0;
			break;
		case fcmpl:
			strcpy(instructions[i].inst_nome, "fcmpl");
			instructions[i].opcode = fcmpl;
			instructions[i].argindex = 0;
			break;
		case fcmpg:
			strcpy(instructions[i].inst_nome, "fcmpg");
			instructions[i].opcode = fcmpg;
			instructions[i].argindex = 0;
			break;
		case dcmpl:
			strcpy(instructions[i].inst_nome, "dcmpl");
			instructions[i].opcode = dcmpl;
			instructions[i].argindex = 0;
			break;
		case dcmpg:
			strcpy(instructions[i].inst_nome, "dcmpg");
			instructions[i].opcode = dcmpg;
			instructions[i].argindex = 0;
			break;
		case ifeq:
			strcpy(instructions[i].inst_nome, "ifeq");
			instructions[i].opcode = ifeq;
			instructions[i].argindex = 2;
			break;
		case ifne:
			strcpy(instructions[i].inst_nome, "ifne");
			instructions[i].opcode = ifne;
			instructions[i].argindex = 2;
			break;
		case iflt:
			strcpy(instructions[i].inst_nome, "iflt");
			instructions[i].opcode = iflt;
			instructions[i].argindex = 2;
			break;
		case ifge:
			strcpy(instructions[i].inst_nome, "ifge");
			instructions[i].opcode = ifge;
			instructions[i].argindex = 2;
			break;
		case ifgt:
			strcpy(instructions[i].inst_nome, "ifgt");
			instructions[i].opcode = ifgt;
			instructions[i].argindex = 2;
			break;
		case ifle:
			strcpy(instructions[i].inst_nome, "ifle");
			instructions[i].opcode = ifle;
			instructions[i].argindex = 2;
			break;
		case if_icmpeq:
			strcpy(instructions[i].inst_nome, "if_icmpeq");
			instructions[i].opcode = if_icmpeq;
			instructions[i].argindex = 2;
			break;
		case if_icmpne:
			strcpy(instructions[i].inst_nome, "if_icmpne");
			instructions[i].opcode = if_icmpne;
			instructions[i].argindex = 2;
			break;
		case if_icmplt:
			strcpy(instructions[i].inst_nome, "if_icmplt");
			instructions[i].opcode = if_icmplt;
			instructions[i].argindex = 2;
			break;
		case if_icmpge:
			strcpy(instructions[i].inst_nome, "if_icmpge");
			instructions[i].opcode = if_icmpge;
			instructions[i].argindex = 2;
			break;
		case if_icmpgt:
			strcpy(instructions[i].inst_nome, "if_icmpgt");
			instructions[i].opcode = if_icmpgt;
			instructions[i].argindex = 2;
			break;
		case if_icmple:
			strcpy(instructions[i].inst_nome, "if_icmple");
			instructions[i].opcode = if_icmple;
			instructions[i].argindex = 2;
			break;
		case if_acmpeg:
			strcpy(instructions[i].inst_nome, "if_acmpeg");
			instructions[i].opcode = if_acmpeg;
			instructions[i].argindex = 2;
			break;
		case if_acmpne:
			strcpy(instructions[i].inst_nome, "if_acmpne");
			instructions[i].opcode = if_acmpne;
			instructions[i].argindex = 2;
			break;
		case inst_goto:
			strcpy(instructions[i].inst_nome, "goto");
			instructions[i].opcode = inst_goto;
			instructions[i].argindex = 2;
			break;
		case jsr:
			strcpy(instructions[i].inst_nome, "jsr");
			instructions[i].opcode = jsr;
			instructions[i].argindex = 2;
			break;
		case ret:
			strcpy(instructions[i].inst_nome, "ret");
			instructions[i].opcode = ret;
			instructions[i].argindex = 1;
			break;
		case tableswitch:
			strcpy(instructions[i].inst_nome, "tableswitch");
			instructions[i].opcode = tableswitch;
			instructions[i].argindex = 0;
			break;
		case lookupswitch:
			strcpy(instructions[i].inst_nome, "lookupswitch");
			instructions[i].opcode = lookupswitch;
			instructions[i].argindex = 0;
			break;
		case ireturn:
			strcpy(instructions[i].inst_nome, "ireturn");
			instructions[i].opcode = ireturn;
			instructions[i].argindex = 0;
			break;
		case lreturn:
			strcpy(instructions[i].inst_nome, "lreturn");
			instructions[i].opcode = lreturn;
			instructions[i].argindex = 0;
			break;
		case freturn:
			strcpy(instructions[i].inst_nome, "freturn");
			instructions[i].opcode = freturn;
			instructions[i].argindex = 0;
			break;
		case dreturn:
			strcpy(instructions[i].inst_nome, "dreturn");
			instructions[i].opcode = dreturn;
			instructions[i].argindex = 0;
			break;
		case areturn:
			strcpy(instructions[i].inst_nome, "areturn");
			instructions[i].opcode = areturn;
			instructions[i].argindex = 0;
			break;
		case inst_return:
			strcpy(instructions[i].inst_nome, "return");
			instructions[i].opcode = inst_return;
			instructions[i].argindex = 0;
			break;
		case getstatic:
			strcpy(instructions[i].inst_nome, "getstatic");
			instructions[i].opcode = getstatic;
			instructions[i].argindex = 2;
			break;
		case putstatic:
			strcpy(instructions[i].inst_nome, "putstatic");
			instructions[i].opcode = putstatic;
			instructions[i].argindex = 2;
			break;
		case getfield:
			strcpy(instructions[i].inst_nome, "getfield");
			instructions[i].opcode = getfield;
			instructions[i].argindex = 2;
			break;
		case putfield:
			strcpy(instructions[i].inst_nome, "putfield");
			instructions[i].opcode = putfield;
			instructions[i].argindex = 2;
			break;
		case invokevirtual:
			strcpy(instructions[i].inst_nome, "invokevirtual");
			instructions[i].opcode = invokevirtual;
			instructions[i].argindex = 2;
			break;
		case invokespecial:
			strcpy(instructions[i].inst_nome, "invokespecial");
			instructions[i].opcode = invokespecial;
			instructions[i].argindex = 2;
			break;
		case invokestatic:
			strcpy(instructions[i].inst_nome, "invokestatic");
			instructions[i].opcode = invokestatic;
			instructions[i].argindex = 2;
			break;
		case invokeinterface:
			strcpy(instructions[i].inst_nome, "invokeinterface");
			instructions[i].opcode = invokeinterface;
			instructions[i].argindex = 4;
			break;
		case inst_new:
			strcpy(instructions[i].inst_nome, "new");
			instructions[i].opcode = inst_new;
			instructions[i].argindex = 2;
			break;
		case newarray:
			strcpy(instructions[i].inst_nome, "newarray");
			instructions[i].opcode = newarray;
			instructions[i].argindex = 1;
			break;
		case anewarray:
			strcpy(instructions[i].inst_nome, "anewarray");
			instructions[i].opcode = anewarray;
			instructions[i].argindex = 2;
			break;
		case arraylength:
			strcpy(instructions[i].inst_nome, "arraylength");
			instructions[i].opcode = arraylength;
			instructions[i].argindex = 0;
			break;
		case athrow:
			strcpy(instructions[i].inst_nome, "athrow");
			instructions[i].opcode = athrow;
			instructions[i].argindex = 0;
			break;
		case checkcast:
			strcpy(instructions[i].inst_nome, "checkcast");
			instructions[i].opcode = checkcast;
			instructions[i].argindex = 2;
			break;
		case instanceof:
			strcpy(instructions[i].inst_nome, "instanceof");
			instructions[i].opcode = instanceof ;
			instructions[i].argindex = 2;
			break;
		case monitorenter:
			strcpy(instructions[i].inst_nome, "monitorenter");
			instructions[i].opcode = monitorenter;
			instructions[i].argindex = 0;
			break;
		case monitorexit:
			strcpy(instructions[i].inst_nome, "monitorexit");
			instructions[i].opcode = monitorexit;
			instructions[i].argindex = 0;
			break;
		case wide:
			strcpy(instructions[i].inst_nome, "wide");
			instructions[i].opcode = wide;
			instructions[i].argindex = 5;
			break;
		case multianewarray:
			strcpy(instructions[i].inst_nome, "multianewarray");
			instructions[i].opcode = multianewarray;
			instructions[i].argindex = 3;
			break;
		case ifnull:
			strcpy(instructions[i].inst_nome, "ifnull");
			instructions[i].opcode = ifnull;
			instructions[i].argindex = 2;
			break;
		case ifnonnull:
			strcpy(instructions[i].inst_nome, "ifnonnull");
			instructions[i].opcode = ifnonnull;
			instructions[i].argindex = 2;
			break;
		case goto_w:
			strcpy(instructions[i].inst_nome, "goto_w");
			instructions[i].opcode = goto_w;
			instructions[i].argindex = 4;
			break;
		case jsr_w:
			strcpy(instructions[i].inst_nome, "jsr_w");
			instructions[i].opcode = jsr_w;
			instructions[i].argindex = 4;
			break;

		default:
			strcpy(instructions[i].inst_nome, "undefined");
			instructions[i].opcode = 255;
			instructions[i].argindex = -1;
			break;
		}

		if (instructions[i].argindex > 0)
		{
			instructions[i].tipoarg = malloc(instructions[i].argindex * sizeof(int));
		}
		else
		{
			instructions[i].tipoarg = NULL;
		}
	}

	return (instructions);
}

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

/*Macro para verificação de inclusão de arquivos de estrutura,
bibliotecas de leitura/escrita de dados e manipulação de arquivos
*/
#ifndef LEITURA_INIT
#define LEITURA_INIT

/*Inclusão de bibliotecas para leitura/escrita de dados,
manipulação de arquivos e definição de estruturas*/
#include <stdio.h>
#include <stdlib.h>
#include "exibidor.h"
#include "classfile.h"

/* FUNÇÃO PRINCIPAL PARA LEITURA DO ARQUIVO .CLASS */
Classfile *readArquivo(Classfile *, char *);

/* FUNÇÕES AUXILIARES PARA LEITURA DAS PARTES ESPECÍFICAS DO ARQUIVO .CLASS */
Cp_info *readConstantPool(FILE *, Cp_info *, u2);
u2 *readInterfaces(FILE *fp, u2 *interface, u2 i_count);
Field_info *readFields(FILE *fp, Field_info *field, u2 f_count, Cp_info *cp);
Method_info *readMethods(FILE *fp, Method_info *metodo, u2 m_count, Cp_info *cp);
Attribute_info *readAttrs(FILE *fp, Attribute_info *a, Cp_info *cp);
Code_attribute *readCode(FILE *fp, Cp_info *cp);
Line_number_table *readLineNumberTable(FILE *fp, Cp_info *cp);
Exception_info *readExceptionTable(FILE *fp, u2 size);
Exception_attribute *readreadExceptionAttributes(FILE *fp);
Constant_value_attribute *readConstantValue(FILE *fp);
Signature_attribute *readSignature(FILE *fp);
Inner_classes_attribute *readInnerClasses(FILE *fp, Cp_info *cp);
Classes *readClasses(FILE *fp);
Stack_map_attribute *readStackMapTable(FILE *fp);
Stack_map_frame *readStackMapFrame(FILE *fp);
Verification_type_info *readVerificationTypeInfo(FILE *fp);
Source_file_attribute *readSourceFile(FILE *fp);

#endif

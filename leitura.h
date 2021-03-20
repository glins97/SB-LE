/*
Universidade de Brasília - 2020/02
Software Básico - Turma A
Leitor/Exibidor de arquivo .class

Alunos:
    Gabriel Lins
    Jaqueline Gontijo
    Tiago Cruz
    Carol Ferreira
    Lucas Barros

*/
/*Macro para verificação de inclusão de arquivos de estrutura,
bibliotecas de leitura/escrita de dados e manipulação de arquivos
*/
#ifndef LEITURA_H
#define LEITURA_H

/*Inclusão de bibliotecas para leitura/escrita de dados,
manipualão de arquivos e definição de estruturas*/
#include <stdio.h>
#include <stdlib.h>
#include "exibidor.h"
#include "ClassFile.h"

Classfile *readArquivo(Classfile *, char *);
Cp_info *readConstantPool(FILE *fp, Cp_info *cp, u2 cp_count);
u2 *readInterfaces(FILE *fp, u2 *interface, u2 i_count);
Field_info *readFields(File *fp, Field_info *field, u2 f_count, Cp_info *cp);
Method_info *readMetodos(FILE *fp, Method_info *metodo, u2 m_count, Cp_info *cp)
    code_attribute *readCode(FILE *fp, cp_info *cp);
line_number_table *readLineNumberTable(FILE *fp, cp_info *cp);
exception_table *readExceptionTable(FILE *fp, u2 size);
Attribute_info *readAtributos(FILE *fp, Attribute_info *a, Cp_info *cp);
exceptions_attribute *readreadExceptionAttributes(FILE *fp);
constantValue_attribute *readConstantValue(FILE *fp);
signature_attribute *readSignature(FILE *fp);
innerClasses_attribute *readInnerClasses(FILE *fp, cp_info *cp);
classes *readClasses(FILE *fp);
stackMapTable_attribute *readStackMapTable(FILE *fp);
stack_map_frame *readStackMapFrame(FILE *fp)
    verification_type_info *readVerificationTypeInfo(FILE *fp);
source_file_attribute *readSourceFile(FILE fp);

#endif

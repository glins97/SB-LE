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

#include "leitor.h"
#include <string.h> // testar retirando!

/*Macro para leitura de um tipo u1 do arquivo .class*/
#define u1READ(arq) getc(arq)
/*Macro para leitura de um tipo u2 do arquivo .class*/
#define u2READ(arq) (getc(arq) << 8) | getc(arq)
/*Macro para leitura de um tipo u4 do arquivo .class*/
#define u4READ(arq) (getc(arq) << 24) | (getc(arq) << 16 | getc(arq) << 8 | getc(arq))

/* FUNÇÃO PRINCIPAL PARA LEITURA DO ARQUIVO .CLASS */
Classfile *readArquivo(Classfile *cf, char *nomeArquivo)
{
	FILE *fp = fopen(nomeArquivo, "rb"); // abre o arquivo .class em modo leitura binario

	if (!fp)
	{ // se nao encontrou arquivo ou nao conseguiu abrir, encerra o programa
		printf("Erro na abertura do arquivo .class, o programa sera encerrado...\n");
		exit(0);
	}

	cf->magic = u4READ(fp); // lê CAFEBABE
	cf->minor_version = u2READ(fp);
	cf->major_version = u2READ(fp);

	cf->constant_pool_count = u2READ(fp);
	cf->constant_pool = readConstantPool(fp, cf->constant_pool, cf->constant_pool_count);

	cf->access_flags = u2READ(fp);
	cf->this_class = u2READ(fp);
	cf->super_class = u2READ(fp);

	cf->interfaces_count = u2READ(fp);
	cf->interfaces = (cf->interfaces_count > 0) ? readInterfaces(fp, cf->interfaces, cf->interfaces_count) : NULL;

	cf->fields_count = u2READ(fp);
	cf->fields = (cf->fields_count > 0) ? readFields(fp, cf->fields, cf->fields_count, cf->constant_pool) : NULL;

	/*Leitura do value 'methods_count' = quantidade de entradas na tabela Method*/
	cf->methods_count = u2READ(fp);
	cf->methods = (cf->methods_count > 0) ? readMethods(fp, cf->methods, cf->methods_count, cf->constant_pool) : NULL; // ASS: (FILE *fp, method_info* metodo, u2 m_count, cp_info *cp)

	cf->attributes_count = u2READ(fp);
	if (cf->attributes_count > 0)
	{
		cf->attributes = (Attribute_info **)malloc(cf->attributes_count * sizeof(Attribute_info *));
		for (int i = 0; i < cf->attributes_count; i++)
		{
			*(cf->attributes + i) = readAttrs(fp, *(cf->attributes + i), cf->constant_pool);
		}
	}

	fclose(fp); // Terminou de read o arquivo->libera fp.

	return cf; //retorna pointer para a estrutura do tipo classfile para a main.c
}

/* FUNÇÕES AUXILIARES PARA LEITURA DAS PARTES ESPECÍFICAS DO ARQUIVO .CLASS */
Cp_info *readConstantPool(FILE *fp, Cp_info *cp, u2 cp_count)
{
	cp = (Cp_info *)malloc(cp_count * sizeof(struct cp_info));

	for (Cp_info *p = cp; p < cp + cp_count - 1; p++)
	{
		p->tag = u1READ(fp);

		switch (p->tag)
		{
		case CONSTANT_Class:
			p->cp_union.Class.name = u2READ(fp);
			break;

		case CONSTANT_Field:
			p->cp_union.Field.class_name = u2READ(fp);
			p->cp_union.Field.name_and_type = u2READ(fp);
			break;

		case CONSTANT_Method:
			p->cp_union.Method.class_name = u2READ(fp);
			p->cp_union.Method.name_and_type = u2READ(fp);
			break;

		case CONSTANT_InterfaceMethod:
			p->cp_union.InterfaceMethod.class_name = u2READ(fp);
			p->cp_union.InterfaceMethod.name_and_type = u2READ(fp);
			break;

		case CONSTANT_String:
			p->cp_union.String.string = u2READ(fp);
			break;

		case CONSTANT_Integer:
			p->cp_union.Integer.bytes = u4READ(fp);
			break;

		case CONSTANT_Float:
			p->cp_union.Float.bytes = u4READ(fp);
			break;

		case CONSTANT_Long:
			p->cp_union.Long.hi_bytes = u4READ(fp);
			p->cp_union.Long.lo_bytes = u4READ(fp);
			p++;
			break;

		case CONSTANT_Double:
			p->cp_union.Double.hi_bytes = u4READ(fp);
			p->cp_union.Double.lo_bytes = u4READ(fp);
			p++;
			break;

		case CONSTANT_NameAndType:
			p->cp_union.NameAndType.name = u2READ(fp);
			p->cp_union.NameAndType.descriptor = u2READ(fp);
			break;

		case CONSTANT_Utf8:
			p->cp_union.Utf8.length = u2READ(fp);
			p->cp_union.Utf8.bytes = malloc(p->cp_union.Utf8.length * sizeof(u1));
			for (u1 *i = p->cp_union.Utf8.bytes; i < p->cp_union.Utf8.bytes + p->cp_union.Utf8.length; i++)
			{
				*i = u1READ(fp);
			}
			break;

		case CONSTANT_MethodHandle:
			p->cp_union.MethodHandle.reference_kind = u1READ(fp);
			p->cp_union.MethodHandle.reference = u2READ(fp);
			break;

		case CONSTANT_MethodType:
			p->cp_union.MethodType.descriptor = u2READ(fp);
			break;

		case CONSTANT_InvokeDynamic:
			p->cp_union.InvokeDynamic.bootstrap_method_attr = u2READ(fp);
			p->cp_union.InvokeDynamic.name_and_type = u2READ(fp);
			break;
			// VERIFICAR A NECESSIDADE DESTE DEFAULT
		default:
			break;
		}
	}

	return cp;
}

u2 *readInterfaces(FILE *fp, u2 *interface, u2 i_count)
{
	interface = (u2 *)malloc(i_count * sizeof(u2));
	for (u2 *p = interface; p < interface + i_count; p++)
	{
		*interface = u2READ(fp);
	}

	return interface;
}

Field_info *readFields(FILE *fp, Field_info *field, u2 f_count, Cp_info *cp)
{
	field = (Field_info *)malloc(f_count * sizeof(struct field_info));

	for (Field_info *p = field; p < field + f_count; p++)
	{
		p->access_flags = u2READ(fp);
		p->name = u2READ(fp);
		p->descriptor = u2READ(fp);
		p->attributes_count = u2READ(fp);

		if (p->attributes_count > 0)
		{
			p->attributes = (Attribute_info **)malloc(p->attributes_count * sizeof(Attribute_info *));
			for (int i = 0; i < p->attributes_count; p++)
			{
				*(p->attributes + i) = readAttrs(fp, *(p->attributes + i), cp);
			}
		}
	}

	return field;
}

Method_info *readMethods(FILE *fp, Method_info *metodo, u2 m_count, Cp_info *cp)
{
	metodo = (Method_info *)malloc(m_count * sizeof(method_info));

	for (Method_info *p = metodo; p < metodo + m_count; p++)
	{
		p->access_flags = u2READ(fp);
		p->name = u2READ(fp);
		p->descriptor = u2READ(fp);
		p->attributes_count = u2READ(fp);

		//printf("access_flags: %02x\n",i->access_flags);
		//printf("Name index method: %d\n",i->name);

		/*Estrutura condicional que avalia se a quantidade de atributos
		do método é maior que zero. Se for, prossegue com a leitura dos
		atributos do método*/
		attribute_info *atributos = (attribute_info *)malloc(p->attributes_count * sizeof(attribute_info));

		if (p->attributes_count > 0)
		{
			p->attributes = (attribute_info **)malloc(p->attributes_count * sizeof(attribute_info *));
			for (int i = 0; i < p->attributes_count; i++)
			{
				*(p->attributes + i) = readAttrs(fp, *(p->attributes + i), cp);
			}
		}
	}

	return metodo;
}

Attribute_info *readAttrs(FILE *fp, Attribute_info *a, cp_info *cp)
{
	a = (Attribute_info *)malloc(sizeof(attribute_info));

	a->attribute_name = u2READ(fp);
	a->attribute_length = u4READ(fp);

	//printf("att name index: %d\n",attributes->attribute_name);
	//printf("attr length: %d\n",attributes->attribute_length);

	if (a->attribute_length > 0)
	{
		char *string;
		string = decodeUTF8String(cp + a->attribute_name - 1);

		if (strcmp(string, "SourceFile") == 0)
		{
			//printf("Entrou sourcefile\n");
			Source_file_attribute *SourceFile = NULL; //(code_attribute*) malloc(i->attributes_count*sizeof(code_attribute));
			SourceFile = readSourceFile(fp);
			a->info = NULL; //malloc(i->attributes_count*sizeof(code_attribute));
			a->info = (source_file_attribute *)SourceFile;
		}
		else if (strcmp(string, "Code") == 0)
		{
			printf("Entrou code\n");
			Code_attribute *code_attr = NULL;
			code_attr = readCode(fp, cp);
			a->info = (code_attribute *)code_attr;
		}
		else if (strcmp(string, "LineNumberTable") == 0)
		{
			Line_number_table *lnt = NULL;
			printf("Entrou lnt\n");
			lnt = readLineNumberTable(fp, cp);
			a->info = (Line_number_table *)lnt;
		}
		else if (strcmp(string, "StackMapTable") == 0)
		{
			printf("Entrou stack map table\n");
			Stack_map_attribute *stackMapTable = NULL;
			stackMapTable = readStackMapTable(fp);
			printf("Saiu de smt\n");
			a->info = (Stack_map_attribute *)stackMapTable;
		}
		else if (strcmp(string, "InnerClasses") == 0)
		{
			printf("Entrou em inner class\n");
			Inner_classes_attribute *innerClasses = NULL;
			innerClasses = readInnerClasses(fp, cp);
			a->info = (Inner_classes_attribute *)innerClasses;
		}
		else if (strcmp(string, "Signature") == 0)
		{
			printf("Entrou em signature\n");
			signature_attribute *signatureR = NULL;
			signatureR = readSignature(fp);
			a->info = (Signature_attribute *)signatureR;
		}
		else if (strcmp(string, "ConstantValue") == 0)
		{
			Constant_value_attribute *constantV = NULL;
			constantV = readConstantValue(fp);
			a->info = (Constant_value_attribute *)constantV;
		}
		else if (strcmp(string, "Exceptions") == 0)
		{
			Exception_attribute *exceptions = NULL;
			exceptions = readreadExceptionAttributes(fp);
			a->info = (Exception_attribute *)exceptions;
		}
	}

	return a;
}

Code_attribute *readCode(FILE *fp, Cp_info *cp)
{
	//code_attribute *code_attributes = NULL;
	code_attributes = (Code_attribute *)malloc(sizeof(code_attribute));
	code_attributes->max_stack = u2READ(fp);
	code_attributes->max_locals = u2READ(fp);
	code_attributes->code_length = u4READ(fp);
	if (code_attributes->code_length > 0)
	{
		code_attributes->code = malloc(code_attributes->code_length * sizeof(u1));
		for (u1 *p = code_attributes->code; p < code_attributes->code + code_attributes->code_length; p++)
		{
			*p = u1READ(fp);
		}
	}

	code_attributes->exception_info_length = u2READ(fp);

	if (code_attributes->exception_info_length > 0)
	{
		code_attributes->ex_info = NULL; //malloc(code_attributes->exception_info_length*sizeof(exception_info));
		code_attributes->ex_info = readExceptionTable(fp, code_attributes->exception_info_length);
	}

	code_attributes->attributes_count = u2READ(fp);
	// u2 auxCodeAttrCount = code_attributes->attributes_count;
	// char * string_name = malloc(100*sizeof(char));

	if (code_attributes->attributes_count > 0)
	{
		code_attributes->attributes = (attribute_info **)malloc(code_attributes->attributes_count * sizeof(attribute_info *));
		for (int i = 0; i < code_attributes->attributes_count; i++)
		{
			*(code_attributes->attributes + i) = readAttrs(fp, *(code_attributes->attributes + i), cp);
		}
	}

	return code_attributes;
}

Line_number_table *readLineNumberTable(FILE *fp, cp_info *cp)
{
	Line_number_table *lnt = (Line_number_table *)malloc(sizeof(struct line_number_table));
	lnt->line_number_length = u2READ(fp);
	if (lnt->line_number_length > 0)
	{
		lnt->info = (Line_number_info *)malloc(lnt->line_number_length * sizeof(struct line_number_info));
		for (Line_number_info *linfo = lnt->info; linfo < lnt->info + lnt->line_number_length; linfo++)
		{
			linfo->start_pc = u2READ(fp);
			linfo->line_number = u2READ(fp);
		}
	}
	return lnt;
}

Exception_info *readExceptionTable(FILE *fp, u2 size)
{
	Exception_info *exception_tableAux = (Exception_info *)malloc(size * sizeof(struct exception_info));
	for (Exception_info *e = exception_tableAux; e < exception_tableAux + size; e++)
	{
		e->start_pc = u2READ(fp);
		e->end_pc = u2READ(fp);
		e->handread_pc = u2READ(fp);
		e->catch_type = u2READ(fp);
	}
	return exception_tableAux;
}

Exception_attribute *readreadExceptionAttributes(FILE *fp)
{
	Exception_attribute *exceptions = (Exception_attribute *)malloc(sizeof(struct exception_attribute));
	exceptions->num_exceptions = u2READ(fp);
	exceptions->exception_info = NULL;
	if (exceptions->num_exceptions > 0)
	{
		exceptions->exception_info = (u2 *)malloc(exceptions->num_exceptions * sizeof(u2));
		for (u2 *excpAux = exceptions->exception_info; excpAux < exceptions->exception_info + exceptions->num_exceptions; excpAux++)
		{
			*excpAux = u2READ(fp);
		}
	}
	return exceptions;
}

Constant_value_attribute *readConstantValue(FILE *fp)
{
	Constant_value_attribute *cv = (Constant_value_attribute *)malloc(sizeof(struct constant_value_attribute));
	cv->constant_value = u2READ(fp);
	return cv;
}

Signature_attribute *readSignature(FILE *fp)
{
	Signature_attribute *signature = (Signature_attribute *)malloc(sizeof(struct signature_attribute));
	signature->signature = u2READ(fp);
	return signature;
}

Inner_classes_attribute *readInnerClasses(FILE *fp, cp_info *cp)
{
	Inner_classes_attribute *innerClasses = (Inner_classes_attribute *)malloc(sizeof(struct inner_classes_attribute));
	innerClasses->num_classes = u2READ(fp);
	if (innerClasses->num_classes > 0)
	{
		innerClasses->classes_array = (Classes **)malloc(innerClasses->num_classes * sizeof(Classes *));
		for (int position = 0; position < innerClasses->num_classes; position++)
		{
			*(innerClasses->classes_array + position) = readClasses(fp);
		}
	}
	return innerClasses;
}

Classes *readClasses(FILE *fp)
{
	Classes *classeret = (Classes *)malloc(sizeof(struct classes));
	classeret->inner_class_info = u2READ(fp);
	classeret->outer_class_info = u2READ(fp);
	classeret->inner_name = u2READ(fp);
	classeret->inner_class_access_flags = u2READ(fp);

	return classeret;
}

Stack_map_attribute *readStackMapTable(FILE *fp)
{
	Stack_map_attribute *stackMapTable = (Stack_map_attribute *)malloc(sizeof(struct stack_map_attribute));
	stackMapTable->num_entries = u2READ(fp);
	if (stackMapTable->num_entries > 0)
	{
		stackMapTable->entries = (Stack_map_frame **)malloc(stackMapTable->num_entries * sizeof(Stack_map_frame *));
		for (int i = 0; i < stackMapTable->num_entries; i++)
		{
			*(stackMapTable->entries + i) = readStackMapFrame(fp);
		}
	}
	return stackMapTable;
}

Stack_map_frame *readStackMapFrame(FILE *fp)
{
	Stack_map_frame *StackMapFrame = (Stack_map_frame *)malloc(sizeof(struct stack_map_frame));
	StackMapFrame->frame_type = u1READ(fp);
	if (StackMapFrame->frame_type >= 0 && StackMapFrame->frame_type <= 63)
	{
	}
	else if (StackMapFrame->frame_type >= 64 && StackMapFrame->frame_type <= 127)
	{
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame.stack = (Verification_type_info **)malloc(sizeof(Verification_type_info *));
		*(StackMapFrame->map_frame_type.same_locals_1_stack_item_frame.stack) = readVerificationTypeInfo(fp);
	}
	else if (StackMapFrame->frame_type == 247)
	{
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta = u2READ(fp);
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.stack = (Verification_type_info **)malloc(sizeof(Verification_type_info *));
		*(StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.stack) = readVerificationTypeInfo(fp);
	}
	else if (StackMapFrame->frame_type >= 248 && StackMapFrame->frame_type <= 250)
	{
		StackMapFrame->map_frame_type.chop_frame.offset_delta = u2READ(fp);
	}
	else if (StackMapFrame->frame_type == 251)
	{
		StackMapFrame->map_frame_type.same_frame_extended.offset_delta = u2READ(fp);
	}
	else if (StackMapFrame->frame_type >= 252 && StackMapFrame->frame_type <= 254)
	{
		StackMapFrame->map_frame_type.append_frame.offset_delta = u2READ(fp);
		u2 sizeMalloc = (StackMapFrame->frame_type - 251);
		StackMapFrame->map_frame_type.append_frame.locals = (Verification_type_info **)malloc(sizeMalloc * sizeof(Verification_type_info *));
		for (int position = 0; position < sizeMalloc; position++)
		{
			*(StackMapFrame->map_frame_type.append_frame.locals + position) = readVerificationTypeInfo(fp);
		}
	}
	else if (StackMapFrame->frame_type == 255)
	{
		StackMapFrame->map_frame_type.full_frame.offset_delta = u2READ(fp);
		StackMapFrame->map_frame_type.full_frame.num_locals = u2READ(fp);
		if (StackMapFrame->map_frame_type.full_frame.num_locals > 0)
		{
			StackMapFrame->map_frame_type.full_frame.locals = (Verification_type_info **)malloc(StackMapFrame->map_frame_type.full_frame.num_locals * sizeof(Verification_type_info *));
			for (int position = 0; position < StackMapFrame->map_frame_type.full_frame.num_locals; position++)
			{
				*(StackMapFrame->map_frame_type.full_frame.locals + position) = readVerificationTypeInfo(fp);
				if ((*(StackMapFrame->map_frame_type.full_frame.locals + position))->tag == 7)
				{
				}
			}
		}
		StackMapFrame->map_frame_type.full_frame.num_stack_items = u2READ(fp);
		if (StackMapFrame->map_frame_type.full_frame.num_stack_items > 0)
		{
			StackMapFrame->map_frame_type.full_frame.stack = (Verification_type_info **)malloc(StackMapFrame->map_frame_type.full_frame.num_stack_items * sizeof(Verification_type_info *));
			for (int position = 0; position < StackMapFrame->map_frame_type.full_frame.num_stack_items; position++)
			{
				*(StackMapFrame->map_frame_type.full_frame.stack + position) = readVerificationTypeInfo(fp);
			}
		}
	}
	return StackMapFrame;
}

Verification_type_info *readVerificationTypeInfo(FILE *fp)
{
	Verification_type_info *vti = (Verification_type_info *)malloc(sizeof(struct verification_type_info));
	vti->tag = u1READ(fp);
	switch (vti->tag)
	{
	case 7:
		vti->type_info.object_variable_info.cp = u2READ(fp);
		break;
	case 8:
		vti->type_info.uninitialized_variable_info.offset = u2READ(fp);
		break;
	default:
		break;
	}

	return vti;
}

Source_file_attribute *readSourceFile(FILE *fp)
{
	Source_file_attribute *sf;
	sf = (Source_file_attribute *)malloc(sizeof(struct source_file_attribute));
	sf->source_file = u2READ(fp);
	return sf;
}

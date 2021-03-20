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

#include "leitura.h"

/*Macro para leitura de um tipo u1 do arquivo .class*/
#define u1READ(fd) getc(fd)
/*Macro para leitura de um tipo u2 do arquivo .class*/
#define u2READ(fd) (getc(fd) << 8) | getc(fd)
/*Macro para leitura de um tipo u4 do arquivo .class*/
#define u4READ(fd) (getc(fd) << 24) | (getc(fd) << 16 | getc(fd) << 8 | getc(fd)

Classfile *readArquivo(Classfile *cf, char *nomeArquivo)
{
	FILE *fp = fopen(nomeArquivo, "rb"); // abre o arquivo .class em modo leitura binario

	if (!fp)
	{
		printf("Erro na abertura do arquivo .class, o programa sera encerrado...\n");
		exit(0);
	}

	cf->magic = u4READ(fp);
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
	cf->fieds = (cf->fields_count > 0) ? readFields(fp, cf->fields, cf->fields_count, cf->constant_pool) : NULL;

	// printf("Passou leitura field\n");

	/*Leitura do value 'methods_count', representando
    a quantidade de entradas na tabela Method*/
	cf->methods_count = u2READ(fp);
	//printf("Methods: %d\n",arquivoClass->methods_count);
	cf->methods = (cf->methods_count > 0) ? readMethods(fp, cf->methods_count, cf->constant_pool) : NULL;

	cf->attributes_count = u2READ(fp);
	if (cf->attributes_count > 0)
	{
		cf->attributes = (Attribute_info **)malloc(cf->attributes_count * sizeof(attribute_info *));
		for (int i = 0; i < cf->attributes_count; i++)
		{
			*(cf->attributes + i) = readAttrs(fp, *(cf->attributes + i), cf->constant_pool);
		}
	}

	fclose(fp);

	return cf;
}

Cp_info *readConstantPool(FILE *fp, Cp_info *cp, u2 cp_count)
{
	cp = (Cp_info *)malloc(cp_count * sizeof(Cp_info));

	for (Cp_info *p = cp; p < cp + cp_count - 1; p++)
	{
		p->tag = u1READ(fp);

		switch (p->tag)
		{
		case CONSTANT_Class:
			p->cp_union.Class.name_index = u2READ(fp);
			break;

		case CONSTANT_Fieldref:
			p->cp_union.Fieldref.class_index = u2READ(fp);
			p->cp_union.Fieldref.name_and_type_index = u2READ(fp);
			break;

		case CONSTANT_Methodref:
			p->cp_union.Methodref.class_index = u2READ(fp);
			p->cp_union.Methodref.name_and_type_index = u2READ(fp);
			break;

		case CONSTANT_InterfaceMethodref:
			p->cp_union.InterfaceMethodref.class_index = u2READ(fp);
			p->cp_union.InterfaceMethodref.name_and_type_index = u2READ(fp);
			break;

		case CONSTANT_String:
			p->cp_union.String.string_index = u2READ(fp);
			break;

		case CONSTANT_Integer:
			p->cp_union.Integer.bytes = u4READ(fp);
			break;

		case CONSTANT_Float:
			p->cp_union.Float.bytes = u4READ(fp);
			break;

		case CONSTANT_Long:
			p->cp_union.Long.high_bytes = u4READ(fp);
			p->cp_union.Long.low_bytes = u4READ(fp);
			p++;
			break;

		case CONSTANT_Double:
			p->cp_union.Double.high_bytes = u4READ(fp);
			p->cp_union.Double.low_bytes = u4READ(fp);
			p++;
			break;

		case CONSTANT_NameAndType:
			p->cp_union.NameAndType.name_index = u2READ(fp);
			p->cp_union.NameAndType.descriptor_index = u2READ(fp);
			break;

		case CONSTANT_Utf8:
			p->cp_union.UTF8.length = u2READ(fp);
			p->cp_union.UTF8.bytes = malloc(p->cp_union.UTF8.length * sizeof(u1));
			for (u1 *i = p->cp_union.UTF8.bytes; i < p->cp_union.UTF8.bytes + p->cp_union.UTF8.length; i++)
			{
				*i = u1READ(fp);
			}
			break;

		case CONSTANT_MethodHandle:
			p->cp_union.MethodHandle.reference_kind = u1READ(fp);
			p->cp_union.MethodHandle.reference_index = u2READ(fp);
			break;

		case CONSTANT_MethodType:
			p->cp_union.MethodType.descriptor_index = u2READ(fp);
			break;

		case CONSTANT_InvokeDynamic:
			p->cp_union.InvokeDynamicInfo.bootstrap_method_attr_index = u2READ(fp);
			p->cp_union.InvokeDynamicInfo.name_and_type_index = u2READ(fp);
			break;

		default:
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

Field_info *readFields(File *fp, Field_info *field, u2 f_count, Cp_info *cp)
{
	field = (Field_info *)malloc(f_count * sizeof(Field_info));

	for (Field_info *p = field; p < field + f_count; p++)
	{
		p->access_flags = u2READ(fp);
		p->name_index = u2READ(fp);
		p->descriptor_index = u2READ(fp);
		p->attributes_count = u2READ(fp);

		if (p->attributes_count > 0)
		{
			p->attributes = (Attribute_info **)malloc(p->attributes_count * sizeof(Attribute_info *));
			for (int i = 0; i < p->attributes_count; p++)
			{
				*(p->attributes + i) = readAttributes(fp, cp);
			}
		}
	}

	return field;
}

Method_info *readMethods(FILE *fp, Method_info *metodo, u2 m_count, Cp_info *cp)
{
	metodo = (Method_info *)malloc(m_count * sizeof(Method_info));

	for (Method_info *p = metodo; p < metodo + m_count; p++)
	{
		p->access_flags = u2READ(fp);
		p->name_index = u2READ(fp);
		p->descriptor_index = u2READ(fp);
		p->attributes_count = u2READ(fp);

		/*Estrutura condicional que avalia se a quantidade de atributos
		do método é maior que zero. Se for, prossegue com a leitura dos
		atributos do método*/
		Attribute_info *atributos = (Attribute_info *)malloc(p->attributes_count * sizeof(Attribute_info));

		if (p->attributes_count > 0)
		{
			p->attributes = (Attribute_info **)malloc(i->attributes_count * sizeof(Attribute_info *));
			for (int i = 0; i < p->attributes_count; i++)
			{
				*(p->attributes + i) = leAttrs(fp, *(p->attributes + i), cp);
			}
		}
	}

	return metodo;
}

code_attribute *readCode(FILE *fp, cp_info *cp)
{
	code_attribute *code_attributes = NULL;
	code_attributes = (code_attribute *)malloc(sizeof(code_attribute));
	code_attributes->max_stack = u2READ(fp);
	code_attributes->max_locals = u2READ(fp);
	code_attributes->code_length = u4READ(fp);
	if (code_attributes->code_length > 0)
	{
		code_attributes->code = malloc(code_attributes->code_length * sizeof(u1));
		for (u1 *p = code_attributes->code; p < code_attributes->code + code_attributes->code_length; p++)
		{
			*p = u1Read(fp);
		}
	}

	code_attributes->exception_table_length = u2READ(fp);

	if (code_attributes->exception_table_length > 0)
	{
		code_attributes->table = NULL; //malloc(code_attributes->exception_table_length*sizeof(exception_table));
		code_attributes->table = readExceptionTable(fp, code_attributes->exception_table_length);
	}

	code_attributes->attributes_count = u2READ(fp);
	// u2 auxCodeAttrCount = code_attributes->attributes_count;
	// char * string_name_index = malloc(100*sizeof(char));

	if (code_attributes->attributes_count > 0)
	{
		code_attributes->attributes = (attribute_info **)malloc(code_attributes->attributes_count * sizeof(attribute_info *));
		for (int position = 0; position < code_attributes->attributes_count; position++)
		{
			*(code_attributes->attributes + position) = readAttributes(fp, cp);
		}
	}

	return code_attributes;
}

line_number_table *readLineNumberTable(FILE *fp, cp_info *cp)
{
	line_number_table *lnt = (line_number_table *)malloc(sizeof(line_number_table));
	lnt->line_number_table_length = u2READ(fp);
	if (lnt->line_number_table_length > 0)
	{
		lnt->info = (line_number_tableInfo *)malloc(lnt->line_number_table_length * sizeof(line_number_tableInfo));
		for (line_number_tableInfo *linfo = lnt->info; linfo < lnt->info + lnt->line_number_table_length; linfo++)
		{
			linfo->start_pc = u2READ(fp);
			linfo->line_number = u2READ(fp);
		}
	}
	return lnt;
}

exception_table *readExceptionTable(FILE *fp, u2 size)
{
	exception_table *exception_tableAux = (exception_table *)malloc(size * sizeof(exception_table));
	for (exception_table *e = exception_tableAux; e < exception_tableAux + size; e++)
	{
		e->start_pc = u2READ(fp);
		e->end_pc = u2READ(fp);
		e->handread_pc = u2READ(fp);
		e->catch_type = u2READ(fp);
	}
	return exception_tableAux;
}

Attribute_info *readAttrs(FILE *fp, Attribute_info *a, Cp_info *cp)
{
	a = (Attribute_info *)malloc(sizeof(Attribute_info));

	a->attribute_name_index = u2READ(fp);
	a->attribute_length = u4READ(fp);

	//printf("att name index: %d\n",attributes->attribute_name_index);
	//printf("attr length: %d\n",attributes->attribute_length);

	if (a->attribute_length > 0)
	{
		char *string_name_index;
		string_name_index = decodeUTF8String(cp + attributes->attribute_name_index - 1);

		if (strcmp(string_name_index, "SourceFile") == 0)
		{
			//printf("Entrou sourcefile\n");
			source_file_attribute *SourceFile = NULL; //(code_attribute*) malloc(i->attributes_count*sizeof(code_attribute));
			SourceFile = readSourceFile(fp);
			a->info = NULL; //malloc(i->attributes_count*sizeof(code_attribute));
			a->info = (source_file_attribute *)SourceFile;
		}
		else if (strcmp(string_name_index, "Code") == 0)
		{
			printf("Entrou code\n");
			code_attribute *code_attr = NULL;
			code_attr = readCode(fp, cp);
			a->info = (code_attribute *)code_attr;
		}
		else if (strcmp(string_name_index, "LineNumberTable") == 0)
		{
			line_number_table *lnt = NULL;
			printf("Entrou lnt\n");
			lnt = readLineNumberTable(fp, cp);
			a->info = (line_number_table *)lnt;
		}
		else if (strcmp(string_name_index, "StackMapTable") == 0)
		{
			printf("Entrou stack map table\n");
			stackMapTable_attribute *stackMapTable = NULL;
			stackMapTable = readStackMapTable(fp);
			printf("Saiu de smt\n");
			a->info = (stackMapTable_attribute *)stackMapTable;
		}
		else if (strcmp(string_name_index, "InnerClasses") == 0)
		{
			printf("Entrou em inner class\n");
			innerClasses_attribute *innerClasses = NULL;
			innerClasses = readInnerClasses(fp, cp);
			a->info = (innerClasses_attribute *)innerClasses;
		}
		else if (strcmp(string_name_index, "Signature") == 0)
		{
			printf("Entrou em signature\n");
			signature_attribute *signatureR = NULL;
			signatureR = readSignature(fp);
			a->info = (signature_attribute *)signatureR;
		}
		else if (strcmp(string_name_index, "ConstantValue") == 0)
		{
			constantValue_attribute *constantV = NULL;
			constantV = readConstantValue(fp);
			a->info = (constantValue_attribute *)constantV;
		}
		else if (strcmp(string_name_index, "Exceptions") == 0)
		{
			exceptions_attribute *exceptions = NULL;
			exceptions = readreadExceptionAttributes(fp);
			a->info = (exceptions_attribute *)exceptions;
		}
	}

	return a;
}

exceptions_attribute *readreadExceptionAttributes(FILE *fp)
{
	exceptions_attribute *exceptions = (exceptions_attribute *)malloc(sizeof(exceptions_attribute));
	exceptions->number_of_exceptions = u2Read(fp);
	exceptions->exception_index_table = NULL;
	if (exceptions->number_of_exceptions > 0)
	{
		exceptions->exception_index_table = (u2 *)malloc(exceptions->number_of_exceptions * sizeof(u2));
		for (u2 *excpAux = exceptions->exception_index_table; excpAux < exceptions->exception_index_table + exceptions->number_of_exceptions; excpAux++)
		{
			*excpAux = u2Read(fp);
		}
	}
	return exceptions;
}

constantValue_attribute *readConstantValue(FILE *fp)
{
	constantValue_attribute *cv = (constantValue_attribute *)malloc(sizeof(constantValue_attribute));
	cv->constantvalue_index = u2Read(fp);
	return cv;
}

signature_attribute *readSignature(FILE *fp)
{
	signature_attribute *signature = (signature_attribute *)malloc(sizeof(signature_attribute));
	signature->signature_index = u2Read(fp);
	return signature;
}

innerClasses_attribute *readInnerClasses(FILE *fp, cp_info *cp)
{
	innerClasses_attribute *innerClasses = (innerClasses_attribute *)malloc(sizeof(innerClasses_attribute));
	innerClasses->number_of_classes = u2Read(fp);
	if (innerClasses->number_of_classes > 0)
	{
		innerClasses->classes_vector = (classes **)malloc(innerClasses->number_of_classes * sizeof(classes *));
		for (int position = 0; position < innerClasses->number_of_classes; position++)
		{
			*(innerClasses->classes_vector + position) = readClasses(fp);
		}
	}
	return innerClasses;
}

classes *readClasses(FILE *fp)
{
	classes *classeret = (classes *)malloc(sizeof(classes));
	classeret->inner_class_info_index = u2Read(fp);
	classeret->outer_class_info_index = u2Read(fp);
	classeret->inner_name_index = u2Read(fp);
	classeret->inner_class_access_flags = u2Read(fp);

	return classeret;
}

stackMapTable_attribute *readStackMapTable(FILE *fp)
{
	stackMapTable_attribute *stackMapTable = (stackMapTable_attribute *)malloc(sizeof(stackMapTable_attribute));
	stackMapTable->number_of_entries = u2Read(fp);
	if (stackMapTable->number_of_entries > 0)
	{
		stackMapTable->entries = (stack_map_frame **)malloc(stackMapTable->number_of_entries * sizeof(stack_map_frame *));
		for (int position = 0; position < stackMapTable->number_of_entries; position++)
		{
			*(stackMapTable->entries + position) = readStackMapFrame(fp);
		}
	}
	return stackMapTable;
}

stack_map_frame *readStackMapFrame(FILE *fp)
{
	stack_map_frame *StackMapFrame = (stack_map_frame *)malloc(sizeof(stack_map_frame));
	StackMapFrame->frame_type = u1Read(fp);
	if (StackMapFrame->frame_type >= 0 && StackMapFrame->frame_type <= 63)
	{
	}
	else if (StackMapFrame->frame_type >= 64 && StackMapFrame->frame_type <= 127)
	{
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame.stack = (verification_type_info **)malloc(sizeof(verification_type_info *));
		*(StackMapFrame->map_frame_type.same_locals_1_stack_item_frame.stack) = readVerificationTypeInfo(fp);
	}
	else if (StackMapFrame->frame_type == 247)
	{
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta = u2Read(fp);
		StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.stack = (verification_type_info **)malloc(sizeof(verification_type_info *));
		*(StackMapFrame->map_frame_type.same_locals_1_stack_item_frame_extended.stack) = readVerificationTypeInfo(fp);
	}
	else if (StackMapFrame->frame_type >= 248 && StackMapFrame->frame_type <= 250)
	{
		StackMapFrame->map_frame_type.chop_frame.offset_delta = u2Read(fp);
	}
	else if (StackMapFrame->frame_type == 251)
	{
		StackMapFrame->map_frame_type.same_frame_extended.offset_delta = u2Read(fp);
	}
	else if (StackMapFrame->frame_type >= 252 && StackMapFrame->frame_type <= 254)
	{
		StackMapFrame->map_frame_type.append_frame.offset_delta = u2Read(fp);
		u2 sizeMalloc = (StackMapFrame->frame_type - 251);
		StackMapFrame->map_frame_type.append_frame.locals = (verification_type_info **)malloc(sizeMalloc * sizeof(verification_type_info *));
		for (int position = 0; position < sizeMalloc; position++)
		{
			*(StackMapFrame->map_frame_type.append_frame.locals + position) = readVerificationTypeInfo(fp);
		}
	}
	else if (StackMapFrame->frame_type == 255)
	{
		StackMapFrame->map_frame_type.full_frame.offset_delta = u2Read(fp);
		StackMapFrame->map_frame_type.full_frame.number_of_locals = u2Read(fp);
		if (StackMapFrame->map_frame_type.full_frame.number_of_locals > 0)
		{
			StackMapFrame->map_frame_type.full_frame.locals = (verification_type_info **)malloc(StackMapFrame->map_frame_type.full_frame.number_of_locals * sizeof(verification_type_info *));
			for (int position = 0; position < StackMapFrame->map_frame_type.full_frame.number_of_locals; position++)
			{
				*(StackMapFrame->map_frame_type.full_frame.locals + position) = readVerificationTypeInfo(fp);
				if ((*(StackMapFrame->map_frame_type.full_frame.locals + position))->tag == 7)
				{
				}
			}
		}
		StackMapFrame->map_frame_type.full_frame.number_of_stack_items = u2Read(fp);
		if (StackMapFrame->map_frame_type.full_frame.number_of_stack_items > 0)
		{
			StackMapFrame->map_frame_type.full_frame.stack = (verification_type_info **)malloc(StackMapFrame->map_frame_type.full_frame.number_of_stack_items * sizeof(verification_type_info *));
			for (int position = 0; position < StackMapFrame->map_frame_type.full_frame.number_of_stack_items; position++)
			{
				*(StackMapFrame->map_frame_type.full_frame.stack + position) = readVerificationTypeInfo(fp);
			}
		}
	}
	return StackMapFrame;
}

verification_type_info *readVerificationTypeInfo(FILE *fp)
{
	verification_type_info *VTI = (verification_type_info *)malloc(sizeof(verification_type_info));
	VTI->tag = u1Read(fp);
	switch (VTI->tag)
	{
	case 7:
		VTI->type_info.object_variable_info.cpool_index = u2Read(fp);
		break;
	case 8:
		VTI->type_info.uninitialized_variable_info.offset = u2Read(fp);
		break;
	default:
		break;
	}

	return VTI;
}

source_file_attribute *readSourceFile(FILE *fp)
{
	source_file_attribute *SourceFile = NULL;
	SourceFile = (source_file_attribute *)malloc(sizeof(source_file_attribute));
	SourceFile->source_file_index = u2Read(fp);
	return SourceFile;
}

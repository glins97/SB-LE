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

#include "exibidor.h"
#include <string.h>
#include <math.h>
#include "leitor.h"

#define SEPARADOR printf("______________________________________________________________________________\n");

/* FUNÇÃO PRINCIPAL: print ARQUIVO .CLASS NA TELA DO USUÁRIO CONFORME jclasslib */

char *printPointer;
double value;
uint64_t longValue;
Method_info *auxMethod;
Attribute_info **auxAttributeClasse;

void printClassfile(Classfile *cf)
{
	//	instrucao *instructions = construirinstructions();
	SEPARADOR;
	printf("GENERAL INFORMATION\n");
	SEPARADOR;
	printf("Magic: %08x\n", cf->magic);
	printf("Minor Version: %04x\n", cf->minor_version);
	printf("Major Version: %04x\n", cf->major_version);
	printf("Constant Pool Count: %04x\n", cf->constant_pool_count);
	printf("Access Flags: %04x\n", cf->access_flags);
	printf("This Class: %04x\n", cf->this_class);
	printf("Super Class: %04x\n", cf->super_class);
	printf("Interfaces Count: %04x\n", cf->interfaces_count);
	printf("Fields Count: %04x\n", cf->fields_count);
	printf("Methods Count: %04x\n", cf->methods_count);
	printf("Atributes Count: %02x\n", cf->attributes_count);
	SEPARADOR;

	printf("\n\n----------CONSTANT POOL----------\n\n");
	printConstantPool(cf);

	printf("\n\n----------INTERFACES----------\n\n");
	for (u2 *auxInterfaces = cf->interfaces; auxInterfaces < cf->interfaces + cf->interfaces_count; auxInterfaces++)
	{
		printPointer = decodeNINT(cf->constant_pool, *auxInterfaces, NAME_INDEX);
		printf("Interface: cp_info#%d <%s>\n", *auxInterfaces, printPointer);
	}

	printf("\n\n----------FIELDS----------\n\n");
	printFields(cf);

	printf("\n\n-----METODOS-----\n\n");
	printMethods(cf);

	printf("\n\n-----ATRIBUTOS DA CLASSE-----\n\n");
	printAttrsClasse(cf);
}

void printConstantPool(Classfile *cf)
{
	uint32_t entrada = 1; // counter para indicar o número da entrada na constant pool

	for (Cp_info *aux = cf->constant_pool; aux < cf->constant_pool + cf->constant_pool_count - 1; aux++)
	{
		printf("--------------Entrada [%d]--------------\n", entrada++);
		printf("TAG: %02d: %s\n", aux->tag, searchNameTag(aux->tag));

		switch (aux->tag)
		{
		case CONSTANT_Class:
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.Class.name, CLASS_INDEX);
			printf("Class Name: cp_info#%02d <%s>\n", aux->cp_union.Class.name, printPointer);
			break;
		case CONSTANT_Field:
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.Field.class_name, NAME_INDEX);
			printf("Class Name: cp_info#%02d <%s>\n", aux->cp_union.Field.class_name, printPointer);
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.Field.name_and_type, NAME_AND_TYPE);
			printf("Name and Type: cp_info#%02d <%s>\n", aux->cp_union.Field.name_and_type, printPointer);
			break;
		case CONSTANT_Method:
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.Method.class_name, NAME_INDEX);
			printf("Class Name: cp_info#%02d <%s>\n", aux->cp_union.Method.class_name, printPointer);
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.Method.name_and_type, NAME_AND_TYPE);
			printf("Name and Type: cp_info#%02d <%s>\n", aux->cp_union.Method.name_and_type, printPointer);
			break;
		case CONSTANT_InterfaceMethod:
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.String.string, NAME_INDEX);
			printf("Class Name: cp_info#%02d <%s>\n", aux->cp_union.InterfaceMethod.class_name, printPointer);
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.String.string, NAME_AND_TYPE);
			printf("Name and Type Index: cp_info#%02d <%s>\n", aux->cp_union.InterfaceMethod.name_and_type, printPointer);
			break;
		case CONSTANT_String:
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.String.string, STRING_INDEX);
			printf("String: cp_info#%02d <%s>\n", aux->cp_union.String.string, printPointer);
			break;
		case CONSTANT_Integer:
			printf("Bytes: %04x\n", aux->cp_union.Integer.bytes);
			printf("Integer: %d\n", aux->cp_union.Integer.bytes);
			break;
		case CONSTANT_Float:
			printf("Bytes: %04x\n", aux->cp_union.Float.bytes);
			printf("Float: %d\n", aux->cp_union.Float.bytes);
			break;
		case CONSTANT_Long:
			longValue = decodeLongInfo(aux);
			printf("Long High Bytes: 0x%08x\n", aux->cp_union.Long.hi_bytes);
			printf("Long Low Bytes: 0x%08x\n", aux->cp_union.Long.lo_bytes);
			printf("Long: %lu\n", longValue);
			break;
		case CONSTANT_Double:
			value = decodeDoubleInfo(aux);
			printf("Double High Bytes: 0x%08x\n", aux->cp_union.Double.hi_bytes);
			printf("Double Low Bytes: 0x%08x\n", aux->cp_union.Double.lo_bytes);
			printf("Double: %lf\n", value);
			break;
		case CONSTANT_NameAndType:
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.NameAndType.name, NAME_AND_TYPE_INFO_NAME_INDEX);
			printf("Name: cp_info#%02d <%s>\n", aux->cp_union.NameAndType.name, printPointer);
			printPointer = decodeNINT(cf->constant_pool, aux->cp_union.NameAndType.descriptor, NAME_AND_TYPE_INFO_DESCRIPTOR_INDEX);
			printf("Descriptor: cp_info#%02d <%s>\n", aux->cp_union.NameAndType.descriptor, printPointer);
			break;
		case CONSTANT_Utf8:
			printf("Length of byte array: %d\n", (int)aux->cp_union.Utf8.length);
			printf("Length of string: %d\n", (int)aux->cp_union.Utf8.length);
			printf("String: ");
			for (u1 *i = aux->cp_union.Utf8.bytes; i < aux->cp_union.Utf8.bytes + aux->cp_union.Utf8.length; i++)
			{
				printf("%c", (char)(*i));
			}
			printf("\n");
			break;
		case CONSTANT_MethodHandle:
			printf("MethodHandle Reference Kind: %02x\n", aux->cp_union.MethodHandle.reference_kind);
			printf("MethodHandle Reference Index: %04x\n", aux->cp_union.MethodHandle.reference);
			break;
		case CONSTANT_MethodType:
			printf("MethodType Descriptor Index: %04x\n", aux->cp_union.MethodType.descriptor);
			break;
		case CONSTANT_InvokeDynamic:
			printf("InvokeDynamic - Bootstrap Method Attr Index: %04x\n", aux->cp_union.InvokeDynamic.bootstrap_method_attr);
			printf("InvokeDynamic - Name and Type Index: %04x\n", aux->cp_union.InvokeDynamic.name_and_type);
			break;
		default:
			printf("DefaultImpressao\n");
			break;
		}
	}
}

void printFields(Classfile *cf)
{
	uint32_t field = 0;
	Attribute_info **fieldAttrAux;
	for (Field_info *auxField = cf->fields; auxField < cf->fields + cf->fields_count; auxField++, field++)
	{
		printf("--------------Field [%d]--------------\n\n", counter);
		printPointer = decodeUTF8String(cf->constant_pool - 1 + auxField->name);
		printf("Name: cp_info#%d <%s>\n", auxField->name, printPointer);
		printPointer = decodeUTF8String(cf->constant_pool - 1 + auxField->descriptor);
		printf("Descriptor: cp_info#%d <%s>\n", auxField->descriptor, printPointer);
		printPointer = decodeAccessFlags(auxField->access_flags);
		printf("Access Flags: 0x%04x [%s]\n", auxField->access_flags, printPointer);
		printf("Attributes Count: %d\n", auxField->attributes_count);
		if (auxField->attributes_count > 0)
		{
			fieldAttrAux = auxField->attributes;
			for (int positionFields = 0; positionFields < auxField->attributes_count; positionFields++)
			{
				printPointer = decodeUTF8String(cf->constant_pool - 1 + (*(fieldAttrAux + positionFields))->attribute_name);
				printf("Attribute Name Index: cp_info#%d <%s>\n", (*(fieldAttrAux + positionFields))->attribute_name, printPointer);
				printf("Attribute Length: %d\n", (*(fieldAttrAux + positionFields))->attribute_length);
				if (strcmp(printPointer, "ConstantValue") == 0)
				{
					Constant_value_attribute *cvAux = (Constant_value_attribute *)(*(fieldAttrAux + positionFields))->info;
					Cp_info *cpInfoAux = cf->constant_pool - 1 + cvAux->constant_value;
					if (cpInfoAux->tag == 4)
					{
						float valueCV = decodeFloatInfo(cf->constant_pool - 1 + cvAux->constant_value);
						printf("Constant Value Index: cp_info#%d <%f>\n", cvAux->constant_value, valueCV);
					}
					else if (cpInfoAux->tag == 3)
					{
						int valueret = decodeIntegerInfo(cf->constant_pool - 1 + cvAux->constant_value);
						printf("Constant Value Index: cp_info#%d <%d>\n", cvAux->constant_value, valueret);
					}
					else if (cpInfoAux->tag == 8)
					{
						char *stringEntrada = decodeNINT(cf->constant_pool, cvAux->constant_value, NAME_INDEX);
						printf("Constant Value Index: cp_info#%d <%s>\n", cvAux->constant_value, stringEntrada);
					}
					else if (cpInfoAux->tag == 6)
					{
						double valueDB = decodeDoubleInfo(cf->constant_pool - 1 + cvAux->constant_value);
						printf("Constant Value Index: cp_info#%d <%lf>\n", cvAux->constant_value, valueDB);
					}
					else if (cpInfoAux->tag == 5)
					{
						uint64_t valueL = decodeLongInfo(cf->constant_pool - 1 + cvAux->constant_value);
						printf("Constant Value Index: cp_info#%d <%lu>\n", cvAux->constant_value, valueL);
					}
				}
				else if (strcmp(printPointer, "Signature") == 0)
				{
					Signature_attribute *sig = (Signature_attribute *)(*(fieldAttrAux + positionFields))->info;
					char *Signature_Index = decodeUTF8String(cf->constant_pool - 1 + sig->signature);
					printf("Signature index: cp_info#%d <%s>\n", sig->signature, Signature_Index);
				}
			}
		}
	}
}

void printMethods(Classfile *cf)
{
	uint32_t method = 0;

	for (Method_info *auxMethod = cf->methods; auxMethod < cf->methods + cf->methods_count; auxMethod++, method++)
	{
		printf("--------------Metodo [%d]--------------\n\n", counter);
		printPointer = decodeUTF8String(cf->constant_pool - 1 + auxMethod->name);
		printf("Name: cp_info#%d <%s>\n", auxMethod->name, printPointer);
		printPointer = decodeUTF8String(cf->constant_pool - 1 + auxMethod->descriptor);
		printf("Descriptor: cp_info#%d <%s>\n", auxMethod->descriptor, printPointer);
		printPointer = decodeAccessFlags(auxMethod->access_flags);
		printf("Access Flags: 0x%04x [%s]\n", auxMethod->access_flags, printPointer);
		printf("Attributes Count: %d\n", auxMethod->attributes_count);

		printf("Attrs:\n");
		Attribute_info **auxAttrCompleto = auxMethod->attributes;
		for (int position = 0; position < auxMethod->attributes_count; position++)
		{ // for - 1
			printPointer = decodeUTF8String(cf->constant_pool - 1 + (*(auxAttrCompleto + position))->attribute_name);
			printf("Attribute Name Index: cp_info#%d <%s>\n", (*(auxAttrCompleto + position))->attribute_name, printPointer);
			printf("Attribute Length: %d\n", (*(auxAttrCompleto + position))->attribute_length);

			if (strcmp(printPointer, "Code") == 0)
			{
				Code_attribute *auxCodePontual = (Code_attribute *)(*(auxAttrCompleto + position))->info;
				printf("Max Stack: %d\n", auxCodePontual->max_stack);
				printf("Max Locals: %d\n", auxCodePontual->max_locals);
				printf("Code length: %d\n", auxCodePontual->code_length);
				printf("\n\n----Code----\n\n");
				if (auxCodePontual->code_length > 0)
				{
					printPointer = decode(cf->constant_pool, cf->constant_pool_count, auxCodePontual->code, auxCodePontual->code_length, instructions);
					printf("%s\n", printPointer);
				}
				if (auxCodePontual->exception_info_length > 0)
				{
					printf("Exception Table:\n");
					printf("Nr.\t\tStart PC\tEnd PC\tHandread PC\tCatch Type\n");
					int counterExceptionTable = 0;
					for (Exception_info *exceptionTableAux = auxCodePontual->ex_info; exceptionTableAux < (auxCodePontual->ex_info + auxCodePontual->exception_info_length); exceptionTableAux++)
					{
						printf("%d\t\t%02x\t\t%02x\t\t%02x\t%02x\n", counterExceptionTable, exceptionTableAux->start_pc, exceptionTableAux->end_pc, exceptionTableAux->handread_pc, exceptionTableAux->catch_type);
						counterExceptionTable++;
					}
					printf("\n\n");
				}
				printf("Attributes Count: %d\n", auxCodePontual->attributes_count);
				if (auxCodePontual->attributes_count > 0)
				{
					int lntcounter = 0;
					Attribute_info **auxAttributesFromCode = auxCodePontual->attributes;
					for (int positionDois = 0; positionDois < auxCodePontual->attributes_count; positionDois++)
					{
						printPointer = decodeUTF8String(cf->constant_pool - 1 + (*(auxAttributesFromCode + positionDois))->attribute_name);
						printf("Attribute Name Index: cp_info#%d <%s>\n", (*(auxAttributesFromCode + positionDois))->attribute_name, printPointer);
						printf("Attribute Length: %d\n", (*(auxAttributesFromCode + positionDois))->attribute_length);
						if (strcmp(printPointer, "LineNumberTable") == 0)
						{
							Line_number_table *lntAux = (Line_number_table *)(*(auxAttributesFromCode + positionDois))->info;
							printf("Line Number Table Length: %d\n", (int)lntAux->line_number_length);
							printf("Attribute Info: \n");
							printf("Nr.\t\tStartPC\t\tLineNumber\n");
							for (Line_number_info *linfo = lntAux->info; linfo < lntAux->info + lntAux->line_number_length; linfo++)
							{
								printf("%d\t\t%d\t\t%d\n", lntcounter, linfo->start_pc, linfo->line_number);
								lntcounter++;
							}
							printf("\n");
						}
						else if (strcmp(printPointer, "StackMapTable") == 0)
						{
							int offsetImpressao = 0;
							Stack_map_attribute *smt = (Stack_map_attribute *)(*(auxAttributesFromCode + positionDois))->info;
							Stack_map_frame **smf = smt->entries;
							printf("Nr.\t\tStack Map Frame\n");
							for (int positionSMF = 0; positionSMF < smt->num_entries; positionSMF++)
							{
								if ((*(smf + positionSMF))->frame_type >= 0 && (*(smf + positionSMF))->frame_type <= 63)
								{
									offsetImpressao += setPrintOffset(positionSMF, (*(smf + positionSMF))->frame_type);
									printf("%d\t\tSAME(%d),Offset: %d(+%d)\n", positionSMF, (*(smf + positionSMF))->frame_type, offsetImpressao, (*(smf + positionSMF))->frame_type);
								}
								else if ((*(smf + positionSMF))->frame_type >= 64 && (*(smf + positionSMF))->frame_type <= 127)
								{
									offsetImpressao += setPrintOffset(positionSMF, ((*(smf + positionSMF))->frame_type) - 64);
									printf("%d\t\tSAME_LOCALS_1_STACK_ITEM(%d), Offset: %d(+%d)\n", positionSMF, (*(smf + positionSMF))->frame_type, offsetImpressao, ((*(smf + positionSMF))->frame_type - 64));
									printf("\t\tStack verifications:\n");
									Verification_type_info **VTIAux = (*(smf + positionSMF))->map_frame_type.same_locals_1_stack_item_frame.stack;
									switch ((*(VTIAux))->tag)
									{
									case 0:
										printf("\t\t\tTOP\n");
										break;
									case 1:
										printf("\t\t\tINTEGER\n");
										break;
									case 2:
										printf("\t\t\tFLOAT\n");
										break;
									case 3:
										printf("\t\t\tLONG\n");
										break;
									case 4:
										printf("\t\t\tDOUBLE\n");
										break;
									case 5:
										printf("\t\t\tNULL\n");
										break;
									case 6:
										printf("\t\t\tUNINITIALIZED THIS\n");
										break;
									case 7:
										printPointer = decodeNINT(cf->constant_pool, (*(VTIAux))->type_info.object_variable_info.cp, NAME_INDEX);
										printf("\t\t\tOBJECT cp_info#%d <%s>\n", (*(VTIAux))->type_info.object_variable_info.cp, printPointer);
										break;
									case 8:
										printf("\t\t\tUNINITIALIZED Offset: %d\n", (*(VTIAux))->type_info.uninitialized_variable_info.offset);
										break;
									}
								}
								else if ((*(smf + positionSMF))->frame_type == 247)
								{
									offsetImpressao += setPrintOffset(positionSMF, (*(smf + positionSMF))->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta);
									printf("%d\t\tSAME_LOCALS_1_STACK_ITEM_EXTENDED(%d), Offset: %d(+%d)\n", positionSMF, (*(smf + positionSMF))->frame_type, offsetImpressao, (*(smf + positionSMF))->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta);
									printf("\t\tStack verifications:\n");
									Verification_type_info **VTIAux = (*(smf + positionSMF))->map_frame_type.same_locals_1_stack_item_frame_extended.stack;
									switch ((*(VTIAux))->tag)
									{
									case 0:
										printf("\t\t\tTOP\n");
										break;
									case 1:
										printf("\t\t\tINTEGER\n");
										break;
									case 2:
										printf("\t\t\tFLOAT\n");
										break;
									case 3:
										printf("\t\t\tLONG\n");
										break;
									case 4:
										printf("\t\t\tDOUBLE\n");
										break;
									case 5:
										printf("\t\t\tNULL\n");
										break;
									case 6:
										printf("\t\t\tUNINITIALIZED THIS\n");
										break;
									case 7:
										printPointer = decodeNINT(cf->constant_pool, (*(VTIAux))->type_info.object_variable_info.cp, NAME_INDEX);
										printf("\t\t\tOBJECT cp_info#%d <%s>\n", (*(VTIAux))->type_info.object_variable_info.cp, printPointer);
										break;
									case 8:
										printf("\t\t\tUNINITIALIZED Offset: %d\n", (*(VTIAux))->type_info.uninitialized_variable_info.offset);
										break;
									}
								}
								else if ((*(smf + positionSMF))->frame_type >= 248 && (*(smf + positionSMF))->frame_type <= 250)
								{
									offsetImpressao += setPrintOffset(positionSMF, (*(smf + positionSMF))->map_frame_type.chop_frame.offset_delta);
									printf("%d\t\tCHOP(%d),Offset: %d(+%d)\n", positionSMF, (*(smf + positionSMF))->frame_type, offsetImpressao, (*(smf + positionSMF))->map_frame_type.chop_frame.offset_delta);
								}
								else if ((*(smf + positionSMF))->frame_type == 251)
								{
									offsetImpressao += setPrintOffset(positionSMF, (*(smf + positionSMF))->map_frame_type.same_frame_extended.offset_delta);
									printf("%d\t\tSAME_FRAME_EXTENDED(%d),Offset: %d(+%d)\n", positionSMF, (*(smf + positionSMF))->frame_type, offsetImpressao, (*(smf + positionSMF))->map_frame_type.same_frame_extended.offset_delta);
								}
								else if ((*(smf + positionSMF))->frame_type >= 252 && (*(smf + positionSMF))->frame_type <= 254)
								{
									offsetImpressao += setPrintOffset(positionSMF, (*(smf + positionSMF))->map_frame_type.append_frame.offset_delta);
									printf("%d\t\tAPPEND(%d),Offset: %d(+%d)\n", positionSMF, (*(smf + positionSMF))->frame_type, offsetImpressao, (*(smf + positionSMF))->map_frame_type.append_frame.offset_delta);
									Verification_type_info **VTIAux = (*(smf + positionSMF))->map_frame_type.append_frame.locals;
									printf("\t\t  Local verifications:\n");
									for (int positionVTI = 0; positionVTI < ((*(smf + positionSMF))->frame_type - 251); positionVTI++)
									{
										switch ((*(VTIAux + positionVTI))->tag)
										{
										case 0:
											printf("\t\t\tTOP\n");
											break;
										case 1:
											printf("\t\t\tINTEGER\n");
											break;
										case 2:
											printf("\t\t\tFLOAT\n");
											break;
										case 3:
											printf("\t\t\tLONG\n");
											break;
										case 4:
											printf("\t\t\tDOUBLE\n");
											break;
										case 5:
											printf("\t\t\tNULL\n");
											break;
										case 6:
											printf("\t\t\tUNINITIALIZED THIS\n");
											break;
										case 7:
											printPointer = decodeNINT(cf->constant_pool, (*(VTIAux + positionVTI))->type_info.object_variable_info.cp, NAME_INDEX);
											printf("\t\t\tOBJECT cp_info#%d <%s>\n", (*(VTIAux + positionVTI))->type_info.object_variable_info.cp, printPointer);
											break;
										case 8:
											printf("\t\t\tUNINITIALIZED Offset: %d\n", (*(VTIAux + positionVTI))->type_info.uninitialized_variable_info.offset);
											break;
										}
									}
								}
								else if ((*(smf + positionSMF))->frame_type == 255)
								{
									offsetImpressao += setPrintOffset(positionSMF, (*(smf + positionSMF))->map_frame_type.full_frame.offset_delta);
									printf("%d\t\tFULL_FRAME(%d),Offset: %d(+%d)\n", positionSMF, (*(smf + positionSMF))->frame_type, offsetImpressao, (*(smf + positionSMF))->map_frame_type.full_frame.offset_delta);
									Verification_type_info **VTIAux = (*(smf + positionSMF))->map_frame_type.full_frame.locals;
									printf("\t\t  Local verifications:\n");
									for (int positionVTI = 0; positionVTI < (*(smf + positionSMF))->map_frame_type.full_frame.num_locals; positionVTI++)
									{
										switch ((*(VTIAux + positionVTI))->tag)
										{
										case 0:
											printf("\t\t\tTOP\n");
											break;
										case 1:
											printf("\t\t\tINTEGER\n");
											break;
										case 2:
											printf("\t\t\tFLOAT\n");
											break;
										case 3:
											printf("\t\t\tLONG\n");
											break;
										case 4:
											printf("\t\t\tDOUBLE\n");
											break;
										case 5:
											printf("\t\t\tNULL\n");
											break;
										case 6:
											printf("\t\t\tUNINITIALIZED THIS\n");
											break;
										case 7:
											printPointer = decodeNINT(cf->constant_pool, (*(VTIAux + positionVTI))->type_info.object_variable_info.cp, NAME_INDEX);
											printf("\t\t\tOBJECT cp_info#%d <%s>\n", (*(VTIAux + positionVTI))->type_info.object_variable_info.cp, printPointer);
											break;
										case 8:
											printf("\t\t\tUNINITIALIZED Offset: %d\n", (*(VTIAux + positionVTI))->type_info.uninitialized_variable_info.offset);
											break;
										}
									}
									VTIAux = (*(smf + positionSMF))->map_frame_type.full_frame.stack;
									printf("\t\t  Stack verifications:\n");
									for (int positionVTI = 0; positionVTI < (*(smf + positionSMF))->map_frame_type.full_frame.num_stack_items; positionVTI++)
									{
										switch ((*(VTIAux + positionVTI))->tag)
										{
										case 0:
											printf("\t\t\tTOP\n");
											break;
										case 1:
											printf("\t\t\tINTEGER\n");
											break;
										case 2:
											printf("\t\t\tFLOAT\n");
											break;
										case 3:
											printf("\t\t\tLONG\n");
											break;
										case 4:
											printf("\t\t\tDOUBLE\n");
											break;
										case 5:
											printf("\t\t\tNULL\n");
											break;
										case 6:
											printf("\t\t\tUNINITIALIZED THIS\n");
											break;
										case 7:
											printPointer = decodeNINT(cf->constant_pool, (*(VTIAux + positionVTI))->type_info.object_variable_info.cp, NAME_INDEX);
											printf("\t\t\tOBJECT cp_info#%d <%s>\n", (*(VTIAux + positionVTI))->type_info.object_variable_info.cp, printPointer);
											break;
										case 8:
											printf("\t\t\tUNINITIALIZED Offset: %d\n", (*(VTIAux + positionVTI))->type_info.uninitialized_variable_info.offset);
											break;
										} 
									}	  
								}
							}
						}
					}
				}
			}

			else if (strcmp(printPointer, "Exceptions") == 0)
			{
				Exception_attribute *excpAux = (Exception_attribute *)(*(auxAttrCompleto + position))->info;
				int counterExcp = 0;
				char *exceptionIndexString;
				printf("Nr.\t\tException\t\t\tVerbose\n");
				for (u2 *indexExcp = excpAux->exception_info; indexExcp < excpAux->exception_info + excpAux->num_exceptions; indexExcp++)
				{
					exceptionIndexString = decodeNINT(cf->constant_pool, *indexExcp, NAME_INDEX);
					printf("%d\t\tcp_info#%d\t\t\t%s\n", counterExcp, *indexExcp, exceptionIndexString);
					counterExcp++;
				}
			}

			else if (strcmp(printPointer, "Signature") == 0)
			{
				Signature_attribute *sig = (Signature_attribute *)(*(auxAttrCompleto + position))->info;
				char *Signature_Index = decodeUTF8String(cf->constant_pool - 1 + sig->signature);
				printf("Signature index: cp_info#%d <%s>\n", sig->signature, Signature_Index);
			}
		}

	} // for - 1
}

void printAttrs(Classfile *cf)
{
	Attribute_info **auxAttributeClasse = cf->attributes;
	for (int position = 0; position < cf->attributes_count; position++)
	{
		printPointer = decodeUTF8String(cf->constant_pool + (*(auxAttributeClasse + position))->attribute_name - 1);
		printf("Attribute Name Index: cp_info#%d <%s>\n", (*(auxAttributeClasse + position))->attribute_name, printPointer);
		printf("Attribute Length: %d\n", (int)(*(auxAttributeClasse + position))->attribute_length);
		if (strcmp(printPointer, "SourceFile") == 0)
		{
			Source_file_attribute *SourceFile = ((Source_file_attribute *)((*(auxAttributeClasse + position))->info));
			printf("Source File Name Index: cp_info#%d <%s>\n", SourceFile->source_file, decodeUTF8String(cf->constant_pool + SourceFile->source_file - 1));
		}
		else if (strcmp(printPointer, "InnerClasses") == 0)
		{
			Inner_classes_attribute *innerC = ((Inner_classes_attribute *)((*(auxAttributeClasse + position))->info));
			printf("Nr.\t\tInner Class\t\t\tOuter Class\t\tInner Name\t\tAccess Flags\n");
			char *innerClassString, *outerClassString, *innerNameIndex, *accessFlagsInner;
			Classes **vetorClasses = innerC->classes_array;
			for (int positionInncerC = 0; positionInncerC < innerC->num_classes; positionInncerC++)
			{
				innerClassString = decodeNINT(cf->constant_pool, (*(vetorClasses + positionInncerC))->inner_class_info, NAME_INDEX);
				outerClassString = decodeNINT(cf->constant_pool, (*(vetorClasses + positionInncerC))->outer_class_info, NAME_INDEX);
				innerNameIndex = decodeUTF8String(cf->constant_pool - 1 + (*(vetorClasses + positionInncerC))->inner_name);
				accessFlagsInner = decodeAccessFlags((*(vetorClasses + positionInncerC))->inner_class_access_flags);
				printf("%d\t\tcp_info#%d\t\t\tcp_info#%d\t\tcp_info#%d\t\t0x%04x\n", positionInncerC, (*(vetorClasses + positionInncerC))->inner_class_info, (*(vetorClasses + positionInncerC))->outer_class_info, (*(vetorClasses + positionInncerC))->inner_name, (*(vetorClasses + positionInncerC))->inner_class_access_flags);
				printf("  \t\t%s\t\t%s\t\t%s\t\t\t%s\n", innerClassString, outerClassString, innerNameIndex, accessFlagsInner);
			}
		}
		else if (strcmp(printPointer, "Signature") == 0)
		{
			Signature_attribute *sig = (Signature_attribute *)((*(auxAttributeClasse + position))->info);
			char *Signature_Index = decodeUTF8String(cf->constant_pool - 1 + sig->signature);
			printf("Signature index: cp_info#%d <%s>\n", sig->signature, Signature_Index);
		}
	}
}

char *decode(Cp_info *cp, u2 sizeCP, u1 *code, u4 length, instrucao *instructions)
{
	u1 *aux;

	char *ret = (char *)malloc(1000 * sizeof(char));
	char *stringaux = (char *)malloc(100 * sizeof(char));
	u2 *aux2;
	
	char *stringargs;
	char *stringdecod; 
	strcpy(ret, "");

	for (aux = code; aux < code + length;)
	{
		int argindex = instructions[*aux].argindex;
		strcat(ret, instructions[*aux].inst_nome);
		switch (argindex)
		{
		case 0:
			strcat(ret, "\n");
			aux++;
			break;
		case 1:
			strcat(ret, " #");
			sprintf(stringaux, "%d", *(++aux));
			strcat(ret, stringaux);
			strcat(ret, " ");
			stringdecod = decodeInstructionOP(cp, *aux, sizeCP);
			strcat(ret, stringdecod);
			strcat(ret, "\n");
			aux++;
			break;

		case 2:
			aux2 = (u2 *)malloc(sizeof(u2));
			*aux2 = *(++aux) << 8;
			*aux2 |= *(++aux);

			stringargs = decodeInstructionOP(cp, *aux2, sizeCP);
			strcat(ret, " #");
			sprintf(stringaux, "%d", (int)*aux2);
			strcat(ret, stringaux);
			strcat(ret, " ");
			strcat(ret, stringargs);
			strcat(ret, "\n");
			aux++;
			break;

		default:
			strcat(ret, "undefined");
			aux++;
			break;
		}
	}

	free(stringargs);
	free(aux2);
	return (ret);
}

char *searchNameTag(u1 tag)
{
	char *nometag = malloc(40 * sizeof(char));
	switch (tag)
	{
	case CONSTANT_Class:
		strcpy(nometag, "CONSTANT_Class_Info");
		break;
	case CONSTANT_Field:
		strcpy(nometag, "CONSTANT_Field_Info");
		break;
	case CONSTANT_Method:
		strcpy(nometag, "CONSTANT_Method_Info");
		break;
	case CONSTANT_InterfaceMethod:
		strcpy(nometag, "CONSTANT_InterfaceMethod_Info");
		break;
	case CONSTANT_String:
		strcpy(nometag, "CONSTANT_String_Info");
		break;
	case CONSTANT_Integer:
		strcpy(nometag, "CONSTANT_Integer_Info");
		break;
	case CONSTANT_Float:
		strcpy(nometag, "CONSTANT_Float_Info");
		break;
	case CONSTANT_Long:
		strcpy(nometag, "CONSTANT_Long_Info");
		break;
	case CONSTANT_Double:
		strcpy(nometag, "CONSTANT_Double_Info");
		break;
	case CONSTANT_NameAndType:
		strcpy(nometag, "CONSTANT_NameAndType_Info");
		break;
	case CONSTANT_Utf8:
		strcpy(nometag, "CONSTANT_Utf8_Info");
		break;
	case CONSTANT_MethodHandle:
		strcpy(nometag, "CONSTANT_MethodHandle_Info");
		break;
	case CONSTANT_MethodType:
		strcpy(nometag, "CONSTANT_MethodType_Info");
		break;
	case CONSTANT_InvokeDynamic:
		strcpy(nometag, "CONSTANT_InvokeDynamic_Info");
		break;
	default:
		return NULL;
		break;
	}
	return (nometag);
}

char *decodeUTF8String(Cp_info *cp)
{
	char *decoded_string = (char *)malloc((cp->cp_union.Utf8.length + 1) * sizeof(char));

	for (u1 *aux = cp->cp_union.Utf8.bytes; aux < cp->cp_union.Utf8.bytes + cp->cp_union.Utf8.length; aux++)
	{
		*decoded_string = (char)*aux;
		decoded_string++;
	}
	*decoded_string = '\0';

	return (decoded_string);
}

char *decodeInstructionOP(Cp_info *cp, u2 index, u2 sizeCP)
{
	char *ret = malloc(100 * sizeof(char));
	char *stringNomeClasse;
	char *stringNomeMetodo;
	char *stringGeral;	
	char *pointer2pontos;
	Cp_info *cp_aux = cp + index - 1;

	if (index < sizeCP)
	{
		switch (cp_aux->tag)
		{
		case CONSTANT_Method:
			stringNomeClasse = decodeNINT(cp, cp_aux->cp_union.Method.class_name, NAME_INDEX);
			stringNomeMetodo = decodeNINT(cp, cp_aux->cp_union.Method.name_and_type, NAME_AND_TYPE);

			pointer2pontos = strchr(stringNomeMetodo, ':');
			*pointer2pontos = '\0';

			strcpy(ret, "<");
			strcat(ret, stringNomeClasse);
			strcat(ret, ".");
			strcat(ret, stringNomeMetodo);
			strcat(ret, ">");
			break;

		case CONSTANT_Field:

			stringNomeClasse = decodeNINT(cp, cp_aux->cp_union.Field.class_name, NAME_INDEX);
			stringGeral = decodeNINT(cp, cp_aux->cp_union.Field.name_and_type, NAME_AND_TYPE);

			pointer2pontos = strchr(stringGeral, ':');
			*pointer2pontos = '\0';

			strcpy(ret, "<");
			strcat(ret, stringNomeClasse);
			strcat(ret, ".");
			strcat(ret, stringGeral);
			strcat(ret, ">");
			break;

		case CONSTANT_String:

			stringGeral = decodeNINT(cp, cp_aux->cp_union.String.string, STRING_INDEX);

			strcpy(ret, "<");
			strcat(ret, stringGeral);
			strcat(ret, ">");
			break;
		default:
			strcpy(ret, "undefined");
			break;
		}
	}
	else
	{
		sprintf(ret, "%d", index);
	}
	return (ret);
}

char *decodeNINT(Cp_info *cp, u2 index, u1 tipo)
{
	char *ret = malloc(100 * sizeof(u1));

	Cp_info *aux;
	Cp_info *aux2;
	Cp_info *aux3;

	aux = cp + index - 1;

	switch (tipo)
	{
	case NAME_INDEX:
		aux2 = cp + (aux->cp_union.Class.name - 1);

		ret = decodeUTF8String(aux2);
		break;

	case NAME_AND_TYPE:
		aux2 = cp + (aux->cp_union.NameAndType.name - 1);
		aux3 = cp + (aux->cp_union.NameAndType.descriptor - 1);

		strcpy(ret, "");
		strcat(ret, decodeUTF8String(aux2));
		strcat(ret, ":");
		strcat(ret, decodeUTF8String(aux3));
		break;

	case STRING_INDEX:
	case CLASS_INDEX:
		ret = decodeUTF8String(aux);
		break;

	case NAME_AND_TYPE_INFO_NAME_INDEX:
		ret = decodeUTF8String(aux);
		break;

	case NAME_AND_TYPE_INFO_DESCRIPTOR_INDEX:
		ret = decodeUTF8String(aux);
		break;
	}

	return (ret);
}

char *decodeAccessFlags(u2 flag)
{

	char *ret = malloc(100 * sizeof(char));
	strcpy(ret, "");

	while (flag)
	{

		if (flag >= SYNTHETIC)
		{
			flag -= SYNTHETIC;
			strcat(ret, "SYNTHETIC;");
		}
		if (flag >= TRANSIENT)
		{
			flag -= TRANSIENT;
			strcat(ret, "TRANSIENT;");
		}
		if (flag >= VOLATILE)
		{
			flag -= VOLATILE;
			strcat(ret, "VOLATILE;");
		}

		if (flag >= FINAL)
		{
			flag -= FINAL;
			strcat(ret, "FINAL;");
		}

		if (flag >= STATIC)
		{
			flag -= STATIC;
			strcat(ret, "STATIC;");
		}

		if (flag >= PROTECTED)
		{
			flag -= PROTECTED;
			strcat(ret, "PROTECTED;");
		}

		if (flag >= PRIVATE)
		{
			flag -= PRIVATE;
			strcat(ret, "PRIVATE;");
		}

		if (flag >= PUBLIC)
		{
			flag -= PUBLIC;
			strcat(ret, "PUBLIC;");
		}
	}

	ret = sortFlags(ret);
	return (ret);
}

char *sortFlags(char *flagsOrdemInversa)
{
	const char s[2] = ";";
	char *flags = strtok(flagsOrdemInversa, s);
	char *old = (char *)malloc(100 * sizeof(char));
	char *new = (char *)malloc(100 * sizeof(char));

	int counter = 0;

	strcpy(new, "");
	strcpy(old, "");

	printf("--------------------------------------\n");
	while (flags != NULL)
	{

		if (counter == 0)
			strcpy(old, flags);

		if (counter > 0)
		{

			strcpy(new, flags);
			strcat(new, " ");
			strcat(new, old);
			strcpy(old, new);
			counter++;
		}
		else
			counter++;

		flags = strtok(NULL, s);
	}

	if (counter == 1)
	{
		free(new);
		return old;
	}
	else
	{
		free(old);
		return new;
	}
}

double decodeDoubleInfo(Cp_info *cp)
{
	uint64_t value = ((uint64_t)cp->cp_union.Double.hi_bytes << 32) | (uint64_t)cp->cp_union.Double.lo_bytes;
	int sign = ((value >> 63) == 0) ? 1 : -1;
	int exp = ((value >> 52) & 0x7ffL);
	long mant = (exp == 0) ? ((value & 0xfffffffffffffL) << 1) : ((value & 0xfffffffffffffL) | 0x10000000000000L);

	double ret = sign * mant * (pow(2, exp - 1075));
	return ret;
}

uint64_t decodeLongInfo(Cp_info *cp)
{
	return ((((uint64_t)cp->cp_union.Long.hi_bytes) << 32) | ((uint64_t)cp->cp_union.Long.lo_bytes));
}

int decodeIntegerInfo(Cp_info *cp)
{
	u4 value = cp->cp_union.Integer.bytes;
	return value;
}

float decodeFloatInfo(Cp_info *cp)
{
	u4 value = cp->cp_union.Float.bytes;
	float ret;
	int sign = ((value >> 31) == 0) ? 1 : -1;
	int exp = ((value >> 23) & 0xff);
	int mant = (exp == 0) ? (value & 0x7fffff) << 1 : (value & 0x7fffff) | 0x800000;
	ret = (sign) * (mant) * (pow(2, exp - 150));
	return ret;
}

int setPrintOffset(int position, u1 offset)
{
	if (position == 0)
		return offset;
	return (offset + 1);
}

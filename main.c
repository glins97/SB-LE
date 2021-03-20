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
#include <string.h> // Testar programa retirando aqui!
#include "classfile.h"
#include "leitor.h"
#include "exibidor.h"

int main(int argc, char *argv[])
{
  Classfile *class_file;
  char *nomeArquivo; // string que contem o nome do arquivo .class

  /* Verifica se o nome do arquivo .class foi passado na execução do programa.
   * Se foi, nomeArquivo contem essa string.
   */
  if (argc > 1)
  {
    nomeArquivo = (char *)malloc(strlen(argv[1]) * sizeof(char));
    strcpy(nomeArquivo, argv[1]);
  }
  else
  {
    printf("O nome do arquivo .class nao foi incluido.\nO programa sera encerrado.......\n");
    exit(0);
  }

  /* Cria estrutura do tipo class file*/
  class_file = (Classfile *)malloc(sizeof(struct classfile));

  /* Le o arquivo e armazena nas esttruturas correspondentes e retorna o pointer
   * para a estrutura do tipo classfile.
   */
  class_file = readArquivo(class_file, nomeArquivo);

  /* print as informacoes lidas do arquivo .class */
  printClassfile(class_file);

  return 0;
}

#include "funcionalidades.h"
#include <stdio.h>


int main() {
  printf("Iniciando o sistema BookED...\n");

  Funcionalidades *func = criaFuncionalidades();

  // pra saber se funcionou os arquivos de leitura de livro e leitor
  printf("Carregando leitores...\n");
  leArqLeitores(func, "leitores.txt");
  printf("Carregando livros...\n");
  leArqLivros(func, "livros.txt");

  // pra saber se funcionou até a rede de afinidades
  printf("Construindo rede de afinidades...\n");
  constroiAfinidades(func);

  // pra saber se funcionou até gerar as saidas
  printf("Processando comandos e gerando saida_resultado.txt...\n");
  ProcessaArqComandos(func, "comandos.txt", "saida_resultado.txt");

  // saber se tudo rodou e liberar a memoria
  printf("Finalizando e liberando memoria...\n");
  liberaFuncionalidades(func);

  // tudo rodou e acabou
  printf("Sistema BookED finalizado com sucesso!\n");

  return 0;
}
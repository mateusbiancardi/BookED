#include "funcionalidades.h"
#include <stdio.h>

// Para executar com args: ./main {nome_da_pasta}
int main(int argc, char *argv[]) {
  printf("Iniciando o sistema BookED...\n");

  Funcionalidades *func = criaFuncionalidades();

  // pra saber se funcionou os arquivos de leitura de livro e leitor
  if (argc < 2) {
    printf("Uso: %s <pasta_dos_arquivos>\n", argv[0]);
    return 1;
  }

  char path_leitores[256], path_livros[256], path_comandos[256],
      path_saida[256];
  snprintf(path_leitores, sizeof(path_leitores), "%s/leitores.txt", argv[1]);
  snprintf(path_livros, sizeof(path_livros), "%s/livros.txt", argv[1]);
  snprintf(path_comandos, sizeof(path_comandos), "%s/comandos.txt", argv[1]);
  snprintf(path_saida, sizeof(path_saida), "%s/saida_resultado.txt", argv[1]);

  printf("Carregando leitores...\n");
  leArqLeitores(func, path_leitores);
  printf("Carregando livros...\n");
  leArqLivros(func, path_livros);

  printf("Construindo rede de afinidades...\n");
  constroiAfinidades(func);

  printf("Processando comandos e gerando %s...\n", path_saida);
  ProcessaArqComandos(func, path_comandos, path_saida);

  // saber se tudo rodou e liberar a memoria
  printf("Finalizando e liberando memoria...\n");
  liberaFuncionalidades(func);

  // tudo rodou e acabou
  printf("Sistema BookED finalizado com sucesso!\n");

  return 0;
}
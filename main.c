#include "leitor.h"
#include "livro.h"

int main() {

  // const char *nomeArquivo = "livros.txt";

  // FILE *arquivo = fopen(nomeArquivo, "r");

  // // Pula a primeira linha do arquivo (o cabeçalho)
  // char linha_cabecalho[256];
  // fgets(linha_cabecalho, sizeof(linha_cabecalho), arquivo);

  // while (1) {
  //   Livro *livro_atual = inicializaLivro();

  //   int resultado = leLivroDoArquivo(livro_atual, arquivo);

  //   if (resultado == 5) {
  //     imprimeLivro(livro_atual);
  //   } else {
  //     liberaLivro(livro_atual);
  //     break;
  //   }
  // }

  char *nomeArquivo = "leitores.txt";
  FILE *arquivo = fopen(nomeArquivo, "r");

  // Pula a linha de cabeçalho
  char linha_cabecalho[256];
  fgets(linha_cabecalho, sizeof(linha_cabecalho), arquivo);

  while (1) {
    Leitor *leitor_atual = inicializaLeitor();

    int resultado = leLeitorDoArquivo(leitor_atual, arquivo);

    if (resultado > 0) {
      imprimeLeitor(leitor_atual);
    } else {
      liberaLeitor(leitor_atual);
      break;
    }
  }

  return 0;
}
#include "livro.h"
#include <stdio.h>
#include <stdlib.h>

struct livro {
  int id;
  char titulo[30];
  char autor[30];
  char genero[30];
  int ano;
};

Livro *inicializaLivro() {
  Livro *l = calloc(1, sizeof(Livro));

  l->id = 0;
  l->ano = 0;

  return l;
};

int leLivroDoArquivo(Livro *l, FILE *arquivo) {
  return fscanf(arquivo, "%d;%29[^;];%29[^;];%29[^;];%d\n", &l->id, l->titulo,
                l->autor, l->genero, &l->ano);
}

void liberaLivro(Livro *l) { free(l); };

void imprimeLivro(Livro *l) {
  if (l == NULL)
    return;
  printf("ID: %d\n", l->id);
  printf("Titulo: %s\n", l->titulo);
  printf("Autor: %s\n", l->autor);
  printf("Genero: %s\n", l->genero);
  printf("Ano: %d\n", l->ano);
}

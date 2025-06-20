/*
 *
 * Tad Livro
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#include "livro.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct livro {
  int id;
  char titulo[60];
  char autor[60];
  char genero[60];
  int ano;
};

Livro *inicializaLivro() {
  Livro *l = calloc(1, sizeof(Livro));

  l->id = 0;
  l->ano = 0;

  return l;
};

int leLivroDoArquivo(Livro *l, FILE *arquivo) {
  return fscanf(arquivo, "%d;%59[^;];%59[^;];%59[^;];%d\n", &l->id, l->titulo,
                l->autor, l->genero, &l->ano);
}

int getIdLivro(Livro *l) { return l->id; }
char *getTitulo(Livro *l) { return l->titulo; }
char *getAutor(Livro *l) { return l->autor; }
char *getGenero(Livro *l) { return l->genero; }
int getAno(Livro *l) { return l->ano; }

// Funções envolvendo lista ----------------------------------------------
int comparaIdLivro(void *idPtr, void *livroPtr) {
  int id = *(int *)idPtr;
  Livro *livro = (Livro *)livroPtr;
  return id == livro->id;
}

Livro *getLivroListaById(Lista *lista, int id) {
  return (Livro *)getItemLista(lista, &id, comparaIdLivro);
}

Livro *removeLivroLista(Lista *lista, int id) {
  Livro *livro = removeItemLista(lista, &id, comparaIdLivro);
  return livro;
}

int verificaLivroListaExiste(Lista *l, int id) {
  return verificaItemListaExiste(l, &id, comparaIdLivro);
}

void insereLivroLista(Lista *lista, Livro *livro) {
  insereItemLista(lista, livro);
}
// ------------------------------------------------------------------------

void liberaLivro(Livro *l) { free(l); };

// Função de debug
void imprimeLivro(Livro *l) {
  if (l == NULL)
    return;
  printf("ID: %d\n", l->id);
  printf("Titulo: %s\n", l->titulo);
  printf("Autor: %s\n", l->autor);
  printf("Genero: %s\n", l->genero);
  printf("Ano: %d\n", l->ano);
}

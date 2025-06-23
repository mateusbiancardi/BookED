/*
 *
 * Tad Leitor
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#include "leitor.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct leitor {
  int id;
  char nome[MAX_TAM_NOME];
  int nPreferencias;
  char **preferencias;
  Lista *livrosLidos;
  Lista *livrosDesejados;
  // Recomendação recebida
  Lista *livrosRecomendados;
  Lista *afinidades;
};

Leitor *inicializaLeitor() {
  Leitor *l = calloc(1, sizeof(Leitor));

  l->id = 0;
  l->nPreferencias = 0;
  l->preferencias = NULL;
  l->livrosLidos = criaLista();
  l->livrosDesejados = criaLista();
  l->livrosRecomendados = criaLista();
  l->afinidades = criaLista();

  return l;
};

int leLeitorDoArquivo(Leitor *l, FILE *arquivo) {
  char buffer_linha[256]; // Buffer para ler o resto da linha
  int result =
      fscanf(arquivo, "%d;%99[^;];%d;", &l->id, l->nome, &l->nPreferencias);

  l->preferencias = malloc(l->nPreferencias * sizeof(char *));

  if (fgets(buffer_linha, sizeof(buffer_linha), arquivo) == NULL) {

    free(l->preferencias);
    l->preferencias = NULL;
    return 0;
  }

  char *token = strtok(buffer_linha, ";\n\r");

  for (int i = 0; i < l->nPreferencias; i++) {
    l->preferencias[i] = strdup(token);
    token = strtok(NULL, ";\n\r");
  }

  return 1;
}

int getIdLeitor(Leitor *l) { return l->id; };
char *getNome(Leitor *l) { return l->nome; }
char **getPreferencias(Leitor *l) { return l->preferencias; }

// Funções envolvendo lista ----------------------------------------------
int comparaIdLeitor(void *idPtr, void *leitorPtr) {
  int id = *(int *)idPtr;
  Leitor *leitor = (Leitor *)leitorPtr;
  return id == leitor->id;
}

Leitor *getLeitorListaById(Lista *lista, int id) {
  return (Leitor *)getItemLista(lista, &id, comparaIdLeitor);
}

int verificaLeitorListaExiste(Lista *l, int id) {
  return verificaItemListaExiste(l, &id, comparaIdLeitor);
}

Leitor *removeLeitorLista(Lista *lista, int id) {
  Leitor *leitor = removeItemLista(lista, &id, comparaIdLeitor);
  return leitor;
}

void insereLeitorLista(Lista *lista, Leitor *leitor) {
  insereItemLista(lista, leitor);
}

Lista *getListaLivrosLidos(Leitor *l) { return l->livrosLidos; };

Lista *getListaLivrosDesejados(Leitor *l) { return l->livrosDesejados; };

Lista *getListaLivrosRecomendados(Leitor *l) { return l->livrosRecomendados; };

Lista *getListaAfinidades(Leitor *l) { return l->afinidades; }
// ------------------------------------------------------------------------

void liberaLeitor(Leitor *l) {
  if (l == NULL)
    return;

  for (int i = 0; i < l->nPreferencias; i++) {
    free(l->preferencias[i]);
  }
  free(l->preferencias);
  // Passando NULL para não liberar os livros (os livros são liberados em outro
  // lugar)
  liberaLista(l->livrosLidos, NULL);
  liberaLista(l->livrosDesejados, NULL);
  liberaLista(l->livrosRecomendados, NULL);
  liberaLista(l->afinidades, NULL);
  free(l);
};

// Função de debug
void imprimeLeitor(Leitor *l) {
  if (l == NULL)
    return;

  printf("ID: %d\n", l->id);
  printf("Nome: %s\n", l->nome);
  printf("Número de Preferências: %d\n", l->nPreferencias);
  for (int i = 0; i < l->nPreferencias; i++) {
    printf("Preferência %d: %s\n", i + 1, l->preferencias[i]);
  }
}

int getNPreferencia(Leitor *l) { return l->nPreferencias; }
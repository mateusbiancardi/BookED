#include "leitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct leitor {
  int id;
  char nome[MAX_TAM_NOME];
  int nPreferencias;
  char **prefencias;
};

Leitor *inicializaLeitor() {
  Leitor *l = calloc(1, sizeof(Leitor));

  l->id = 0;
  l->nPreferencias = 0;
  l->prefencias = NULL;

  return l;
};

int leLeitorDoArquivo(Leitor *l, FILE *arquivo) {
  char buffer_linha[256]; // Buffer para ler o resto da linha
  int result =
      fscanf(arquivo, "%d;%99[^;];%d;", &l->id, l->nome, &l->nPreferencias);

  l->prefencias = malloc(l->nPreferencias * sizeof(char *));

  if (fgets(buffer_linha, sizeof(buffer_linha), arquivo) == NULL) {

    free(l->prefencias);
    l->prefencias = NULL;
    return 0;
  }

  char *token = strtok(buffer_linha, ";\n\r");

  for (int i = 0; i < l->nPreferencias; i++) {
    l->prefencias[i] = strdup(token);
    token = strtok(NULL, ";\n\r");
  }

  return 1;
}

void liberaLeitor(Leitor *l) {
  if (l == NULL)
    return;

  for (int i = 0; i < l->nPreferencias; i++) {
    free(l->prefencias[i]);
  }
  free(l->prefencias);
  free(l);
};

void imprimeLeitor(Leitor *l) {
  if (l == NULL)
    return;

  printf("ID: %d\n", l->id);
  printf("Nome: %s\n", l->nome);
  printf("Número de Preferências: %d\n", l->nPreferencias);
  for (int i = 0; i < l->nPreferencias; i++) {
    printf("Preferência %d: %s\n", i + 1, l->prefencias[i]);
  }
}
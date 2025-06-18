/*
 *
 * Tad Funcionalidades
 * Lê e processa os arquivos, implementando as funcinalidades do bookED
 * Autores: Mateus Biancardi e Rafaela Capovilla
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"
#include "lista.h"

struct funcionalidades {
  Lista *leitores;
  Lista *livros;
};

Funcionalidades *criaFuncionalidades(){
    Funcionalidades *func = (Funcionalidades *) calloc (1, sizeof(Funcionalidades));
    func->leitores = criaLista();
    func->livros = criaLista();

    return func;
}

void leArqLeitores(Funcionalidades *func, const char *path){
    FILE *f = fopen(path, "r");
    if (!f) {
        perror("Erro ao abrir leitores.txt");
        exit(1);
    }

    //serve pra ignorar o cabeçalho do arquivo
    fscanf(f, "%*[^\n]\n");

    // enquanto não for o fim do arquivo, le os dados de leitores do arquivo e adiciona no sistema. A cada rodada do loop, ele aloca memória pra
    // um novo 'Leitor' e tenta preencher com os dados de uma linha do arquivo. Se a leitura for bem-sucedida, o leitor preenchido é inserido
    // na lista principal do sistema. Caso a leitura falhe, a memória alocada para o leitor que não pode ser utilizado é liberada
    while (!feof(f)) {
        Leitor *l = inicializaLeitor();
        if (leLeitorDoArquivo(l, f)) {
            insereLeitorLista(func->leitores, l);
        } 
        else {
            liberaLeitor(l); //libera se a leitura falhar
        }
  }
  fclose(f);
}

void leArqLivros(Funcionalidades *func, const char *path){
    FILE *f = fopen(path, "r");
    if (!f) {
        perror("Erro ao abrir livros.txt");
        exit(1);
    }

    fscanf(f, "%*[^\n]\n");

    while (!feof(f)) {
        Livro *l = inicializaLivro();
        if (leLivroDoArquivo(l, f) == 5) { //fscanf retorna o num de itens lidos
            insereLivroLista(func->livros, l);
        }
        else {
            liberaLivro(l);
        }
  }
  fclose(f);
}
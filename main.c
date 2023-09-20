#include "cofo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int buscar(void *item, void *nome, void *idade, void *nota) {
    Aluno *aluno = (Aluno *)item;
    int comparacao = strcmp((char *)nome, aluno->nome);
    if (comparacao == 0) {
        if (aluno->idade == *(int *)idade && aluno->nota == *(float *)nota) {
            return TRUE;
        }
    }
    return FALSE;
}

int main() {
    int opcao, max_itens, idade;
    Aluno *a, *b;
    gCofo *cofo;
    char nome[30];
    float nota;
    Aluno *aluno = NULL;

    do {
        printf("------MENU------\n");
        printf("Escolha uma opção:\n");
        printf("1 - Criar uma coleção\n");
        printf("2 - Inserir um elemento na coleção\n");
        printf("3 - Listar os elementos da coleção\n");
        printf("4 - Consultar um dos elementos da coleção\n");
        printf("5 - Remover um elemento da coleção\n");
        printf("6 - Esvaziar a coleção\n");
        printf("0 - Fechar o programa\n");

        scanf("%d", &opcao);

        switch (opcao) {

            case 0:
                printf("Até mais!\n");
                break;

            case 1:
                printf("Quantos elementos será a capacidade do cofo?\n");
                scanf("%d", &max_itens);
                cofo = criarCofo(max_itens);
                if (cofo != NULL) {
                    printf("Cofo criado com sucesso!\n");
                } else {
                    printf("Erro ao criar cofo.\n");
                }
                break;

            case 2:
                a = (Aluno *)malloc(sizeof(Aluno));
                printf("Para inserir o Aluno na coleção, por favor, digite o nome:\n");
                scanf(" %29[^\n]", a->nome);
                printf("Idade:\n");
                scanf("%d", &(a->idade));
                printf("Nota:\n");
                scanf("%f", &(a->nota));

                void *elemento = (void *)a;

                int inseriu = inserirNoCofo(cofo, elemento);
                if (inseriu == TRUE) {
                    printf("Aluno inserido com sucesso!\n");
                } else {
                    printf("Erro ao inserir Aluno.\n");
                }
                break;

            case 3:
                printf("Os elementos do cofo são:\n");
                void **imprimir = listarElementos(cofo);

                for (int i = 0; i < cofo->num_itens; i++) {
                    b = (Aluno *)imprimir[i];
                    printf("Aluno %d:\n", i);
                    printf("Nome: %s\n", b->nome);
                    printf("Idade: %d\n", b->idade);
                    printf("Nota: %.2f\n", b->nota);
                }
                break;

            case 4:
                printf("Para consultar um elemento da coleção, por favor, insira:\n");
                printf("Nome:\n");
                scanf(" %29[^\n]", nome);
                printf("Idade:\n");
                scanf("%d", &idade);
                printf("Nota:\n");
                scanf("%f", &nota);

                aluno = (Aluno *)consultarElemento(cofo, nome, idade, nota);

                if (aluno != NULL) {
                    printf("Aluno encontrado:\n");
                    printf("Nome: %s\n", aluno->nome);
                    printf("Idade: %d\n", aluno->idade);
                    printf("Nota: %.2f\n", aluno->nota);
                } else {
                    printf("Aluno não encontrado.\n");
                }
                break;

            case 5:
                printf("Para remover um elemento da coleção, por favor, insira:\n");
                printf("Nome:\n");
                scanf(" %29[^\n]", nome);
                printf("Idade:\n");
                scanf("%d", &idade);
                printf("Nota:\n");
                scanf("%f", &nota);

                void *nome1 = (void *)nome;
                void *idade1 = (void *)&idade;
                void *nota1 = (void *)&nota;

                aluno = (Aluno *)removerDoCofo(cofo, nome1, idade1, nota1, &buscar);

                if (aluno != NULL) {
                    printf("Aluno removido:\n");
                    printf("Nome: %s\n", aluno->nome);
                    printf("Idade: %d\n", aluno->idade);
                    printf("Nota: %.2f\n", aluno->nota);
                } else {
                    printf("Aluno não encontrado ou erro ao remover.\n");
                }
                break;

            case 6:
                if (esvaziarCofo(cofo) == TRUE) {
                    printf("Cofo esvaziado com sucesso!\n");
                } else {
                    printf("Erro ao esvaziar cofo.\n");
                }
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    if (cofo != NULL) {
        destruirCofo(cofo);
    }

    return 0;
}

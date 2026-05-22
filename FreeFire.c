#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Estrutura do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor da mochila
Item mochila[MAX_ITENS];

int totalItens = 0;

// ================= FUNÇÃO PAUSAR =================
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar(); // limpa buffer
    getchar(); // espera ENTER
}

// ================= LISTAR ITENS =================
void listarItens() {

    printf("\n----------------------------------\n");
    printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
    printf("----------------------------------\n");

    if (totalItens == 0) {

        printf("Mochila vazia!\n");

    } else {

        for (int i = 0; i < totalItens; i++) {

            printf("\nItem %d\n", i + 1);
            printf("Nome      : %s\n", mochila[i].nome);
            printf("Tipo      : %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
        }
    }

    printf("----------------------------------\n");
}

// ================= INSERIR ITEM =================
void inserirItem() {

    if (totalItens >= MAX_ITENS) {

        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;

    printf("\nItem adicionado com sucesso!\n");

    listarItens();
}

// ================= BUSCA SEQUENCIAL =================
int buscarItem(char nome[]) {

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }

    return -1;
}

// ================= REMOVER ITEM =================
void removerItem() {

    char nome[30];

    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]", nome);

    int posicao = buscarItem(nome);

    if (posicao == -1) {

        printf("\nItem não encontrado!\n");
        return;
    }

    // Organiza vetor após remoção
    for (int i = posicao; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;

    printf("\nItem removido com sucesso!\n");

    listarItens();
}

// ================= BUSCAR ITEM =================
void procurarItem() {

    char nomeBusca[30];

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    int posicao = buscarItem(nomeBusca);

    if (posicao == -1) {

        printf("\nItem não encontrado!\n");

    } else {

        printf("\n===== ITEM ENCONTRADO =====\n");
        printf("Nome      : %s\n", mochila[posicao].nome);
        printf("Tipo      : %s\n", mochila[posicao].tipo);
        printf("Quantidade: %d\n", mochila[posicao].quantidade);
        printf("===========================\n");
    }
}

// ================= MENU PRINCIPAL =================
int main() {

    int opcao;

    do {

        system("cls"); // Windows
        // system("clear"); // Linux/Mac

        printf("==================================\n");
        printf("  MOCHILA DE SOBREVIVENCIA\n");
        printf("==================================\n");

        printf("\nItens na Mochila: %d/%d\n", totalItens, MAX_ITENS);

        printf("\n1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");

        printf("\n----------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                inserirItem();
                pausar();
                break;

            case 2:

                removerItem();
                pausar();
                break;

            case 3:

                listarItens();
                pausar();
                break;

            case 4:

                procurarItem();
                pausar();
                break;

            case 0:

                printf("\nSaindo do sistema...\n");
                break;

            default:

                printf("\nOpcao invalida!\n");
                pausar();
        }

    } while(opcao != 0);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Define o comando de limpar tela de acordo com o Sistema Operacional
#ifdef _WIN32
    #define LIMPAR_TELA "cls"
#else
    #define LIMPAR_TELA "clear"
#endif

// ================= 1. CRIAÇÃO DAS STRUCTS =================

// Estrutura base do Item (usada em ambas as versões)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura do Nó para a Lista Encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ================= VARIÁVEIS GLOBAIS =================
// Estrutura para o Vetor
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Estrutura para a Lista Encadeada (Ponteiro para o início)
No* inicioLista = NULL;
int totalItensLista = 0;

// Contadores de comparações solicitados no requisito
int compSequencial = 0;
int compBinaria = 0;

// ================= FUNÇÃO PAUSAR =================
void pausar() {
    printf("\nPressione ENTER para continuar...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer residual
    getchar(); // Espera o ENTER do usuário
}

// =========================================================
//         SISTEMA DE MOCHILA 1: VETOR (LISTA SEQUENCIAL)
// =========================================================

void listarItensVetor() {
    printf("\n--- MOCHILA (VETOR): %d/%d ---\n", totalItensVetor, MAX_ITENS);

    if (totalItensVetor == 0) {
        printf("Mochila (Vetor) vazia!\n");
    } else {
        for (int i = 0; i < totalItensVetor; i++) {
            printf("\nItem %d [Vetor]\n", i + 1);
            printf("Nome      : %s\n", mochilaVetor[i].nome);
            printf("Tipo      : %s\n", mochilaVetor[i].tipo);
            printf("Quantidade: %d\n", mochilaVetor[i].quantidade);
        }
    }
    printf("----------------------------------\n");
}

void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\nMochila (Vetor) cheia!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %29[^\n]", mochilaVetor[totalItensVetor].nome);

    printf("Digite o tipo do item: ");
    scanf(" %19[^\n]", mochilaVetor[totalItensVetor].tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);

    totalItensVetor++;
    printf("\nItem adicionado ao Vetor com sucesso!\n");
    listarItensVetor();
}

// Busca Sequencial no Vetor (Como você tinha feito, mas somando as comparações)
int buscarSequencialVetor(char nome[]) {
    compSequencial = 0; // Reinicia o contador para esta busca
    
    for (int i = 0; i < totalItensVetor; i++) {
        compSequencial++; // Computa a comparação do if
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i; // Retorna o índice onde encontrou
        }
    }
    return -1; // Não encontrado
}

void removerItemVetor() {
    char nome[30];
    printf("\nDigite o nome do item para remover do Vetor: ");
    scanf(" %29[^\n]", nome);

    int posicao = buscarSequencialVetor(nome);

    if (posicao == -1) {
        printf("\nItem não encontrado no Vetor!\n");
        return;
    }

    // Desloca os elementos para reorganizar o vetor (mantendo o seu padrão)
    for (int i = posicao; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    totalItensVetor--;
    printf("\nItem removido do Vetor com sucesso!\n");
    listarItensVetor();
}

// Ordenação do Vetor usando Bubble Sort (Requisito 4)
void ordenarVetor() {
    if (totalItensVetor <= 1) {
        printf("\nItens insuficientes para ordenar.\n");
        return;
    }

    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            // Se o item j for alfabeticamente maior que o item j+1, troca de lugar
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = temp;
            }
        }
    }
    printf("\nMochila (Vetor) ordenada por nome com sucesso!\n");
    listarItensVetor();
}

// Busca Binária no Vetor (Requisito 5 e 6)
void buscarBinariaVetor() {
    char nomeBusca[30];
    compBinaria = 0; // Reinicia o contador da busca binária

    if (totalItensVetor == 0) {
        printf("\nMochila (Vetor) vazia!\n");
        return;
    }

    printf("\n[ATENÇÃO] A busca binária exige o vetor ordenado.");
    printf("\nDigite o nome do item para a Busca Binária: ");
    scanf(" %29[^\n]", nomeBusca);

    int inicio = 0;
    int fim = totalItensVetor - 1;
    int encontrado = -1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        compBinaria++; // Registra a comparação do strcmp abaixo

        int resultadoCmp = strcmp(mochilaVetor[meio].nome, nomeBusca);

        if (resultadoCmp == 0) {
            encontrado = meio;
            break; // Encontrou!
        } 
        else if (resultadoCmp < 0) {
            inicio = meio + 1; // Procura na metade da direita
        } 
        else {
            fim = meio - 1; // Procura na metade da esquerda
        }
    }

    if (encontrado == -1) {
        printf("\nItem não encontrado via Busca Binária!\n");
    } else {
        printf("\n===== ITEM ENCONTRADO (BUSCA BINÁRIA) =====\n");
        printf("Nome      : %s\n", mochilaVetor[encontrado].nome);
        printf("Tipo      : %s\n", mochilaVetor[encontrado].tipo);
        printf("Quantidade: %d\n", mochilaVetor[encontrado].quantidade);
        printf("============================================\n");
    }
    printf("Comparações realizadas na Busca Binária: %d\n", compBinaria);
}


// =========================================================
//         SISTEMA DE MOCHILA 2: LISTA ENCADEADA (DINÂMICA)
// =========================================================

void listarItensLista() {
    printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
    
    if (inicioLista == NULL) {
        printf("Mochila (Lista) vazia!\n");
    } else {
        No* atual = inicioLista;
        int i = 1;
        while (atual != NULL) {
            printf("\nItem %d [Lista]\n", i++);
            printf("Nome      : %s\n", atual->dados.nome);
            printf("Tipo      : %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            atual = atual->proximo;
        }
    }
    printf("----------------------------------\n");
}

void inserirItemLista() {
    // Aloca memória dinamicamente para o novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro de falta de memória no sistema!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %29[^\n]", novoNo->dados.nome);

    printf("Digite o tipo do item: ");
    scanf(" %19[^\n]", novoNo->dados.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);

    // Insere no início da lista encadeada (Operação O(1) - rápida)
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    
    totalItensLista++;
    printf("\nItem adicionado à Lista Encadeada com sucesso!\n");
    listarItensLista();
}

void buscarItemLista() {
    char nomeBusca[30];
    compSequencial = 0; // Reinicia o contador para a busca na lista

    if (inicioLista == NULL) {
        printf("\nMochila (Lista) vazia!\n");
        return;
    }

    printf("\nDigite o nome do item para buscar na Lista: ");
    scanf(" %29[^\n]", nomeBusca);

    No* atual = inicioLista;
    int encontrado = 0;

    while (atual != NULL) {
        compSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n===== ITEM ENCONTRADO (LISTA) =====\n");
            printf("Nome      : %s\n", atual->dados.nome);
            printf("Tipo      : %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("====================================\n");
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("\nItem não encontrado na Lista Encadeada!\n");
    }
    printf("Comparações realizadas na Lista (Sequencial): %d\n", compSequencial);
}

void removerItemLista() {
    char nome[30];
    if (inicioLista == NULL) {
        printf("\nMochila (Lista) vazia!\n");
        return;
    }

    printf("\nDigite o nome do item para remover da Lista: ");
    scanf(" %29[^\n]", nome);

    No* atual = inicioLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == -1 || atual == NULL) {
        printf("\nItem não encontrado na Lista!\n");
        return;
    }

    // Se o item a ser removido for o primeiro da lista
    if (anterior == NULL) {
        inicioLista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual); // Libera a memória alocada dinamicamente
    totalItensLista--;
    printf("\nItem removido da Lista Encadeada com sucesso!\n");
    listarItensLista();
}


// =========================================================
//            MENUS DE INTERFACE COM O JOGADOR
// =========================================================

void menuVetor() {
    int opcao;
    do {
        system(LIMPAR_TELA);
        printf("==================================\n");
        printf("   MODO VETOR (LISTA SEQUENCIAL)   \n");
        printf("==================================\n");
        printf("Itens no Vetor: %d/%d\n\n", totalItensVetor, MAX_ITENS);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens da Mochila\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("5. Ordenar Mochila (Bubble Sort)\n");
        printf("6. Buscar Item (Busca Binária)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { opcao = -1; }

        switch(opcao) {
            case 1: inserirItemVetor(); pausar(); break;
            case 2: removerItemVetor(); pausar(); break;
            case 3: listarItensVetor(); pausar(); break;
            case 4: {
                char nome[30];
                printf("\nDigite o nome do item: ");
                scanf(" %29[^\n]", nome);
                int pos = buscarSequencialVetor(nome);
                if(pos != -1) {
                    printf("\n===== ITEM ENCONTRADO =====\n");
                    printf("Nome      : %s\n", mochilaVetor[pos].nome);
                    printf("Quantidade: %d\n", mochilaVetor[pos].quantidade);
                } else { printf("\nItem nao encontrado.\n"); }
                printf("Comparações (Sequencial Vetor): %d\n", compSequencial);
                pausar(); break;
            }
            case 5: ordenarVetor(); pausar(); break;
            case 6: buscarBinariaVetor(); pausar(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); pausar();
        }
    } while(opcao != 0);
}

void menuLista() {
    int opcao;
    do {
        system(LIMPAR_TELA);
        printf("==================================\n");
        printf("  MODO LISTA (ESTRUTURA DINÂMICA) \n");
        printf("==================================\n");
        printf("Itens na Lista Encadeada: %d\n\n", totalItensLista);
        printf("1. Adicionar Item (Loot Dinâmico)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens da Mochila\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) { opcao = -1; }

        switch(opcao) {
            case 1: inserirItemLista(); pausar(); break;
            case 2: removerItemLista(); pausar(); break;
            case 3: listarItensLista(); pausar(); break;
            case 4: buscarItemLista(); pausar(); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n"); pausar();
        }
    } while(opcao != 0);
}

int main() {
    int opcao;

    do {
        system(LIMPAR_TELA);
        printf("==================================\n");
        printf("    MOCHILA DE SOBREVIVENCIA     \n");
        printf("==================================\n");
        printf("Escolha a Estrutura de Dados:\n\n");
        printf("1. Trabalhar com Vetor (Lista Sequencial)\n");
        printf("2. Trabalhar com Lista Encadeada (Dinâmica)\n");
        printf("0. Sair do Jogo\n");
        printf("----------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
        }

        switch(opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("\nSaindo do sistema de sobrevivência...\n"); break;
            default: printf("\nOpcao invalida!\n"); pausar();
        }

    } while(opcao != 0);

    // Liberar a memória da lista antes de fechar o programa (Boas práticas de C)
    No* atual = inicioLista;
    while (atual != NULL) {
        No* prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    return 0;
}
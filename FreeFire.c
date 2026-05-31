#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Estrutura que representa um componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;

long comparacoes = 0;
int ordenadoPorNome = 0;

// Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Pausa o programa
void pausar() {
    printf("\\nPressione ENTER para continuar...");
    limparBuffer();
    getchar();
}

// Exibe os componentes formatados
void mostrarComponentes(Componente v[], int n) {
    printf("\\n---------------------------------------------------------\\n");
    printf("%-20s %-15s %-10s\\n", "NOME", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------------------\\n");

    for(int i = 0; i < n; i++) {
        printf("%-20s %-15s %-10d\\n",
               v[i].nome,
               v[i].tipo,
               v[i].prioridade);
    }

    printf("---------------------------------------------------------\\n");
}

// Cadastro de componentes
void adicionarComponente() {

    if(totalComponentes >= MAX_COMPONENTES) {
        printf("\\nLimite de componentes atingido!\\n");
        return;
    }

    Componente novo;

    printf("\\nNome: ");
    limparBuffer();
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\\n")] = 0;

    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\\n")] = 0;

    printf("Prioridade (1-10): ");
    scanf("%d", &novo.prioridade);

    torre[totalComponentes++] = novo;
    ordenadoPorNome = 0;

    printf("\\nComponente adicionado com sucesso!\\n");
}

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n) {

    comparacoes = 0;

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {

            comparacoes++;

            if(strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }

    ordenadoPorNome = 1;
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n) {

    comparacoes = 0;

    for(int i = 1; i < n; i++) {

        Componente chave = v[i];
        int j = i - 1;

        while(j >= 0) {

            comparacoes++;

            if(strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }

        v[j + 1] = chave;
    }

    ordenadoPorNome = 0;
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n) {

    comparacoes = 0;

    for(int i = 0; i < n - 1; i++) {

        int menor = i;

        for(int j = i + 1; j < n; j++) {

            comparacoes++;

            if(v[j].prioridade < v[menor].prioridade)
                menor = j;
        }

        Componente aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }

    ordenadoPorNome = 0;
}

// Função obrigatória para medir tempo
void medirTempo(void (*algoritmo)(Componente[], int),
                Componente vetor[],
                int tamanho) {

    clock_t inicio = clock();

    algoritmo(vetor, tamanho);

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\\nComparacoes: %ld\\n", comparacoes);
    printf("Tempo: %.8f segundos\\n", tempo);
}

// Busca binária por nome
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {

    int inicio = 0;
    int fim = n - 1;

    while(inicio <= fim) {

        int meio = (inicio + fim) / 2;

        int cmp = strcmp(v[meio].nome, nome);

        if(cmp == 0)
            return meio;

        if(cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

// Busca componente-chave
void buscarComponenteChave() {

    if(!ordenadoPorNome) {
        printf("\\nPrimeiro execute Bubble Sort por nome.\\n");
        return;
    }

    char nome[30];

    printf("\\nDigite o componente-chave: ");
    limparBuffer();

    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\\n")] = 0;

    int pos = buscaBinariaPorNome(torre, totalComponentes, nome);

    if(pos == -1) {
        printf("\\nComponente nao encontrado.\\n");
    } else {
        printf("\\nCOMPONENTE ENCONTRADO!\\n");
        printf("Nome: %s\\n", torre[pos].nome);
        printf("Tipo: %s\\n", torre[pos].tipo);
        printf("Prioridade: %d\\n", torre[pos].prioridade);
    }
}

// Montagem final da torre
void ativarTorre() {

    printf("\\n===== PLANO DE FUGA =====\\n");

    mostrarComponentes(torre, totalComponentes);

    if(!ordenadoPorNome) {
        printf("\\nA torre exige componentes organizados por nome.\\n");
        return;
    }

    int pos = buscaBinariaPorNome(torre, totalComponentes, "Chip Central");

    if(pos != -1) {
        printf("\\nTORRE ATIVADA COM SUCESSO!\\n");
        printf("Componente-chave 'Chip Central' encontrado.\\n");
    } else {
        printf("\\nFALHA NA ATIVACAO!\\n");
        printf("Componente-chave 'Chip Central' nao encontrado.\\n");
    }
}

int main() {

    int opcao;

    do {

        printf("\\n========================================\\n");
        printf(" PLANO DE FUGA - CODIGO DA ILHA\\n");
        printf("========================================\\n");
        printf("Componentes cadastrados: %d/%d\\n\\n",
               totalComponentes,
               MAX_COMPONENTES);

        printf("1. Adicionar Componente\\n");
        printf("2. Listar Componentes\\n");
        printf("3. Bubble Sort por Nome\\n");
        printf("4. Insertion Sort por Tipo\\n");
        printf("5. Selection Sort por Prioridade\\n");
        printf("6. Busca Binaria por Nome\\n");
        printf("0. Ativar Torre de Fuga e Sair\\n");

        printf("\\nOpcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                adicionarComponente();
                pausar();
                break;

            case 2:
                mostrarComponentes(torre, totalComponentes);
                pausar();
                break;

            case 3:
                printf("\\nOrdenacao Bubble Sort por Nome\\n");
                medirTempo(bubbleSortNome, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                pausar();
                break;

            case 4:
                printf("\\nOrdenacao Insertion Sort por Tipo\\n");
                medirTempo(insertionSortTipo, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                pausar();
                break;

            case 5:
                printf("\\nOrdenacao Selection Sort por Prioridade\\n");
                medirTempo(selectionSortPrioridade, torre, totalComponentes);
                mostrarComponentes(torre, totalComponentes);
                pausar();
                break;

            case 6:
                buscarComponenteChave();
                pausar();
                break;

            case 0:
                ativarTorre();
                break;

            default:
                printf("\\nOpcao invalida.\\n");
        }

    } while(opcao != 0);

    return 0;
}
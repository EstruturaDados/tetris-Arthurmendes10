#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5   // Tamanho fixo da fila circular

// -------------------------------
// STRUCT DA PEÇA
// -------------------------------
typedef struct {
    char nome;  // Tipo da peça: I, O, T, L
    int id;     // Identificador único
} Peca;

// -------------------------------
// STRUCT DA FILA CIRCULAR
// -------------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// -------------------------------
// PROTÓTIPOS DAS FUNÇÕES
// -------------------------------
void inicializarFila(Fila *f);
int enqueue(Fila *f, Peca p);
int dequeue(Fila *f, Peca *removida);
void exibirFila(Fila *f);
Peca gerarPeca();

// -------------------------------
// VARIÁVEL GLOBAL PARA IDs
// -------------------------------
int proxID = 0;

// -------------------------------
// FUNÇÃO PRINCIPAL
// -------------------------------
int main() {
    Fila fila;
    int opcao;

    srand(time(NULL)); // Semente para gerar peças aleatórias
    inicializarFila(&fila);

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    printf("\n=== Fila de Peças do Tetris Stack ===\n");

    do {
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca removida;
            if (dequeue(&fila, &removida)) {
                printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
            } else {
                printf("\nA fila está vazia! Não há peça para jogar.\n");
            }

        } else if (opcao == 2) {
            if (enqueue(&fila, gerarPeca())) {
                printf("\nNova peça inserida!\n");
            } else {
                printf("\nA fila está cheia! Não é possível inserir nova peça.\n");
            }
        }

    } while (opcao != 0);

    printf("\nEncerrando sistema...\n");
    return 0;
}

// -------------------------------
// INICIALIZA A FILA
// -------------------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// -------------------------------
// INSERE UMA PEÇA (ENQUEUE)
// -------------------------------
int enqueue(Fila *f, Peca p) {
    if (f->quantidade == TAM_FILA) {
        return 0; // fila cheia
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;

    return 1;
}

// -------------------------------
// REMOVE UMA PEÇA (DEQUEUE)
// -------------------------------
int dequeue(Fila *f, Peca *removida) {
    if (f->quantidade == 0) {
        return 0; // fila vazia
    }

    *removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    return 1;
}

// -------------------------------
// EXIBE O ESTADO ATUAL DA FILA
// -------------------------------
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");

    if (f->quantidade == 0) {
        printf("[VAZIA]\n");
        return;
    }

    int i = f->inicio;

    for (int count = 0; count < f->quantidade; count++) {
        Peca p = f->itens[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\n");
}

// -------------------------------
// GERA UMA PEÇA ALEATÓRIA
// -------------------------------
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I', 'O', 'T', 'L'};

    p.nome = tipos[rand() % 4];
    p.id = proxID++;

    return p;
}

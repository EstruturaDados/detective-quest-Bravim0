#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó (sala) da árvore binária
struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
};

// Função para criar uma sala dinamicamente
struct Sala* criarSala(const char *nome) {
    struct Sala *nova = (struct Sala*) malloc(sizeof(struct Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Função para explorar a mansão
void explorarSalas(struct Sala *atual) {
    char opcao;

    while (atual != NULL) {
        printf("\n📍 Voce está em: %s\n", atual->nome);

        // Verifica se é nó-folha
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("🔎 Fim do caminho! Voce chegou ao final da exploração.\n");
            return;
        }

        printf("Para onde deseja ir?\n");
        printf("  e → esquerda\n");
        printf("  d → direita\n");
        printf("  s → sair\n");
        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("⚠️ Nao existe caminho à esquerda!\n");

        } else if (opcao == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("⚠️ Nao existe caminho à direita!\n");

        } else if (opcao == 's') {
            printf("\n👋 Voce decidiu encerrar a exploração.\n");
            return;

        } else {
            printf("❌ Opcao inválida! Tente novamente.\n");
        }
    }
}

int main() {

    // 🔨 Montagem da árvore (fixa)

    // Nó raiz – Hall de Entrada
    struct Sala *hall = criarSala("Hall de Entrada");

    // Nível 1
    hall->esquerda = criarSala("Corredor Oeste");
    hall->direita  = criarSala("Corredor Leste");

    // Nível 2 à esquerda
    hall->esquerda->esquerda = criarSala("Biblioteca");
    hall->esquerda->direita  = criarSala("Sala de Música");

    // Nível 2 à direita
    hall->direita->esquerda  = criarSala("Sala de Jantar");
    hall->direita->direita   = criarSala("Jardim Interno");

    // 🚪 Iniciar exploração da mansão
    // =================================
    printf("===== 🕵️ Detective Quest – Mansao Misteriosa =====\n");
    printf("Explore a mansao seguindo os caminhos da árvore binária!\n");

    explorarSalas(hall);

    printf("\nFim da aventura!\n");
    return 0;
}

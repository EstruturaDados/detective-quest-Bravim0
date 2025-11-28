#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==============================
//     ÁRVORE BINÁRIA DE SALAS
// ==============================

struct Sala {
    char nome[50];
    char pista[50];   // pista opcional encontrada nesta sala
    struct Sala *esquerda;
    struct Sala *direita;
};

// Função para criar salas
struct Sala* criarSala(const char *nome, const char *pista) {
    struct Sala *nova = (struct Sala*) malloc(sizeof(struct Sala));
    strcpy(nova->nome, nome);

    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        strcpy(nova->pista, "");

    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// ==============================
//     ÁRVORE DE BUSCA (BST)
// ==============================

struct BST {
    char info[50];
    struct BST *esq;
    struct BST *dir;
};

// Inserir nova pista na BST
struct BST* inserir(struct BST *raiz, const char *valor) {
    if (raiz == NULL) {
        struct BST *nova = (struct BST*) malloc(sizeof(struct BST));
        strcpy(nova->info, valor);
        nova->esq = NULL;
        nova->dir = NULL;
        return nova;
    }

    if (strcmp(valor, raiz->info) < 0)
        raiz->esq = inserir(raiz->esq, valor);
    else if (strcmp(valor, raiz->info) > 0)
        raiz->dir = inserir(raiz->dir, valor);

    return raiz;
}

// Listar pistas em ordem alfabética
void emOrdem(struct BST *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf(" - %s\n", raiz->info);
    emOrdem(raiz->dir);
}

// ==============================
//     EXPLORAÇÃO DA MANSÃO
// ==============================

void explorarSalas(struct Sala *atual, struct BST **pistas) {
    char opcao;

    while (atual != NULL) {
        printf("\n📍 Você está em: %s\n", atual->nome);

        // Se existir pista neste cômodo, adicionar à BST
        if (strlen(atual->pista) > 0) {
            printf("🔎 Você encontrou uma pista: \"%s\"\n", atual->pista);
            *pistas = inserir(*pistas, atual->pista);
        }

        // Nó-folha → fim do caminho
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("🛑 Fim do caminho nesta direção!\n");
            return;
        }

        printf("\nPara onde deseja ir?\n");
        printf("  e → esquerda\n");
        printf("  d → direita\n");
        printf("  s → sair da exploração\n");
        printf("Opção: ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("⚠️ Caminho inexistente!\n");

        } else if (opcao == 'd') {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("⚠️ Caminho inexistente!\n");

        } else if (opcao == 's') {
            printf("\n👋 Encerrando exploração.\n");
            return;
        } else {
            printf("❌ Opção inválida!\n");
        }
    }
}

// ==============================
//     PROGRAMA PRINCIPAL
// ==============================

int main() {
    struct Sala *hall = criarSala("Hall de Entrada", "");

    // Salas do 1º nível
    hall->esquerda = criarSala("Corredor Oeste", "Pegadas suspeitas");
    hall->direita  = criarSala("Corredor Leste", "");

    // Salas do 2º nível
    hall->esquerda->esquerda = criarSala("Biblioteca", "Livro arrancado da prateleira");
    hall->esquerda->direita  = criarSala("Sala de Música", "");
    hall->direita->esquerda  = criarSala("Sala de Jantar", "Copo quebrado");
    hall->direita->direita   = criarSala("Jardim Interno", "");

    // Arvore de pistas BST
    struct BST *pistas = NULL;

    printf("===== 🕵️‍♂️ Detective Quest – Nível Aventureiro =====\n");
    printf("Explore a mansão e colete pistas!\n");

    explorarSalas(hall, &pistas);

    // Exibir pistas coletadas
    printf("\n📜 Pistas coletadas (ordem alfabética):\n");
    if (pistas == NULL) {
        printf("Nenhuma pista encontrada.\n");
    } else {
        emOrdem(pistas);
    }

    printf("\nFim da investigação!\n");
    return 0;
}

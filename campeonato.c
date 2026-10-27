/*
 * Gerenciador de Campeonato de Futebol
 * Disciplina: Algoritmos e Pensamento Computacional
 * VERSÃO INICIAL comentarios para ajudar na implementação */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>   /* necessário para configurar os acentos no console */
#endif

/* ---------- 1. CONSTANTES ---------- */
#define MAX_TIMES    10   
#define MIN_TIMES    4    
#define MAX_PARTIDAS 45   
#define TAM_NOME     50   

/* ---------- 2. STRUCTS ---------- */
typedef struct {
    int  codigo;
    char nome[TAM_NOME];
    int  pontos;
    int  vitorias;
    int  empates;
    int  derrotas;
    int  golsFeitos;
    int  golsSofridos;
} Time;

typedef struct {
    int codMandante;
    int codVisitante;
    int golsMandante;
    int golsVisitante;
} Partida;

/* ---------- 3. DADOS GLOBAIS ---------- */
Time    times[MAX_TIMES];
int     qtdTimes = 0;

Partida partidas[MAX_PARTIDAS];
int     qtdPartidas = 0;   /* será usado ao implementar o registro de partidas */

/* ---------- 4. FUNÇÕES AUXILIARES DE ENTRADA ---------- */

/* Lê uma linha de texto e remove o '\n' do final */
void lerTexto(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

/* Lê um número inteiro; se o usuário digitar letras, retorna -1 */
int lerInteiro(void) {
    char linha[50];
    int valor;
    fgets(linha, sizeof(linha), stdin);
    if (sscanf(linha, "%d", &valor) != 1) {
        return -1;
    }
    return valor;
}

/* Compara dois textos ignorando maiúsculas/minúsculas (1 = iguais, 0 = diferentes) */
int nomesIguais(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

/* ---------- 5. FUNÇÕES DE TIMES ---------- */

/* Retorna a posição do time no vetor pelo nome, ou -1 se não existir */
int buscarTimePorNome(const char *nome) {
    for (int i = 0; i < qtdTimes; i++) {
        if (nomesIguais(times[i].nome, nome)) {
            return i;
        }
    }
    return -1;
}


void cadastrarTime(void) {
    char nome[TAM_NOME];

    printf("\n--- CADASTRAR TIME ---\n");

    if (qtdTimes >= MAX_TIMES) {
        printf("Limite de %d times atingido.\n", MAX_TIMES);
        return;
    }

    printf("Nome do time: ");
    lerTexto(nome, TAM_NOME);

    if (strlen(nome) == 0) {
        printf("O nome não pode ficar vazio.\n");
        return;
    }
    if (buscarTimePorNome(nome) != -1) {
        printf("Já existe um time com esse nome.\n");
        return;
    }

    /* Guarda o novo time com tudo zerado e código gerado automaticamente */
    Time novo;
    novo.codigo       = qtdTimes + 1;
    strcpy(novo.nome, nome);
    novo.pontos       = 0;
    novo.vitorias     = 0;
    novo.empates      = 0;
    novo.derrotas     = 0;
    novo.golsFeitos   = 0;
    novo.golsSofridos = 0;

    times[qtdTimes] = novo;
    qtdTimes++;

    printf("Time \"%s\" cadastrado com o código %d.\n", novo.nome, novo.codigo);
}

/* RF02 */
void listarTimes(void) {
    printf("\n--- TIMES CADASTRADOS ---\n");

    if (qtdTimes == 0) {
        printf("Nenhum time cadastrado ainda.\n");
        return;
    }

    for (int i = 0; i < qtdTimes; i++) {
        printf("%2d - %s\n", times[i].codigo, times[i].nome);
    }
    printf("Total: %d time(s)\n", qtdTimes);
}

/* ---------- 6. MENU (RF14) ---------- */

void exibirMenu(void) {
    printf("\n==================================\n");
    printf("   GERENCIADOR DE CAMPEONATO\n");
    printf("==================================\n");
    printf("1 - Cadastrar time\n");
    printf("2 - Listar times\n");
    printf("3 - Registrar partida\n");
    printf("4 - Listar partidas\n");
    printf("5 - Ver classificação\n");
    printf("6 - Consultar estatísticas de um time\n");
    printf("0 - Sair\n");
    printf("==================================\n");
    printf("Escolha uma opção: ");
}

int main(void) {
    int opcao;

#ifdef _WIN32
    SetConsoleOutputCP(65001);   /* saída em UTF-8 (acentos corretos) */
    SetConsoleCP(65001);         /* entrada em UTF-8 */
#endif

    do {
        exibirMenu();
        opcao = lerInteiro();

        switch (opcao) {
            case 1: cadastrarTime(); break;
            case 2: listarTimes();   break;
            case 0: printf("\nEncerrando o programa. Até logo!\n"); break;
            default: printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
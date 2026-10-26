/*Camila Cardoso dos Reis Silva GRR20263633 Felipe Augusto Klass GRR20260844*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


#define TAM_BUFFER 256

/*Varáveis Globais*/

int maxErros = 6, totalVitorias, totalDerrotas;

/*Protótipos das funções*/

void limpaBuffer();
char *lerString();
char *lerPalavra();
void *alocar(size_t size);
void *alocarZerado(int qtd, size_t size);
int sorteio(int max, char sorteadas[], int *qtdSorteadas);
void iniciaJogo(char *palavra, char *dica);
void paraMaiusculo(char *s);
void limpaTela();


void main() {
    /*Variaveis Locais Main*/
    int qtdPalavras = 0, i, indSorteado = 0, qtdSorteadas = 0;
    char **palavras, **dicas;
    char *sorteadas;
    char resposta;
    
    do {

        limpaTela();

        printf("------------------------------------------------\n");
        printf("\n Bem-vindo ao jogo da Forca!\n");
        printf("\n------------------------------------------------\n");
        
        do { 
            printf("\n Escolha a quantidade de palavras que deseja inserir para jogar forca:");
            printf("\n -> ");

            if (scanf("%d", &qtdPalavras) != 1) {
                qtdPalavras = 0; // Define qtdPalavras como 0 para entrar no loop de validação
            }

            limpaBuffer();
    
            if (qtdPalavras <= 0) {
                printf("\n !!! Quantidade de palavras invalida! Digite um valor maior que 0 !!!\n");
            }
    
        } while (qtdPalavras <= 0); /*Validação*/
        
        /*Aloca memória necessaria para as palavras e dicas*/
        palavras = alocar(qtdPalavras * sizeof(char*));
        dicas = alocar(qtdPalavras * sizeof(char*));
        
        for (i = 0; i < qtdPalavras; i++) {
    
            printf("\n Digite a palavra (sem acento) %d:", i + 1);
            printf("\n -> ");
            palavras[i] = lerPalavra();
    
            printf("\n Digite a dica %d:", i + 1);
            printf("\n -> ");
            dicas[i] = lerString();
        }
    
        limpaTela();
        printf("\n Agora vamos jogar!\n");
    
        srand(time(NULL)); /*Gerar números aleatórios baseado no tempo do sistema*/
        
        sorteadas = alocarZerado(qtdPalavras, sizeof(char));
        qtdSorteadas = 0;
    
        /*Loop Partidas*/
        for (i = 0; i < qtdPalavras; i++) {
            indSorteado = sorteio(qtdPalavras, sorteadas, &qtdSorteadas);
            
            iniciaJogo(palavras[indSorteado], dicas[indSorteado]);
        }
    
        limpaTela();
    
        printf("\n------------------------------------------------\n");
        printf("\n Total de partidas jogadas: %d\n", totalVitorias + totalDerrotas);
        printf("\n Total de vitorias: %d\n", totalVitorias);
        printf("\n Total de derrotas: %d\n", totalDerrotas);
        printf("\n------------------------------------------------\n");
        
        /*Libera a memória alocada para as palavras e dicas*/
        for (i = 0; i < qtdPalavras; i++) {
            free(palavras[i]);
            free(dicas[i]);
        }
        free(palavras);
        free(dicas);
        free(sorteadas);

        printf("\n Deseja jogar novamente? (S - Sim / Qualquer outro caractere - Nao): ");
        printf("\n -> ");
        scanf(" %c", &resposta);
        limpaBuffer();
    } while (resposta == 'S' || resposta == 's'); /*Loop do jogo*/
}

/*Implementação das funções*/

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /*Limpa o buffer de entrada*/
    }
}

/*Validação de alocação de memória*/
void *alocar(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memoria.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/*Validação de alocação de memória zerada*/
void *alocarZerado(int qtd, size_t size) {
    void *ptr = calloc(qtd, size);
    if (ptr == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memoria.\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

char *lerString() {
    char buffer[TAM_BUFFER];
    char *s;

    do {

        fgets(buffer, TAM_BUFFER, stdin);
        if (buffer[strlen(buffer) - 1] != '\n') {
            limpaBuffer(); /*Limpa o buffer se a entrada for maior que TAM_BUFFER*/
        }
        buffer[strcspn(buffer, "\n")] = '\0'; /*Remove o caractere de nova linha*/

        if (strlen(buffer) == 0) {
            printf("\n !!! Entrada invalida! Digite uma string com pelo menos 1 caractere !!!\n");
            printf("\n -> ");
        }

    } while (strlen(buffer) == 0); /*Validação*/

    s = alocar((strlen(buffer) + 1) * sizeof(char));
    strcpy(s, buffer);

    return s;
}

char *lerPalavra() {
    char *p;
    int i, valida = 1;

    p = lerString();
    paraMaiusculo(p);

    for (i = 0 ; p[i] != '\0'; i++) {
        if ((p[i] <'A' || p[i] > 'Z') && (p[i] != '-' && p[i] != ' ')) {
            valida = 0;
            break;
        }
    }
    if (!valida) {
        printf("\n !!! Palavra invalida! Digite uma palavra sem acento e com apenas letras de 'A' a 'Z', espaco ou '-' !!!\n");
        printf("\n -> ");
        free(p);
        return lerPalavra();
    }
    return p;
}

int sorteio(int max, char sorteadas[], int *qtdSorteadas) {
    int i, indice;

    if (*qtdSorteadas == max) {
        for (i = 0; i < max; i++) {
            sorteadas[i] = 0;
        }
        *qtdSorteadas = 0;
    } /*Zera a variável de palavras sorteadas*/

    do {
        indice = rand() % max;
    } while (sorteadas[indice] == 1); /*Sorteia denovo caso a palavra já tenha sido sorteada*/

    sorteadas[indice] = 1; /*Marca a palavra como sorteada*/
    (*qtdSorteadas)++;
    return indice;
}

/*Partida*/
void iniciaJogo(char *palavra, char *dica) {
    int erros = 0, acertos = 0, i, carcEspecial = 0, resultado = 0;
    int tamanhoPalavra = strlen(palavra);
    char *palavraOculta = alocar((tamanhoPalavra + 1) * sizeof(char));
    char chutes[26] = {0}; /*Array para armazenar as letras chutadas*/
    char letra;

    
    for (i = 0; i < tamanhoPalavra; i++) {
        if (palavra[i] == ' ') {
            palavraOculta[i] = ' ';
            carcEspecial++;
        } else if (palavra[i] == '-'){
            palavraOculta[i] = '-';
            carcEspecial++;
        }
        else {
            palavraOculta[i] = '_';
        }
    } /*Cria a palavra oculta*/
    palavraOculta[tamanhoPalavra] = '\0';

    do{
        limpaTela();

        if (resultado == 1) {
            printf("\nLetra correta! Erros: %d/%d\n", erros, maxErros);
        } else if (resultado == 2) {
            printf("\nLetra incorreta! Erros: %d/%d\n", erros, maxErros);
        }

        printf("\nDica: %s\n", dica);
        printf("\nPalavra: %s\n", palavraOculta);
        printf("\nLetras chutadas: ");
        for (i = 0; i < 26; i++) {
            if (chutes[i] != 0) {
                printf("%c ", chutes[i]);
            }
        } /*Mostra as letras chutadas*/
    
        do {
            printf("\n\nDigite uma letra: ");
            printf("\n-> ");
            scanf("%c", &letra);
            limpaBuffer();
            letra = toupper(letra);
            if (letra < 'A' || letra > 'Z') {
                printf("\n!!! Letra invalida! Digite uma letra de 'A' a 'Z' !!!\n");
            }
            else if(chutes[letra - 'A'] != 0) {
                printf("\n!!! Letra ja chutada! Digite outra letra !!!\n");
                letra = 0;
            }
        } while (letra < 'A' || letra > 'Z'); /*Validação da letra digitada*/

        chutes[letra - 'A'] = letra; /*Marca a letra como chutada*/

        int letraEncontrada = 0;

        for (i = 0; i < tamanhoPalavra; i++) {
            if(palavra[i] == letra) {
                palavraOculta[i] = letra;
                letraEncontrada = 1;
                acertos++;
            } /*Procura a letra na palavra e marca acertos*/
        }

        if (!letraEncontrada) {
            erros++;
            resultado = 2;
        } else {
            resultado = 1;
        }

    } while (acertos < (tamanhoPalavra - carcEspecial) && erros < maxErros); /*Loop da partida, remove caracteres especiais da contagem de letras*/

    if (acertos == (tamanhoPalavra - carcEspecial)) {
        limpaTela();
        printf("\nParabens! Voce acertou a palavra: %s\n", palavra);
        totalVitorias++;
    }
    else {
        limpaTela();
        printf("\nVoce perdeu! A palavra era: %s\n", palavra);
        totalDerrotas++;
    }

    printf("\nPressione Enter para continuar...");
    limpaBuffer();

    /*Libera a memória alocada para a palavra oculta*/
    free(palavraOculta);
}

/*Transforma uma string em maiúscula*/
void paraMaiusculo(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++)
        s[i] = toupper(s[i]);
}

/*Limpa a tela*/
void limpaTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdbool.h>
# include <windows.h>
# include <time.h>
# define ESPERAR(ms) Sleep(ms)

char tabuleiro[3][3];
char *tabuleiro_ptr=&tabuleiro[0][0];

int c; /* Variavel de apoio para limpar buffer de memoria do scan*/

int nivel = 0;

char jog1, jog2;

int conta_jogadas = 0;

 int menu(){
    int opcao;
    printf("\n\t-------- # JOGO DA VELHA # --------\n\n");
    printf("\t- Selecione o modo de jogo:\n\t1 - Contra computador;\n\t2 - Contra usuario;\n\t3 - Sair;\n\tOP: ");
    scanf("%d", &opcao);
    while ((c = getchar()) != '\n' && c != EOF);

    while ((opcao != 1 && opcao != 2 && opcao != 3)){
        printf("\n\tOpcao invalida, digite novamente: ");
        scanf("%d", &opcao);
        while ((c = getchar()) != '\n' && c != EOF);
    }

    switch(opcao){
        case 1:
            printf("\n\tSelecione a dificuldade do adversario:\n\t1 - Facil;\n\t2 - Medio;\n\t3 - Dificil;\n\tOP: ");
            scanf("%d", &nivel);
            while ((c = getchar()) != '\n' && c != EOF);
            while ((nivel != 1 && nivel != 2 && nivel != 3)){
                printf("\n\tOpcao invalida, digite novamente: ");
                scanf("%d", &nivel);
                while ((c = getchar()) != '\n' && c != EOF);
            }
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
    }
 }

void inicializa_velha(){
    int i, j;
    for (i=0;  i < 3; i++){
        for (j=0; j < 3; j++)
            tabuleiro[i][j]= ' ';
            tabuleiro_ptr++;
    }
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("%c", tabuleiro[i][j]);
        }
    }
}

void escolha_simb(char *jogador1, char *jogador2){
    char simb, simbUpper;
    printf("\n\tJogador 1, escolha o simbolo (X/O): ");
    scanf(" %c", &simb);
    while ((c = getchar()) != '\n' && c != EOF);
    simbUpper = toupper(simb);

    while (simbUpper != 'X' && simbUpper != 'O'){
        printf("\n\tSimbolo invalido, digite novamente: ");
        scanf(" %c", &simb);
        while ((c = getchar()) != '\n' && c != EOF);
        simbUpper = toupper(simb);
    }

    if (simbUpper == 'X'){
        printf("\n\tJogador 1 - X;\n\tJogador 2 - O;");
        *jogador1 = 'X';
        *jogador2 = 'O';
    } else {
        printf("\n\tJogador 1 - O;\n\tJogador 2 - X;");
        *jogador1 = 'O';
        *jogador2 = 'X';
    }

    printf("\n\n\tPressione qualquer tecla para iniciar o jogo...");
    getchar();
}

int verifica_ganhador(char jog){
    int i, j, igual = 0;
    /*VERIFICA SE O JOGADOR VENCEU PELA LINHA*/
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (tabuleiro[i][j] == jog){
                igual += 1;
            }
        }
        if (igual == 3){
            return 1;
        } else {
            igual = 0;
        }
    }
    /*VERIFICA SE O JOGADOR VENCEU PELA COLUNA*/
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (tabuleiro[j][i] == jog){
                igual += 1;
            }
        }
        if (igual == 3){
            return 1;
        } else {
            igual = 0;
        }
    }

    /*VERIFICA SE O JOGADOR VENCEU PELA DIAGONAL*/
    /*DIAGONAL PRINCIPAL*/
    for (i = 0; i < 3; i++){
        if (tabuleiro[i][i] == jog) {
            igual +=1;
        }
    }
    if (igual == 3){
        return 1;
    } else {
        igual = 0;
    }

    /*DIAGONAL SEGUNDARIA*/
    for (i = 0; i < 3; i++){
        if (tabuleiro[i][3 - i - 1] == jog) {
            igual +=1;
        }
    }
    if (igual == 3) {
        return 1;
    } else {
        igual = 0;
    }

    return 0;
}

int jogada_usuario(int lin, int col){

    if ((tabuleiro[lin-1][col-1] == ' ') && ((lin <= 3 && lin >= 1) && (col <= 3 && col >= 1))){
        return 0;
    } else {
        if ((lin > 3 || lin < 1) || (col > 3 || col < 1)){
            return 1;
        } else {
            return 2;
        }
    }
}

void printa_tabuleiro(char jog){
    system("cls");
    printf("\n\t-------- # JOGO DA VELHA # --------\n");
    printf("\n\tTURNO DE: %c\n", jog);
    printf("\n         1      2      3\n");
    printf("\n\t %c  |   %c  |  %c\t  1\n\t-----------------\n\t %c  |   %c  |  %c\t  2\n\t-----------------\n\t %c  |\t%c  |  %c\t  3",
    tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2],
    tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2],
    tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
    printf("\n\n");
}

int faz_jogada(char jog){
    int lin, col, resp, venceu, i, j;
    conta_jogadas = 0;
    printa_tabuleiro(jog);

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (tabuleiro[i][j] == 'X' || tabuleiro[i][j] == 'O'){
                conta_jogadas += 1;
            }
        }
    }
    if (conta_jogadas == 9){
        printa_tabuleiro(jog);
        printf("\n\tEMPATE!");
        printf("\n\n\tPressione qualquer tecla para continuar...");
        getchar();
        return 0;
    }

    printf("\n\tSelecione a linha: ");
    scanf("%d", &lin);
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\n\tSelecione a coluna: ");
    scanf("%d", &col);
    while ((c = getchar()) != '\n' && c != EOF);

    resp = jogada_usuario(lin, col);

    while (resp != 0) {
        if (resp == 1) {
            printa_tabuleiro(jog);
            printf("\n\tPosicao invalida!");
            printf("\n\tSelecione a linha: ");
            scanf("%d", &lin);
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\tSelecione a coluna: ");
            scanf("%d", &col);
            while ((c = getchar()) != '\n' && c != EOF);
            resp = jogada_usuario(lin, col);
        } else {
            printa_tabuleiro(jog);
            printf("\n\tPosicao ja preenchida!");
            printf("\n\tSelecione a linha: ");
            scanf("%d", &lin);
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\tSelecione a coluna: ");
            scanf("%d", &col);
            while ((c = getchar()) != '\n' && c != EOF);
            resp = jogada_usuario(lin, col);
        }
    }

    if (resp == 0){
        conta_jogadas = 0;
        tabuleiro[lin-1][col-1] = jog;
        printa_tabuleiro(jog);
        printf("\n\tJogada realizada!");

    }
    ESPERAR(1000);
    venceu = verifica_ganhador(jog);
    if (venceu == 1) {
        printa_tabuleiro(jog);
        printf("\n\t%c VENCEU!", jog);
        printf("\n\n\tPressione qualquer tecla para voltar ao menu...");
        getchar();
        return 1;
    } else {
        return 2;
    }
}

int computador_facil(char jog){
    int resp, venceu;
    int i = 0, j = 0;
    srand(time(NULL));
    i = rand() % (3 - 1 + 1) + 1;
    j = rand() % (3 - 1 + 1) + 1;

    printf("\n\t%d\n\t%d", i, j);

    resp = jogada_usuario(i, j);

    while (resp != 0) {
        if (resp == 1) {
            i = rand() % (3 - 1 + 1) + 1;
            j = rand() % (3 - 1 + 1) + 1;
            resp = jogada_usuario(i, j);
        } else {
            i = rand() % (3 - 1 + 1) + 1;
            j = rand() % (3 - 1 + 1) + 1;
            resp = jogada_usuario(i, j);
        }
    }
    if (resp == 0) {
        tabuleiro[i-1][j-1] = jog;
        printa_tabuleiro(jog);
        printf("\n\tJogada realizada!");
        ESPERAR(1000);
    }

    venceu = verifica_ganhador(jog);
    if (venceu == 1) {
        printa_tabuleiro(jog);
        printf("\n\tCOMPUTADOR VENCEU!", jog);
        printf("\n\n\tPressione qualquer tecla para voltar ao menu...");
        getchar();
        return 1;
    } else {
        return 2;
    }
}

int conta_ameacas(char marca, int *lin, int *col){
    int k, m, l, c, qtd, vl, vc, total = 0;

    for (k = 0; k < 8; k++){
        qtd = 0;
        vl = -1;
        vc = -1;
        for (m = 0; m < 3; m++){
            if (k < 3)       { l = k; c = m; }       /* linhas      */
            else if (k < 6)  { l = m; c = k - 3; }   /* colunas     */
            else if (k == 6) { l = m; c = m; }       /* diag. princ.*/
            else             { l = m; c = 2 - m; }   /* diag. sec.  */

            if (tabuleiro[l][c] == marca){
                qtd++;
            } else if (tabuleiro[l][c] == ' '){
                vl = l;
                vc = c;
            }
        }
        if (qtd == 2 && vl != -1){
            if (total == 0){
                *lin = vl;
                *col = vc;
            }
            total++;
        }
    }
    return total;
}

/* Descobre a peca do adversario (qualquer peca diferente de 'jog' e de ' ').
   Devolve ' ' se ainda nao existe nenhuma. */
char acha_adversario(char jog){
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (tabuleiro[i][j] != jog && tabuleiro[i][j] != ' '){
                return tabuleiro[i][j];
            }
        }
    }
    return ' ';
}

/* Faz a jogada, mostra o tabuleiro e verifica se o computador venceu.
   Retorna 1 se o computador venceu e 2 se o jogo continua. */
int realiza_jogada(int linha, int coluna, char jog){
    int venceu;

    tabuleiro[linha][coluna] = jog;
    printa_tabuleiro(jog);
    venceu = verifica_ganhador(jog);
    printf("\n\tJogada realizada!");
    ESPERAR(1000);
    if (venceu == 1) {
        printa_tabuleiro(jog);
        printf("\n\tCOMPUTADOR VENCEU!");
        printf("\n\n\tPressione ENTER para voltar ao menu...");
        getchar();
        return 1;
    }
    return 2;
}

int computador_dificil(char jog){
    int i = 0, j = 0, igual = 0, resp, venceu, espaco_preenchido = 0, linha, coluna, quantidade, linha_vazia, coluna_vazia;
    int sorteio;
    char adv;

    /* descobre a peca do adversario e conta quantas ele ja jogou */
    adv = acha_adversario(jog);
    if (adv != ' '){
        for (i = 0; i < 3; i++){
            for (j = 0; j < 3; j++){
                if (tabuleiro[i][j] == adv){
                    igual += 1;
                }
            }
        }
    }

/*------------------------------- 1) ATAQUE: VENCER SE POSSIVEL -------------------------------*/

    /* tem que vir ANTES da defesa: se o computador pode ganhar, ganha em vez de bloquear */
    if (conta_ameacas(jog, &linha_vazia, &coluna_vazia) > 0){
        return realiza_jogada(linha_vazia, coluna_vazia, jog);
    }

/*------------------------------- 2) DEFESA: BLOQUEAR O ADVERSARIO -------------------------------*/

    if (igual >= 2 && conta_ameacas(adv, &linha_vazia, &coluna_vazia) > 0){
        return realiza_jogada(linha_vazia, coluna_vazia, jog);
    }

/*------------------------------- 3) CRIAR UM FORK (DUAS AMEACAS DE UMA VEZ) -------------------------------*/

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if (tabuleiro[i][j] == ' '){
                tabuleiro[i][j] = jog;
                quantidade = conta_ameacas(jog, &linha_vazia, &coluna_vazia);
                tabuleiro[i][j] = ' ';
                if (quantidade >= 2){
                    return realiza_jogada(i, j, jog);
                }
            }
        }
    }

/*------------------------------- 4) IMPEDIR O FORK DO ADVERSARIO -------------------------------*/

    if (igual >= 2){
        /* conta quantas casas dariam um fork para o adversario */
        quantidade = 0;
        for (i = 0; i < 3; i++){
            for (j = 0; j < 3; j++){
                if (tabuleiro[i][j] == ' '){
                    tabuleiro[i][j] = adv;
                    if (conta_ameacas(adv, &linha_vazia, &coluna_vazia) >= 2){
                        quantidade++;
                        linha = i;
                        coluna = j;
                    }
                    tabuleiro[i][j] = ' ';
                }
            }
        }

        /* so existe um fork possivel: ocupa essa casa */
        if (quantidade == 1){
            return realiza_jogada(linha, coluna, jog);
        }

        /* varios forks possiveis (ex.: adversario em cantos opostos):
           joga criando uma ameaca, forcando o adversario a bloquear sem que
           o bloqueio dele crie um fork. */
        if (quantidade >= 2){
            for (i = 0; i < 3; i++){
                for (j = 0; j < 3; j++){
                    if (tabuleiro[i][j] == ' '){
                        tabuleiro[i][j] = jog;
                        if (conta_ameacas(jog, &linha_vazia, &coluna_vazia) > 0){
                            /* o adversario sera obrigado a jogar em (linha_vazia, coluna_vazia) */
                            tabuleiro[linha_vazia][coluna_vazia] = adv;
                            quantidade = conta_ameacas(adv, &linha, &coluna);
                            tabuleiro[linha_vazia][coluna_vazia] = ' ';
                            tabuleiro[i][j] = ' ';
                            if (quantidade < 2){
                                return realiza_jogada(i, j, jog);
                            }
                        } else {
                            tabuleiro[i][j] = ' ';
                        }
                    }
                }
            }
        }
    }

/*------------------------------- 5) CENTRO -------------------------------*/

    if (tabuleiro[1][1] == ' '){
        return realiza_jogada(1, 1, jog);
    }

/*------------------------------- 6) CANTO OPOSTO AO DO ADVERSARIO -------------------------------*/

    if (adv != ' '){
        for (i = 0; i < 3; i += 2){
            for (j = 0; j < 3; j += 2){
                if (tabuleiro[i][j] == adv && tabuleiro[2 - i][2 - j] == ' '){
                    return realiza_jogada(2 - i, 2 - j, jog);
                }
            }
        }
    }

/*------------------------------- 7) CANTO VAZIO (ALEATORIO) -------------------------------*/

    quantidade = 0;
    for (i = 0; i < 3; i += 2){
        for (j = 0; j < 3; j += 2){
            if (tabuleiro[i][j] == ' '){
                quantidade++;
            }
        }
    }
    if (quantidade > 0){
        srand(time(NULL));
        sorteio = rand() % quantidade;
        for (i = 0; i < 3; i += 2){
            for (j = 0; j < 3; j += 2){
                if (tabuleiro[i][j] == ' '){
                    if (sorteio == 0){
                        return realiza_jogada(i, j, jog);
                    }
                    sorteio--;
                }
            }
        }
    }

/*------------------------------- 8) LADO VAZIO -------------------------------*/

    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if ((i + j) % 2 == 1 && tabuleiro[i][j] == ' '){
                return realiza_jogada(i, j, jog);
            }
        }
    }

    /* tabuleiro cheio: nao ha o que jogar (o jogo principal deve tratar o empate) */
    return 2;
}

int computador_medio(char jog){
    int escolhe_modo, resp;
    escolhe_modo = 0;
    escolhe_modo = (rand() % 2) * 2;

    if (escolhe_modo == 0){
        return resp = computador_facil(jog);
    } else {
        return resp = computador_dificil(jog);
    }
}

int jogada_computador(char jog, int nivel){
    int resp;
    if (nivel == 1){
        return resp = computador_facil(jog);
    } else {
        if (nivel == 2){
            return resp = computador_medio(jog);
        } else {
            return resp = computador_dificil(jog);
            }
        }
}

 void main(){
    system("cls");
    bool ativo = true;
    int seleciona_modo, jogada1, jogada2;
    seleciona_modo = menu();

    if (seleciona_modo == 1){
        inicializa_velha();
        escolha_simb(&jog1, &jog2);
        while(ativo){
            jogada1 = faz_jogada(jog1);
            if (jogada1 == 1 || jogada1 == 0){
                break;
            } else {
                jogada2 = jogada_computador(jog2, nivel);
                if (jogada2 == 1 || jogada2 == 0){
                    break;
                }
            }
        }
        main();
    } else {
        if (seleciona_modo == 2){
        inicializa_velha();
        escolha_simb(&jog1, &jog2);
        while(ativo){
            jogada1 = faz_jogada(jog1);
            if (jogada1 == 1 || jogada1 == 0){
                break;
            } else {
                jogada2 = faz_jogada(jog2);
                if (jogada2 == 1 || jogada2 == 0){
                    break;
                    }
                }
            }
        main();
        } else {
            printf("\n\tPressione ENTER para encerrar...");
            getchar();
        }
    }
}

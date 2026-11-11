/*
 * ============================================================================
 * PSE EM AÇÃO — Sistema de Planejamento e Acompanhamento de Ações de Saúde
 *               na Escola
 * ----------------------------------------------------------------------------
 * Atividade de Estudo Programada (AEP) — 2ª entrega
 * Cursos: Engenharia de Software / Análise e Desenvolvimento de Sistemas
 * Unicesumar — 2º semestre de 2026
 *
 * Tema de contextualização: saúde mental no ambiente escolar
 *
 * Compilação:
 *   gcc -std=c99 -Wall -Wextra -o pse_em_acao pse_em_acao.c
 *
 * Execução:
 *   ./pse_em_acao        (Linux/macOS)
 *   pse_em_acao.exe      (Windows)
 *
 * O sistema trabalha apenas com dados fictícios e informações coletivas.
 * Não são registrados nomes, diagnósticos ou dados clínicos de estudantes.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_ACOES 100

#define TAM_CODIGO 10
#define TAM_ESCOLA 60
#define TAM_TEMA 50
#define TAM_PUBLICO 50
#define TAM_RESPONSAVEL 50
#define TAM_DATA 11
#define TAM_LINHA 128

/* Situações possíveis de uma ação do PSE */
enum Situacao {
    PLANEJADA = 1,
    REALIZADA = 2,
    CANCELADA = 3
};

/* Registro de uma ação coletiva do PSE */
struct Acao {
    char codigo[TAM_CODIGO];
    char escola[TAM_ESCOLA];
    char tema[TAM_TEMA];
    char dataPrevista[TAM_DATA];
    char publicoAlvo[TAM_PUBLICO];
    char responsavel[TAM_RESPONSAVEL];
    int quantidadePrevista;
    int quantidadeRealizada;
    int situacao;
};

/* Vetor de registros em memória e controle de ocupação */
struct Sistema {
    struct Acao acoes[MAX_ACOES];
    int total;
};

/* --------------------------------------------------------------------------
 * Funções utilitárias de entrada e texto
 * -------------------------------------------------------------------------- */
static void configurarConsole(void);
static void lerLinha(char *destino, int tamanho);
static int textoVazio(const char *texto);
static void lerTexto(const char *rotulo, char *destino, int tamanho);
static int lerInteiro(const char *rotulo, int minimo, int maximo);
static void lerData(const char *rotulo, char *destino);
static void lerCodigo(const char *rotulo, char *destino);
static int codigoValido(const char *codigo);
static int dataValida(const char *data);
static void converterMinusculo(char *destino, const char *origem);
static int contemTexto(const char *texto, const char *busca);
static int compararSemDiferenciar(const char *a, const char *b);
static void formatarPercentual(char *destino, int tamanho, double valor);
static void pausar(void);

/* --------------------------------------------------------------------------
 * Funções de apoio ao domínio do problema
 * -------------------------------------------------------------------------- */
static const char *nomeSituacao(int situacao);
static int buscarIndicePorCodigo(const struct Sistema *sis, const char *codigo);
static void exibirAcao(const struct Acao *acao, int numero);
static void exibirMenu(void);

/* --------------------------------------------------------------------------
 * Funcionalidades do sistema
 * -------------------------------------------------------------------------- */
static void cadastrarAcao(struct Sistema *sis);
static void listarAcoes(const struct Sistema *sis);
static void pesquisarAcao(const struct Sistema *sis);
static void atualizarSituacao(struct Sistema *sis);
static void gerarResumo(const struct Sistema *sis);

/* ==========================================================================
 * Programa principal
 * ========================================================================== */
int main(void) {
    struct Sistema sis;
    int opcao;

    configurarConsole();
    sis.total = 0;

    printf("Bem-vindo(a) ao PSE em Ação!\n");
    printf("Sistema de planejamento e acompanhamento de ações de saúde na escola.\n");

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opção: ", 0, 9);

        switch (opcao) {
            case 1:
                cadastrarAcao(&sis);
                break;
            case 2:
                listarAcoes(&sis);
                break;
            case 3:
                pesquisarAcao(&sis);
                break;
            case 4:
                atualizarSituacao(&sis);
                break;
            case 5:
                gerarResumo(&sis);
                break;
            case 0:
                printf("\nEncerrando o sistema. Até logo!\n");
                break;
            default:
                printf("\n[!] Opção inexistente no menu. Escolha um número entre 0 e 5.\n");
                break;
        }

        if (opcao != 0) {
            pausar();
        }
    } while (opcao != 0);

    return 0;
}

/* ==========================================================================
 * Implementação das funcionalidades
 * ========================================================================== */

/*
 * Cadastra uma nova ação do PSE, validando limite de armazenamento,
 * código repetido, campos obrigatórios, data e quantidade de participantes.
 */
static void cadastrarAcao(struct Sistema *sis) {
    struct Acao nova;
    int indice;

    printf("\n--- CADASTRO DE AÇÃO ---\n");

    if (sis->total >= MAX_ACOES) {
        printf("[!] Limite de armazenamento atingido (%d ações).\n", MAX_ACOES);
        printf("    Exclua registros ou reinicie o sistema para cadastrar novas ações.\n");
        return;
    }

    do {
        lerCodigo("Código da ação (ex.: PSE-001): ", nova.codigo);

        if (feof(stdin)) {
            return;
        }

        if (!codigoValido(nova.codigo)) {
            printf("  [!] Código inválido. Use apenas letras, números, hífen ou sublinhado.\n\n");
            nova.codigo[0] = '\0';
        } else if (buscarIndicePorCodigo(sis, nova.codigo) != -1) {
            printf("  [!] Código duplicado: já existe uma ação cadastrada com este código.\n\n");
            nova.codigo[0] = '\0';
        }
    } while (nova.codigo[0] == '\0');

    lerTexto("Escola: ", nova.escola, TAM_ESCOLA);
    lerTexto("Tema (ex.: saúde mental, alimentação saudável): ", nova.tema, TAM_TEMA);
    lerData("Data prevista (dd/mm/aaaa): ", nova.dataPrevista);
    lerTexto("Público-alvo: ", nova.publicoAlvo, TAM_PUBLICO);
    lerTexto("Responsável pela ação: ", nova.responsavel, TAM_RESPONSAVEL);
    nova.quantidadePrevista = lerInteiro("Quantidade prevista de participantes: ", 0, 9999);

    printf("\nSituação inicial da ação:\n");
    printf(" 1 - Planejada\n");
    printf(" 2 - Realizada\n");
    printf(" 3 - Cancelada\n");
    nova.situacao = lerInteiro("Opção: ", 1, 3);

    nova.quantidadeRealizada = 0;
    if (nova.situacao == REALIZADA) {
        nova.quantidadeRealizada = lerInteiro("Quantidade efetiva de participantes: ", 0, 9999);
    }

    indice = sis->total;
    sis->acoes[indice] = nova;
    sis->total++;

    printf("\n[ok] Ação %s cadastrada com sucesso na posição %d.\n", nova.codigo, indice + 1);
    printf("     Situação: %s | Participantes previstos: %d\n",
           nomeSituacao(nova.situacao), nova.quantidadePrevista);
}

/*
 * Lista todas as ações cadastradas em formato de bloco, para manter a
 * leitura confortável mesmo com nomes de escola e tema extensos.
 */
static void listarAcoes(const struct Sistema *sis) {
    int i;

    printf("\n--- AÇÕES CADASTRADAS (%d de %d) ---\n", sis->total, MAX_ACOES);

    if (sis->total == 0) {
        printf("Nenhuma ação cadastrada até o momento.\n");
        printf("Utilize a opção 1 do menu para cadastrar a primeira ação.\n");
        return;
    }

    for (i = 0; i < sis->total; i++) {
        exibirAcao(&sis->acoes[i], i + 1);
    }

    printf("\nTotal de registros listados: %d\n", sis->total);
}

/*
 * Pesquisa ações por código, escola ou tema. A comparação não diferencia
 * letras maiúsculas de minúsculas e aceita trechos do texto informado.
 */
static void pesquisarAcao(const struct Sistema *sis) {
    char termo[TAM_LINHA];
    char codigo[TAM_CODIGO];
    int tipo;
    int i;
    int encontrados = 0;

    printf("\n--- PESQUISA DE AÇÕES ---\n");

    if (sis->total == 0) {
        printf("Nenhuma ação cadastrada até o momento.\n");
        return;
    }

    printf(" 1 - Pesquisar por código\n");
    printf(" 2 - Pesquisar por escola\n");
    printf(" 3 - Pesquisar por tema\n");
    printf(" 0 - Voltar ao menu\n");
    tipo = lerInteiro("Opção: ", 0, 3);

    if (tipo == 0) {
        printf("Pesquisa cancelada. Retornando ao menu.\n");
        return;
    }

    if (tipo == 1) {
        lerCodigo("Código procurado: ", codigo);
        i = buscarIndicePorCodigo(sis, codigo);

        if (i == -1) {
            printf("\n[!] Ação não encontrada: não existe registro com o código %s.\n", codigo);
            return;
        }

        printf("\nAção encontrada:\n");
        exibirAcao(&sis->acoes[i], i + 1);
        return;
    }

    if (tipo == 2) {
        lerTexto("Trecho do nome da escola: ", termo, TAM_LINHA);
    } else {
        lerTexto("Trecho do tema: ", termo, TAM_LINHA);
    }

    printf("\nResultados para \"%s\":\n", termo);

    for (i = 0; i < sis->total; i++) {
        const char *campo = (tipo == 2) ? sis->acoes[i].escola : sis->acoes[i].tema;

        if (contemTexto(campo, termo)) {
            exibirAcao(&sis->acoes[i], i + 1);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("[!] Nenhuma ação encontrada para a busca informada.\n");
    } else {
        printf("\nRegistros encontrados: %d\n", encontrados);
    }
}

/*
 * Atualiza a situação de uma ação já cadastrada e, quando a nova situação
 * é "realizada", solicita a quantidade efetiva de participantes.
 */
static void atualizarSituacao(struct Sistema *sis) {
    char codigo[TAM_CODIGO];
    int indice;
    int novaSituacao;
    int efetivo;

    printf("\n--- ATUALIZAÇÃO DE SITUAÇÃO ---\n");

    if (sis->total == 0) {
        printf("Nenhuma ação cadastrada até o momento.\n");
        return;
    }

    lerCodigo("Código da ação: ", codigo);
    indice = buscarIndicePorCodigo(sis, codigo);

    if (indice == -1) {
        printf("\n[!] Ação não encontrada: não existe registro com o código %s.\n", codigo);
        printf("    Confira o código na opção 2 (listar ações) e tente novamente.\n");
        return;
    }

    printf("\nDados atuais da ação:\n");
    exibirAcao(&sis->acoes[indice], indice + 1);

    printf("\nNova situação:\n");
    printf(" 1 - Planejada\n");
    printf(" 2 - Realizada\n");
    printf(" 3 - Cancelada\n");
    printf(" 0 - Cancelar a atualização\n");
    novaSituacao = lerInteiro("Opção: ", 0, 3);

    if (novaSituacao == 0) {
        printf("Atualização cancelada. Nenhuma alteração foi realizada.\n");
        return;
    }

    if (novaSituacao == REALIZADA) {
        efetivo = lerInteiro("Quantidade efetiva de participantes: ", 0, 9999);

        if (efetivo > sis->acoes[indice].quantidadePrevista) {
            printf("  [i] Aviso: a quantidade efetiva supera a prevista (%d).\n",
                   sis->acoes[indice].quantidadePrevista);
        }

        sis->acoes[indice].quantidadeRealizada = efetivo;
    } else {
        /* Ações que deixam de ser realizadas não mantêm participantes efetivos */
        sis->acoes[indice].quantidadeRealizada = 0;
    }

    sis->acoes[indice].situacao = novaSituacao;

    printf("\n[ok] Ação %s atualizada para a situação \"%s\".\n",
           sis->acoes[indice].codigo, nomeSituacao(novaSituacao));

    if (novaSituacao == REALIZADA) {
        printf("     Participantes efetivos registrados: %d\n",
               sis->acoes[indice].quantidadeRealizada);
    }
}

/*
 * Gera o resumo geral com totais por situação, participantes e percentual
 * de participação das ações realizadas em relação ao previsto.
 */
static void gerarResumo(const struct Sistema *sis) {
    int i;
    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;
    int previstoRealizadas = 0;
    int efetivoRealizadas = 0;
    int previstoGeral = 0;
    double percentual = 0.0;

    printf("\n--- RESUMO GERAL DAS AÇÕES ---\n");

    if (sis->total == 0) {
        printf("Nenhuma ação cadastrada até o momento.\n");
        printf("Não há dados para gerar o resumo.\n");
        return;
    }

    for (i = 0; i < sis->total; i++) {
        previstoGeral += sis->acoes[i].quantidadePrevista;

        switch (sis->acoes[i].situacao) {
            case PLANEJADA:
                planejadas++;
                break;
            case REALIZADA:
                realizadas++;
                previstoRealizadas += sis->acoes[i].quantidadePrevista;
                efetivoRealizadas += sis->acoes[i].quantidadeRealizada;
                break;
            case CANCELADA:
                canceladas++;
                break;
        }
    }

    if (previstoRealizadas > 0) {
        percentual = (100.0 * efetivoRealizadas) / previstoRealizadas;
    }

    printf("\nTotal de ações cadastradas: %d\n", sis->total);
    printf("  Ações planejadas : %d\n", planejadas);
    printf("  Ações realizadas : %d\n", realizadas);
    printf("  Ações canceladas : %d\n", canceladas);

    printf("\nParticipantes previstos (todas as ações): %d\n", previstoGeral);
    printf("Participantes efetivos (ações realizadas): %d\n", efetivoRealizadas);
    printf("Previstos nas ações realizadas: %d\n", previstoRealizadas);

    if (previstoRealizadas > 0) {
        char textoPercentual[16];

        formatarPercentual(textoPercentual, sizeof(textoPercentual), percentual);
        printf("Percentual de participação das ações realizadas: %s%%\n", textoPercentual);
    } else if (realizadas == 0) {
        printf("Percentual de participação: não há ações realizadas para calcular.\n");
    } else {
        printf("Percentual de participação: não há participantes previstos para calcular.\n");
    }

    printf("\nSituação do acompanhamento:\n");
    {
        char textoConcluidas[16];

        formatarPercentual(textoConcluidas, sizeof(textoConcluidas),
                           (100.0 * realizadas) / sis->total);
        printf("  %d de %d ações concluídas (%s%% do total)\n",
               realizadas, sis->total, textoConcluidas);
    }
}

/* ==========================================================================
 * Funções de apoio ao domínio do problema
 * ========================================================================== */

static const char *nomeSituacao(int situacao) {
    switch (situacao) {
        case PLANEJADA:
            return "Planejada";
        case REALIZADA:
            return "Realizada";
        case CANCELADA:
            return "Cancelada";
        default:
            return "Indefinida";
    }
}

/* Retorna o índice da ação com o código informado ou -1 se não existir. */
static int buscarIndicePorCodigo(const struct Sistema *sis, const char *codigo) {
    int i;

    for (i = 0; i < sis->total; i++) {
        if (compararSemDiferenciar(sis->acoes[i].codigo, codigo) == 0) {
            return i;
        }
    }

    return -1;
}

static void exibirAcao(const struct Acao *acao, int numero) {
    printf("\n[%d] Código........: %s\n", numero, acao->codigo);
    printf("    Escola........: %s\n", acao->escola);
    printf("    Tema..........: %s\n", acao->tema);
    printf("    Data prevista.: %s\n", acao->dataPrevista);
    printf("    Público-alvo..: %s\n", acao->publicoAlvo);
    printf("    Responsável...: %s\n", acao->responsavel);
    printf("    Participantes.: previstos %d | realizados %d\n",
           acao->quantidadePrevista, acao->quantidadeRealizada);
    printf("    Situação......: %s\n", nomeSituacao(acao->situacao));
    printf("--------------------------------------------------------------\n");
}

static void exibirMenu(void) {
    printf("\n==============================================================\n");
    printf("                        PSE EM AÇÃO\n");
    printf("   Planejamento e acompanhamento de ações de saúde na escola\n");
    printf("==============================================================\n");
    printf("  1 - Cadastrar ação\n");
    printf("  2 - Listar ações cadastradas\n");
    printf("  3 - Pesquisar ação\n");
    printf("  4 - Atualizar situação da ação\n");
    printf("  5 - Gerar resumo geral\n");
    printf("  0 - Encerrar o sistema\n");
    printf("==============================================================\n");
}

/* ==========================================================================
 * Funções utilitárias de entrada e texto
 * ========================================================================== */

/*
 * Ajusta a saída do console para UTF-8 no Windows, garantindo que os acentos
 * sejam exibidos corretamente.
 */
static void configurarConsole(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}

/* Lê uma linha inteira do teclado, descartando o restante e a quebra de linha. */
static void lerLinha(char *destino, int tamanho) {
    int c;
    int i = 0;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (c != '\r' && i < tamanho - 1) {
            destino[i++] = (char)c;
        }
    }

    destino[i] = '\0';
}

static int textoVazio(const char *texto) {
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        if (!isspace((unsigned char)texto[i])) {
            return 0;
        }
    }

    return 1;
}

/* Lê um campo de texto obrigatório, repetindo a leitura enquanto for inválido. */
static void lerTexto(const char *rotulo, char *destino, int tamanho) {
    char linha[TAM_LINHA];

    for (;;) {
        printf("%s", rotulo);
        fflush(stdout);
        lerLinha(linha, sizeof(linha));

        if (feof(stdin)) {
            destino[0] = '\0';
            return;
        }

        if (textoVazio(linha)) {
            printf("  [!] Campo obrigatório: informe um valor.\n\n");
            continue;
        }

        if ((int)strlen(linha) >= tamanho) {
            printf("  [!] Texto muito longo. Use no máximo %d caracteres.\n\n", tamanho - 1);
            continue;
        }

        snprintf(destino, (size_t)tamanho, "%s", linha);
        return;
    }
}

/* Lê um número inteiro dentro do intervalo informado. */
static int lerInteiro(const char *rotulo, int minimo, int maximo) {
    char linha[TAM_LINHA];
    char *fim;
    long valor;

    for (;;) {
        printf("%s", rotulo);
        fflush(stdout);
        lerLinha(linha, sizeof(linha));

        if (feof(stdin)) {
            return minimo;
        }

        valor = strtol(linha, &fim, 10);

        while (*fim == ' ' || *fim == '\t') {
            fim++;
        }

        if (fim == linha || *fim != '\0') {
            printf("  [!] Entrada inválida: digite apenas números.\n\n");
            continue;
        }

        if (valor < minimo || valor > maximo) {
            printf("  [!] Valor fora do intervalo permitido (%d a %d).\n\n", minimo, maximo);
            continue;
        }

        return (int)valor;
    }
}

static void lerData(const char *rotulo, char *destino) {
    char linha[TAM_DATA];

    for (;;) {
        printf("%s", rotulo);
        fflush(stdout);
        lerLinha(linha, sizeof(linha));

        if (feof(stdin)) {
            destino[0] = '\0';
            return;
        }

        if (!dataValida(linha)) {
            printf("  [!] Data inválida. Informe uma data real no formato dd/mm/aaaa.\n\n");
            continue;
        }

        snprintf(destino, TAM_DATA, "%s", linha);
        return;
    }
}

static void lerCodigo(const char *rotulo, char *destino) {
    char linha[TAM_CODIGO];

    for (;;) {
        printf("%s", rotulo);
        fflush(stdout);
        lerLinha(linha, sizeof(linha));

        if (feof(stdin)) {
            destino[0] = '\0';
            return;
        }

        if (textoVazio(linha)) {
            printf("  [!] Campo obrigatório: o código não pode ficar vazio.\n\n");
            continue;
        }

        snprintf(destino, TAM_CODIGO, "%s", linha);
        return;
    }
}

static int codigoValido(const char *codigo) {
    int i;

    if (codigo[0] == '\0') {
        return 0;
    }

    for (i = 0; codigo[i] != '\0'; i++) {
        unsigned char c = (unsigned char)codigo[i];

        if (!isalnum(c) && c != '-' && c != '_') {
            return 0;
        }
    }

    return 1;
}

/* Valida formato dd/mm/aaaa e a existência da data no calendário. */
static int dataValida(const char *data) {
    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dia, mes, ano, i;

    if (strlen(data) != 10) {
        return 0;
    }

    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (data[i] != '/') {
                return 0;
            }
        } else if (!isdigit((unsigned char)data[i])) {
            return 0;
        }
    }

    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');
    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (mes < 1 || mes > 12) {
        return 0;
    }

    if (ano < 2000 || ano > 2100) {
        return 0;
    }

    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        diasPorMes[1] = 29;
    }

    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        return 0;
    }

    return 1;
}

static void converterMinusculo(char *destino, const char *origem) {
    int i;

    for (i = 0; origem[i] != '\0' && i < TAM_LINHA - 1; i++) {
        unsigned char c = (unsigned char)origem[i];
        destino[i] = (char)tolower(c);
    }

    destino[i] = '\0';
}

/* Verifica se "busca" aparece em "texto", ignorando maiúsculas e minúsculas. */
static int contemTexto(const char *texto, const char *busca) {
    char textoMinusculo[TAM_LINHA];
    char buscaMinusculo[TAM_LINHA];

    converterMinusculo(textoMinusculo, texto);
    converterMinusculo(buscaMinusculo, busca);

    return strstr(textoMinusculo, buscaMinusculo) != NULL;
}

static int compararSemDiferenciar(const char *a, const char *b) {
    char aMinusculo[TAM_LINHA];
    char bMinusculo[TAM_LINHA];

    converterMinusculo(aMinusculo, a);
    converterMinusculo(bMinusculo, b);

    return strcmp(aMinusculo, bMinusculo);
}

/* Formata o percentual com uma casa decimal e vírgula como separador. */
static void formatarPercentual(char *destino, int tamanho, double valor) {
    char *separador;

    snprintf(destino, (size_t)tamanho, "%.1f", valor);
    separador = strchr(destino, '.');

    if (separador != NULL) {
        *separador = ',';
    }
}

static void pausar(void) {
    char linha[TAM_LINHA];

    printf("\nPressione ENTER para voltar ao menu...");
    fflush(stdout);
    lerLinha(linha, sizeof(linha));
}

# Pseudocódigos

## Menu principal

```text
INÍCIO
    criar vetor de ações
    quantidade <- 0

    REPETIR
        exibir menu principal
        ler opção

        ESCOLHA opção
            CASO 1: cadastrar ação
            CASO 2: listar ações
            CASO 3: pesquisar ação
            CASO 4: atualizar situação
            CASO 5: gerar resumo geral
            CASO 0: encerrar sistema
            OUTRO CASO: exibir mensagem de opção inválida
        FIM-ESCOLHA
    ATÉ opção = 0
FIM
```

## Cadastro de ação

```text
INÍCIO
    solicitar código

    SE código já existir ENTÃO
        exibir "Código já cadastrado"
        encerrar operação
    FIM-SE

    solicitar escola
    solicitar tema
    solicitar data prevista
    solicitar público-alvo
    solicitar responsável
    solicitar quantidade prevista

    SE algum campo obrigatório estiver vazio OU quantidade prevista < 0 ENTÃO
        exibir mensagem de erro
        encerrar operação
    FIM-SE

    situação <- "Planejada"
    participantes efetivos <- 0

    salvar ação no vetor
    incrementar quantidade de ações
    exibir confirmação de cadastro
FIM
```

# Código-fonte — PSE em Ação

Implementação completa do sistema **PSE em Ação** em linguagem C (padrão C99), executada em terminal.

## Arquivo

| Arquivo | Descrição |
| --- | --- |
| `pse_em_acao.c` | Código-fonte completo do sistema (aproximadamente 800 linhas). |

## Compilação

```bash
# Windows (MinGW)
gcc -std=c99 -Wall -Wextra -o pse_em_acao.exe pse_em_acao.c

# Linux / macOS
gcc -std=c99 -Wall -Wextra -o pse_em_acao pse_em_acao.c
```

A compilação não produz erros nem avisos com `-Wall -Wextra`.

## Execução

```bash
pse_em_acao.exe     # Windows
./pse_em_acao       # Linux / macOS
```

## Menu

```text
  1 - Cadastrar ação
  2 - Listar ações cadastradas
  3 - Pesquisar ação
  4 - Atualizar situação da ação
  5 - Gerar resumo geral
  0 - Encerrar o sistema
```

## Estrutura do código

O programa está organizado em quatro blocos:

1. **Tipos e constantes** — `struct Acao` (dados de uma ação), `struct Sistema` (vetor de registros e contador) e as constantes de tamanho.
2. **Funcionalidades** — `cadastrarAcao`, `listarAcoes`, `pesquisarAcao`, `atualizarSituacao` e `gerarResumo`.
3. **Apoio ao domínio** — `buscarIndicePorCodigo`, `exibirAcao`, `nomeSituacao` e `exibirMenu`.
4. **Utilitárias de entrada** — `lerLinha`, `lerTexto`, `lerInteiro`, `lerData`, `lerCodigo`, validações e comparação de textos.

A função `main` apenas controla o laço do menu e chama a funcionalidade escolhida.

## Validações implementadas

| Situação | Comportamento |
| --- | --- |
| Código repetido | Mensagem de código duplicado e nova leitura do campo |
| Campo obrigatório vazio (ou só com espaços) | Mensagem de campo obrigatório e nova leitura |
| Data inexistente (ex.: 31/02/2026) ou fora do formato `dd/mm/aaaa` | Mensagem de data inválida e nova leitura |
| Quantidade não numérica, negativa ou acima de 9999 | Mensagem de intervalo permitido e nova leitura |
| Opção inexistente no menu | Mensagem de opção inexistente e retorno ao menu |
| Registro inexistente na pesquisa ou na atualização | Mensagem de ação não encontrada |
| Limite de armazenamento (100 ações) | Mensagem de limite atingido, sem cadastrar |

Ajustes adicionais: aviso quando a quantidade efetiva supera a prevista e cancelamento explícito da atualização de situação (opção 0).

## Armazenamento

Os registros são mantidos em um vetor de estruturas em memória, com limite de `MAX_ACOES` (100) posições. O uso de arquivo é opcional no desafio e não foi implementado nesta etapa; a persistência está registrada como possibilidade de melhoria no documento final.

## Observações

- O código utiliza somente dados fictícios e coletivos.
- Não há variáveis globais: o estado do sistema é passado por referência às funções.
- No Windows, `SetConsoleOutputCP(65001)` garante a exibição correta dos acentos no terminal.

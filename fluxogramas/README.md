# Fluxogramas

Fluxogramas elaborados na 1ª entrega, usados como base para a implementação.

## Arquivos

| Arquivo | Descrição |
| --- | --- |
| `fluxograma-geral.png` | Fluxo geral: menu principal, validação da opção, chamada da função correspondente e laço de repetição até a opção 0. |
| `fluxograma-cadastro.png` | Fluxo detalhado do cadastro de uma ação, com as decisões de código duplicado, campo obrigatório vazio e quantidade negativa. |

## Relação com a implementação

| Fluxograma | Onde está no código |
| --- | --- |
| Geral | `main`, com `do { exibirMenu(); switch (opcao) } while (opcao != 0)` |
| Cadastro | `cadastrarAcao`, com validação por repetição de leitura |

Duas diferenças entre o desenhado e o implementado, registradas na tabela 3 do documento final:

1. A **situação inicial** passou a ser informada pelo usuário (1, 2 ou 3), em vez de fixada como “planejada”.
2. Foi acrescentada a **validação da data no calendário**, que recusa datas inexistentes como 31/02.

Os dois fluxogramas também são reproduzidos no apêndice A do documento final, em `documentacao/`.

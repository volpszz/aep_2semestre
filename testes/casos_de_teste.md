# Casos de teste — PSE em Ação

Registro dos testes executados sobre a versão final do código-fonte (`codigo/pse_em_acao.c`).

## Ambiente

| Item | Descrição |
| --- | --- |
| Sistema operacional | Windows 11 |
| Compilador | gcc 6.3.0 (MinGW) |
| Comando de compilação | `gcc -std=c99 -Wall -Wextra -o pse_em_acao.exe pse_em_acao.c` |
| Resultado da compilação | Sem erros e sem avisos |

## Casos de teste

| ID | Caso de teste | Entrada | Resultado esperado | Situação |
| --- | --- | --- | --- | --- |
| CT01 | Cadastro com dados válidos | `PSE-001`, escola, tema, `15/09/2026`, público-alvo, responsável, `40` participantes, situação `1` | Registro armazenado e mensagem de confirmação | Conforme |
| CT02 | Cadastro com código duplicado | Código `PSE-001` já cadastrado | Mensagem de código duplicado e nova leitura do código | Conforme |
| CT03 | Campo obrigatório vazio | Escola preenchida apenas com espaços | Mensagem de campo obrigatório e nova leitura | Conforme |
| CT04 | Data inexistente | `31/02/2026` | Mensagem de data inválida e nova leitura | Conforme |
| CT05 | Data em formato inválido | `2026-09-15` | Mensagem de data inválida e nova leitura | Conforme |
| CT06 | Quantidade não numérica | `abc` | Mensagem de entrada inválida e nova leitura | Conforme |
| CT07 | Quantidade negativa | `-8` | Mensagem de valor fora do intervalo (0 a 9999) | Conforme |
| CT08 | Opção inexistente no menu | `7` | Mensagem de opção inexistente e retorno ao menu | Conforme |
| CT09 | Atualização de registro inexistente | `PSE-999` | Mensagem de ação não encontrada | Conforme |
| CT10 | Atualização para realizada | `PSE-002`, situação `2`, `38` participantes | Situação alterada e quantidade efetiva registrada | Conforme |
| CT11 | Resumo geral com cinco ações | Duas planejadas, duas realizadas e uma cancelada | Totais por situação, 205 previstos, 84 efetivos e 93,3% de participação | Conforme |
| CT12 | Pesquisa por tema | Termo `mental` | Três registros encontrados | Conforme |
| CT13 | Pesquisa sem resultados | Termo inexistente | Mensagem de nenhuma ação encontrada | Conforme |
| CT14 | Limite de armazenamento | 100 registros cadastrados e tentativa do 101º | Mensagem de limite atingido, sem cadastro | Conforme |
| CT15 | Encerramento do sistema | Opção `0` | Mensagem de encerramento e fim da execução | Conforme |

## Como reproduzir o teste de limite (CT14)

1. Compile o programa e execute-o.
2. Cadastre 100 ações fictícias com códigos distintos (`T001` a `T100`), mantendo os demais campos válidos.
3. Selecione novamente a opção 1 do menu.
4. O sistema deve exibir:

```text
--- CADASTRO DE AÇÃO ---
[!] Limite de armazenamento atingido (100 ações).
    Exclua registros ou reinicie o sistema para cadastrar novas ações.
```

## Observações

- Os dados utilizados nos testes são fictícios e coletivos, conforme os limites éticos do projeto.
- Os testes de validação foram executados na mesma sessão, de modo a verificar que o programa não perde os dados já digitados quando uma entrada é recusada.

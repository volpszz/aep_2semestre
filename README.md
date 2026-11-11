# PSE em Ação

Repositório da **AEP do 2º semestre de 2026** dos cursos de Engenharia de Software e Análise e Desenvolvimento de Sistemas da Unicesumar, contendo as duas etapas da atividade.

## Projeto

**PSE em Ação — Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola**

Tema escolhido para contextualização: **Saúde Mental no ambiente escolar**.

A proposta consiste em uma aplicação em linguagem C, executada em terminal, para auxiliar uma equipe escolar e de saúde no cadastro, na consulta e no acompanhamento de ações coletivas do Programa Saúde na Escola (PSE).

## Integrantes

- Arthur Volpato Moreira — RA 26004378-2
- João Vitor de Moraes Gongora — RA 26003960-2
- Paulo Nicholas Lopes Pereira — RA 26008839-2

## Status

| Etapa | Situação |
| --- | --- |
| 1ª entrega — documento escrito (contextualização, requisitos, fluxogramas, sprints) | Concluída |
| 2ª entrega — implementação, casos de uso, testes, manual e documento final | Concluída |

## Funcionalidades implementadas

| Código | Funcionalidade | Onde está no código |
| --- | --- | --- |
| RF01 | Cadastrar ação do PSE | `cadastrarAcao` |
| RF02 | Listar ações cadastradas | `listarAcoes` |
| RF03 | Pesquisar ação por código, escola ou tema | `pesquisarAcao` |
| RF04 | Atualizar situação e registrar participantes | `atualizarSituacao` |
| RF05 | Gerar resumo geral | `gerarResumo` |
| RF06 | Validar entradas | `lerTexto`, `lerInteiro`, `lerData`, `lerCodigo`, `codigoValido`, `dataValida` |

## Como compilar e executar

O código-fonte está em [`codigo/pse_em_acao.c`](codigo/pse_em_acao.c) e utiliza apenas a biblioteca padrão da linguagem C.

```bash
# Windows (MinGW)
gcc -std=c99 -Wall -Wextra -o pse_em_acao.exe pse_em_acao.c
pse_em_acao.exe

# Linux / macOS
gcc -std=c99 -Wall -Wextra -o pse_em_acao pse_em_acao.c
./pse_em_acao
```

O programa compila sem erros e sem avisos com as opções `-Wall -Wextra`.

## Estrutura do repositório

```text
.
├── README.md
├── codigo/
│   ├── pse_em_acao.c        # código-fonte do sistema
│   └── README.md            # detalhes técnicos da implementação
├── documentacao/
│   ├── AEP - 2 SEMESTRE PRIMEIRA ENTREGA.pdf
│   ├── AEP - 2 SEMESTRE SEGUNDA ENTREGA.docx
│   └── README.md
├── diagramas/
│   ├── casos_de_uso.png     # diagrama de casos de uso (UML)
│   └── README.md
├── fluxogramas/
│   └── README.md
├── pseudocodigos/
│   └── pseudocodigos.md
└── testes/
    └── casos_de_teste.md    # registro dos testes executados
```

## Artefatos da 2ª entrega

- **Código-fonte completo:** [`codigo/pse_em_acao.c`](codigo/pse_em_acao.c) — menu com laço de repetição, `struct`, vetor de registros, funções com responsabilidades separadas e validação de entradas.
- **Diagrama de casos de uso:** [`diagramas/casos_de_uso.png`](diagramas/casos_de_uso.png) — ator, casos de uso UC01 a UC06 e relação `«include»` da validação.
- **Descrição dos casos de uso:** seção 4 do documento final, com objetivo, ator, pré-condições, fluxo principal, fluxos alternativos e pós-condições.
- **Requisitos atualizados:** seção 2 do documento final, com a justificativa de cada alteração.
- **Testes realizados:** [`testes/casos_de_teste.md`](testes/casos_de_teste.md) — 15 casos de teste executados.
- **Manual do usuário e capturas de tela:** seção 7 do documento final.
- **Documento final:** [`documentacao/AEP - 2 SEMESTRE SEGUNDA ENTREGA.docx`](documentacao/AEP%20-%202%20SEMESTRE%20SEGUNDA%20ENTREGA.docx).

## Apresentação em vídeo

Vídeo de até 7 minutos com a demonstração do sistema em execução e a explicação das decisões de implementação: *link a ser inserido após a gravação.*

## Observações éticas

O sistema utiliza somente dados fictícios e informações coletivas. Não são armazenados nomes, diagnósticos, prontuários ou outros dados sensíveis individuais de estudantes. A aplicação também não realiza diagnóstico, triagem, prescrição ou recomendação de tratamento.

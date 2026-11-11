# Diagramas

Artefatos de modelagem produzidos na 2ª etapa da AEP.

## Arquivos

| Arquivo | Descrição |
| --- | --- |
| `casos_de_uso.png` | Diagrama de casos de uso (UML) do sistema PSE em Ação. |

## Conteúdo do diagrama

- **Ator:** integrante da equipe intersetorial (IntegraPSE).
- **Casos de uso:** UC01 Cadastrar ação do PSE, UC02 Listar ações cadastradas, UC03 Pesquisar ação, UC04 Atualizar situação da ação, UC05 Gerar resumo geral e UC06 Validar entradas.
- **Relação `«include»`:** UC01 e UC04 incluem UC06, pois a validação é executada obrigatoriamente durante o cadastro e a atualização de situação.

A descrição completa de cada caso de uso (objetivo, ator, pré-condições, fluxo principal, fluxos alternativos e pós-condições) está na seção 4 do documento final, em `documentacao/`.

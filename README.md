# Sistema de Senhas de Atendimento

Sistema de gerenciamento de senhas para terminal, escrito em **C** e **modularizado**. Foi inspirado no totem de atendimento de um laboratório de exames: o paciente se registra, recebe uma senha, e as senhas são chamadas por ordem de prioridade e exibidas em um painel.

> Projeto acadêmico em desenvolvimento. Veja a seção [Limitações e próximos passos](#limitações-e-próximos-passos).

---

## Funcionalidades

- **Registro do paciente** com gênero, idade, gestante e lactante (perguntadas apenas quando aplicável, ou seja, para o gênero feminino), necessidade especial e condição de obesidade.
- **Classificação automática** do atendimento em Normal, Preferencial ou Urgente a partir das respostas do registro.
- **Geração de senha** com prefixo por tipo (`N`, `P` ou `U`) e numeração própria para cada tipo (`N001`, `P001`, `U001`...), guardando o **horário de retirada**.
- **Escolha do serviço**: realização de exames/coleta, entrega de amostras ou retirada de resultados/orçamentos.
- **Filas por prioridade**: uma fila para cada tipo de atendimento.
- **Chamada por prioridade**: Urgente, depois Preferencial, depois Normal. Dentro do mesmo tipo, vale a ordem de chegada.
- **Painel de senhas** em três colunas (Normal, Preferencial e Urgente): a senha chamada pisca 3 vezes acima do painel, entra na coluna correspondente e, após o atendimento, o painel volta a ficar vazio.
- **Validação de entrada** nos dados do paciente (gênero, idade e respostas s/n).
- **Alocação dinâmica de memória** (`malloc`/`free`) para as senhas.

---

## Regras de classificação

| Condição do paciente | Tipo | Prefixo |
|---|---|---|
| 80 anos ou mais | Urgente | `U` |
| Gestante, lactante, com necessidade especial ou com obesidade | Preferencial | `P` |
| Nenhuma das anteriores | Normal | `N` |

A verificação segue essa ordem: quem tem 80 anos ou mais é sempre Urgente, mesmo que também se enquadre como preferencial.

**Ordem de chamada:** `U` → `P` → `N`.

---

## Requisitos

- **Windows** (o painel usa `windows.h` para o `Sleep` e `system("cls")` para limpar a tela)
- **GCC** (MinGW-w64 / MSYS2)

---

## Compilação e execução

Abra o terminal na pasta do projeto e rode:

```powershell
gcc *.c -o senhas
.\senhas
```

Se preferir listar os arquivos explicitamente:

```powershell
gcc main.c menu.c paciente.c senha.c fila.c painel.c -o senhas
```

Todos os arquivos `.c` precisam estar na mesma pasta que os `.h`.

---

## Como usar

Ao iniciar, o menu principal é exibido:

```
=== SISTEMA DE SENHAS ===
1 - Retirar senha
2 - Chamar proxima senha
0 - Sair
```

- **1 - Retirar senha:** pede os dados do paciente e o serviço desejado, e gera a senha.
- **2 - Chamar próxima senha:** chama a senha de maior prioridade e mostra o painel.
- **0 - Sair:** encerra o programa e libera a memória.

---

## Estrutura do projeto

```
.
├── main.c        # menu principal, retirar senha e chamar senha
├── menu.c / .h   # menus de serviço e principal
├── paciente.c / .h   # registro e classificação do paciente
├── senha.c / .h  # criação e formatação das senhas
├── fila.c / .h   # fila encadeada e chamada por prioridade
└── painel.c / .h # exibição do painel, anúncio e limpeza
```

Os arquivos `avaliacao.c` e `avaliacao.h` estão reservados para a próxima etapa.

---

## Estruturas de dados

| Estrutura | Módulo | Descrição |
|---|---|---|
| `Paciente` | `paciente.h` | Gênero, idade, gestante, lactante, necessidade especial e obesidade |
| `Senha` | `senha.h` | Código, tipo, serviço, paciente, horário de retirada e ponteiro para a próxima senha (lista encadeada) |
| `Fila` | `fila.h` | Ponteiros para o início e o fim da lista de senhas, e o tamanho |
| `Painel` | `painel.h` | Três filas (colunas), uma para cada tipo de atendimento |
| `TipoAtendimento` | `menu.h` | `TIPO_NORMAL`, `TIPO_PREFERENCIAL`, `TIPO_URGENTE` |
| `TipoServico` | `menu.h` | `SERVICO_EXAME`, `SERVICO_AMOSTRA`, `SERVICO_RESULTADO` |
| `OpcaoPrincipal` | `menu.h` | `OPCAO_SAIR`, `OPCAO_RETIRAR`, `OPCAO_CHAMAR` |

---

## Funções implementadas

### `menu`

| Função | O que faz |
|---|---|
| `menu_servico()` | Mostra as opções de serviço, valida a escolha e devolve o serviço |
| `menu_principal()` | Mostra o menu principal, valida a escolha e devolve a opção |

### `paciente`

| Função | O que faz |
|---|---|
| `paciente_registrar()` | Faz as perguntas do registro e devolve o paciente preenchido |
| `paciente_classificar()` | Decide se o atendimento é Normal, Preferencial ou Urgente |

Funções internas (visíveis apenas em `paciente.c`): `limpar_buffer`, `perguntar_sim_nao`, `perguntar_genero` e `perguntar_idade`.

### `senha`

| Função | O que faz |
|---|---|
| `senha_criar()` | Aloca uma senha, monta o código e registra o horário |
| `senha_formatar_horario()` | Converte o horário de retirada para o formato `HH:MM:SS` |
| `senha_nome_servico()` | Devolve o nome do serviço em texto |

### `fila`

| Função | O que faz |
|---|---|
| `fila_iniciar()` | Deixa a fila vazia |
| `fila_vazia()` | Informa se a fila está vazia |
| `fila_inserir()` | Insere uma senha no fim da fila |
| `fila_remover()` | Remove e devolve a senha do início da fila |
| `fila_liberar()` | Remove todas as senhas e libera a memória |
| `fila_chamar_proxima()` | Devolve a senha de maior prioridade (Urgente, Preferencial, Normal) |

### `painel`

| Função | O que faz |
|---|---|
| `painel_iniciar()` | Deixa as três colunas vazias |
| `painel_inserir()` | Coloca a senha na coluna do tipo dela |
| `painel_exibir()` | Limpa a tela e desenha o painel |
| `painel_anunciar()` | Faz a senha chamada piscar 3 vezes acima do painel |
| `painel_aguardar()` | Aguarda o número de segundos informado |
| `painel_limpar()` | Esvazia o painel e libera a memória |

Função interna: `desenhar`.

### `main`

| Função | O que faz |
|---|---|
| `retirar_senha()` | Registra o paciente, gera a senha e a coloca na fila de espera |
| `chamar_senha()` | Chama a próxima senha, anuncia, exibe no painel e esvazia o painel ao final |
| `main()` | Inicia as estruturas e executa o menu principal em loop |

---

## Exemplos de utilização

### Retirando uma senha

```
=== SISTEMA DE SENHAS ===
1 - Retirar senha
2 - Chamar proxima senha
0 - Sair
1

=== REGISTRO DO PACIENTE ===
Genero (m/f): f
Idade: 30
Esta gestante? (s/n): s
Esta lactante? (s/n): n
Possui necessidade especial? (s/n): n
Possui condicao de obesidade? (s/n): n
1 - Realizacao de Exames/Coleta
2 - Entrega de Amostras
3 - Retirada de Resultados/Orcamentos
1

Senha: P001
Servico: Exames/Coleta
Retirada as: 22:45:26
```

### Prioridade na chamada

Retirando as senhas nesta ordem:

| Ordem de retirada | Paciente | Senha |
|---|---|---|
| 1ª | 30 anos, masculino, sem condições | `N001` |
| 2ª | 30 anos, feminino, gestante | `P001` |
| 3ª | 85 anos | `U001` |

As chamadas (opção 2) acontecem nesta ordem: **`U001`, `P001`, `N001`**.

Se a opção 2 for escolhida sem senhas em espera, o sistema avisa: `Nenhuma senha na fila!`.

### Painel durante a chamada

A senha chamada pisca acima do painel:

```
==========================================
            PAINEL DE SENHAS
==========================================

      >>> CHAMANDO: U001 <<<

NORMAL        PREFERENCIAL  URGENTE
------------------------------------------
  (nenhuma senha no painel)
```

Depois, ela entra na coluna do seu tipo:

```
==========================================
            PAINEL DE SENHAS
==========================================



NORMAL        PREFERENCIAL  URGENTE
------------------------------------------
                            U001
```

Ao final do atendimento, o painel volta a ficar vazio.

---

## Limitações e próximos passos

- [ ] **Avaliação do atendimento:** pergunta "Recebeu o devido atendimento? (s/n)", com registro de uma nota explicando o motivo quando a resposta for `n`.
- [ ] **Validação dos menus numéricos:** digitar letra em vez de número nos menus de serviço e principal ainda trava a leitura (a validação já existe nos dados do paciente).
- O programa funciona apenas no **Windows**.

---

## Autor

_Seu nome_ — _disciplina / instituição_

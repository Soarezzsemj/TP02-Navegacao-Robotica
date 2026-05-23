# Atividade Avaliativa — TAD Caminho

> Implementação do Tipo Abstrato de Dados (TAD) `Caminho` em linguagem C, utilizando listas encadeadas para rastrear trajetórias de um robô em um plano cartesiano.

---

## 📋 Descrição

O sistema permite inicializar, processar e analisar o caminho percorrido por um robô autônomo a partir de uma sequência de comandos de movimento (`N`, `S`, `L`, `O`). Cada movimento é armazenado em uma lista encadeada de instruções, e cada posição visitada é registrada em um histórico de posições.

---

## 📁 Estrutura do Projeto

```
.
├── caminho.h       # Header com definição das structs e assinaturas (fornecido)
├── main.c          # Arquivo de testes (fornecido)
└── 25201228.c      # Implementação do TAD (este arquivo)
```

---

## ⚙️ Compilação

**Linux:**
```bash
gcc 25201228.c main.c -o robo
./robo
```

**Windows:**
```bash
gcc 25201228.c main.c -o robo.exe
robo.exe
```

> **Atenção:** o arquivo `caminho.h` deve estar no mesmo diretório.

---

## 🧱 Estruturas de Dados

```c
typedef struct Comando {
    char Direcao;           // 'N', 'S', 'L' ou 'O'
    struct Comando *Proximo;
} Comando;

typedef struct Posicao {
    int X;
    int Y;
    struct Posicao *Proximo;
} Posicao;

typedef struct Caminho {
    Posicao  *Inicio;      // Primeira posição ocupada pelo robô
    Posicao  *Fim;         // Última posição ocupada pelo robô
    Posicao  *Historico;   // Lista completa de posições visitadas
    Comando  *Instrucoes;  // Lista de comandos executados
    int       N;           // Quantidade de instruções executadas
} Caminho;
```

---

## 🔧 Funções Implementadas

| Função | Descrição |
|---|---|
| `InicializarCaminho(seq, x, y)` | Cria e retorna um `Caminho` a partir da sequência de comandos e posição inicial |
| `DestruirCaminho(C)` | Libera toda a memória alocada pelo caminho |
| `DeterminarFim(C)` | Retorna ponteiro para a posição final do robô |
| `HistoricoPosicoes(C)` | Retorna ponteiro para o início do histórico de posições |
| `CalcularDistanciaTotal(C)` | Retorna o número total de comandos executados |
| `CalcularDistanciaGeometrica(C)` | Retorna a distância euclidiana entre início e fim |
| `CalcularDistanciaManhattan(C)` | Retorna a distância de Manhattan entre início e fim |
| `ContarInstrucoes(C)` | Retorna a quantidade de instruções na lista |

---

## 🗺️ Comandos de Movimento

| Comando | Efeito |
|---|---|
| `N` | Incrementa Y (move para Norte) |
| `S` | Decrementa Y (move para Sul) |
| `L` | Incrementa X (move para Leste) |
| `O` | Decrementa X (move para Oeste) |

---

## 💡 Detalhes de Implementação

- Funções auxiliares `CriarPosicao` e `CriarComando` encapsulam a alocação e inicialização dos nós
- Toda alocação com `malloc` é verificada — em caso de falha, a memória já alocada é liberada antes de retornar `NULL`
- Comandos inválidos na sequência resultam em retorno `NULL` com liberação completa da memória
- Sem vazamentos de memória — compatível com Valgrind

---

## 📐 Exemplos de Saída Esperada

Para a sequência `"LLLLLLLNNNNN"` com posição inicial `(2, 2)`:

```
Posicao final: (9, 7)
Distancia total percorrida: 12
Distancia geometrica: 8.60
Distancia de Manhattan: 12
Quantidade de instrucoes: 12
```

---
## 👤 Autor

**Matrícula:** 25201228  
**Disciplina:** Estruturas de Dados  
**Professor:** Marcelo Eustaquio  
**Compilador:** GCC (Linux/Windows)
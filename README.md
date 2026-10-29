# 📚 Sistema de Gerenciamento de Biblioteca 

> Um sistema em C para organizar o acervo de uma biblioteca de forma rápida e eficiente, usando uma **árvore Patricia (Practical Algorithm To Retrieve Information Coded In Alphanumeric)** indexada pelo **Título** dos livros. 🚀

---

## 👩‍💻 Integrantes da Dupla

| 👤 Nome | 🎓 Matrícula |
|---|---|
| Ana Paula Ferreira | 6569 |
| Laura Soares do Vale | 6574 |

---

## 📖 Descrição do Problema e da Aplicação Desenvolvida

### 🧩 O problema

Uma biblioteca precisa gerenciar o seu acervo de livros, permitindo que os funcionários possam:

- ➕ **Cadastrar** novas obras
- 🔍 **Consultar** informações dos livros
- ❌ **Remover** livros do acervo
- 🗂️ **Organizar** o catálogo

Quando a quantidade de livros é grande, realizar **buscas sequenciais** se torna **ineficiente** 🐌, pois, no pior caso, é necessário percorrer todo o acervo para encontrar um único livro.

### 💡 A solução

Desenvolvemos um sistema que utiliza uma **árvore Patricia** para organizar os livros pelo **Título**, permitindo **buscas, inserções e remoções eficientes** ⚡, mesmo com um acervo grande. Os livros são carregados de um arquivo de texto (`data/livros.txt`), com um livro por linha no formato `título;autor;ano;quantidade`.

---

## 🌳 Estrutura de Dados Escolhida e Justificativa Técnica

Escolhemos a **Árvore Patricia** 🎯, uma árvore **digital** (uma *trie* compactada): em vez de comparar chaves inteiras a cada nó, ela decide o caminho olhando **um bit** da chave por vez.

### 🔧 Como ela funciona

- Os **nós internos** guardam apenas o **índice do bit** que será testado: se o bit for `0`, a busca segue para a esquerda; se for `1`, para a direita.
- Os **nós externos** (folhas) guardam os livros.
- Ao chegar a uma folha, o sistema **compara o título completo** para confirmar se é o livro procurado, já que o caminho só leva ao candidato mais provável.
- A árvore tem **um formato único para cada conjunto de títulos**, independente da ordem em que foram inseridos. Por isso ela **não precisa de balanceamento nem de rotações**.

### ✅ Por que a Patricia?

- 🔑 **Chave natural para texto:** o título é uma sequência de caracteres, e cada caractere já é uma sequência de bits. A Patricia usa esses bits diretamente, sem precisar converter o título em um número.
- ⚡ **Custo de busca ligado ao tamanho do título:** o número de bits testados numa busca é limitado pelo tamanho do título, e não cresce proporcionalmente à quantidade de livros do acervo.
- 🧬 **Aproveita prefixos em comum:** muitos títulos começam igual (por exemplo, os livros da série *Harry Potter e ...*). Em vez de repetir essa parte em vários nós, a Patricia **pula direto** para o primeiro bit em que dois títulos diferem.
- 🧠 **Sem rotações:** como a forma da árvore não depende da ordem de inserção, não é necessário manter fator de balanceamento nem fazer rotações, o que simplifica a inserção.

## ⚙️ Descrição das Principais Operações Implementadas

> 🚧 *Seção em construção — será preenchida conforme o projeto avançar.*

---

## 🗃️ Organização dos Arquivos do Projeto

```
📦 SistemaDeGerenciamentoDeBiblioteca/
 ┣ 📂 data/
 ┃ ┗ 📄 livros.txt     # Acervo inicial (título;autor;ano;quantidade)
 ┣ 📂 include/
 ┃ ┗ 📄 patricia.h     # Declarações: estruturas e protótipos das funções
 ┣ 📂 src/
 ┃ ┣ 📄 patricia.c     # Implementação da árvore Patricia e leitura dos livros
 ┃ ┗ 📄 main.c         # Programa principal (interface do sistema)
 ┣ 📂 tests/
 ┃ ┗ 📄 teste.c        # Testes das operações da árvore
 ┣ 🛠️ Makefile          # Automatização da compilação
 ┗ 📝 README.md         # Documentação do projeto
```

---

## 🛠️ Instruções de Compilação e Execução

Na pasta raiz do projeto:

```
gcc src/main.c src/patricia.c -o oi
```

Depois, execute **a partir da pasta raiz** (o programa abre `data/livros.txt` usando esse caminho):

```
./oi        # Linux/macOS
.\oi        # PowerShell (Windows)
```

> 🚧 *Instruções via `Makefile` — em construção.*

---

## 🧪 Descrição dos Testes Realizados

> 🚧 *Seção em construção — será preenchida conforme o projeto avançar.*

---

## 📊 Resultados Experimentais e Análise

> 🚧 *Seção em construção — será preenchida conforme o projeto avançar.*

---

## ⚠️ Limitações Conhecidas e Possíveis Melhorias

> 🚧 *Seção em construção — será preenchida conforme o projeto avançar.*

---

<p align="center">
  Feito com 💙 e muito ☕ por Ana Paula e Laura
</p>
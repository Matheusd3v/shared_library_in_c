# Shared library - C

### Introdução

Este repositório tem como objetivo gerar uma biblioteca compartilhada (.so) para processar arquivos CSV em um código em C. O código da biblioteca foi desenvolvido e compilado em C.

### Como usar a biblioteca

Para usar a biblioteca, basta importar o header (libcsv.h) no topo do seu código e deixar a biblioteca na raiz do diretório.

Exemplo de uso:

```c
#include <stdio.h>
#include "libcsv.h" 

int main() {
    const char filepath[] = "./test2.csv";
    processCsvFile(filepath, "header256", "header255=71\nheader256=75");

    return 0;
}

```

Ao compilar o código em C, é necessário vincular a biblioteca como no exemplo a seguir:


```bash
gcc main.c -o main -L. -lcsv
```

### Scripts

Foi usado um arquivo Makefile para executar os scripts:

```bash
# Execução do binário do arquivo da biblioteca
make run 

# Atualiza o build e executa o binário
make run-dev 

# Build do binário do arquivo da biblioteca
make build

# Compilação da biblioteca compartilhada em arquivo .so na raiz do projeto
make shared-library

# Execução dos testes unitários
make tests
```

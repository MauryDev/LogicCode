# Documentação do LogicCode

## Introdução

O LogicCode é uma linguagem de programação desenvolvida para a criação e simulação de circuitos lógicos. Ela oferece recursos para a definição de portas lógicas, criação de funções, declaração de constantes e variáveis, e manipulação de valores lógicos.

## Sintaxe

### Declaração de portas lógicas

As portas lógicas podem ser declaradas utilizando as palavras-chave `and`, `or`, `not`, `xor`. Elas permitem a combinação de valores lógicos para obter um resultado lógico.

Exemplo:
```
A = true;
B = false;
C = and(A, B);
```

### Declaração de funções

As funções podem ser definidas usando a palavra-chave `fun`. Elas permitem agrupar um conjunto de instruções lógicas que podem ser reutilizadas em diferentes partes do código.

Exemplo:
```
fun mylogic(a, b) (
    b1 = and(not a, not b);
    b2 = and(not a, b);
    return or(b1, b2);
);
```

### Declaração de constantes

As constantes podem ser definidas utilizando a palavra-chave `const`. Elas representam valores lógicos fixos que não podem ser modificados durante a execução do programa.

Exemplo:
```
const true_value = true;
const false_value = false;
```

### Declaração de variáveis

As variáveis podem ser declaradas sem a palavra-chave `const`. Elas representam valores lógicos que podem ser modificados durante a execução do programa.

Exemplo:
```
A = true;
B = false;
```

### Impressão de valores

Os valores lógicos podem ser impressos utilizando a palavra-chave `print`. Isso permite exibir o resultado de uma operação ou o valor de uma variável no console.

Exemplo:
```
A = true;
B = false;
C = and(A, B);
print(C);
```

## Funções embutidas

O LogicCode fornece algumas funções embutidas que podem ser usadas para manipular valores lógicos.

- `and(x, y)`: Retorna o resultado da operação lógica "E" entre `x` e `y`.
- `or(x, y)`: Retorna o resultado da operação lógica "OU" entre `x` e `y`.
- `not(x)`: Retorna o resultado da operação lógica "NÃO" do valor `x`.
- `xor(x, y)`: Retorna o resultado da operação lógica "OU exclusivo" entre `x` e `y`.

## Exemplo completo

Aqui está um exemplo completo que demonstra o uso do LogicCode para definir portas lógicas, criar funções e imprimir valores:

```
A = true;
B = false;

fun mylogic(a, b) (
    b1 = and(not a, not b);
    b2 = and(not a, b);
    return or(b1, b2);
);

C = mylogic(A, B);
print(C);
```

Neste exemplo, declaramos as variáveis `A` e `B` com valores lógicos. Em seguida, definimos a função `mylogic` que realiza operações lógicas com base nos parâmetros `a` e `b`. Finalmente, chamamos a função `mylogic` com os valores
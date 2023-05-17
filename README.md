# Documenta��o do LogicCode

## Introdu��o

O LogicCode � uma linguagem de programa��o desenvolvida para a cria��o e simula��o de circuitos l�gicos. Ela oferece recursos para a defini��o de portas l�gicas, cria��o de fun��es, declara��o de constantes e vari�veis, e manipula��o de valores l�gicos.

## Sintaxe

### Declara��o de portas l�gicas

As portas l�gicas podem ser declaradas utilizando as palavras-chave `and`, `or`, `not`, `xor`. Elas permitem a combina��o de valores l�gicos para obter um resultado l�gico.

Exemplo:
```
A = true;
B = false;
C = and(A, B);
```

### Declara��o de fun��es

As fun��es podem ser definidas usando a palavra-chave `fun`. Elas permitem agrupar um conjunto de instru��es l�gicas que podem ser reutilizadas em diferentes partes do c�digo.

Exemplo:
```
fun mylogic(a, b) (
    b1 = and(not a, not b);
    b2 = and(not a, b);
    return or(b1, b2);
);
```

### Declara��o de constantes

As constantes podem ser definidas utilizando a palavra-chave `const`. Elas representam valores l�gicos fixos que n�o podem ser modificados durante a execu��o do programa.

Exemplo:
```
const true_value = true;
const false_value = false;
```

### Declara��o de vari�veis

As vari�veis podem ser declaradas sem a palavra-chave `const`. Elas representam valores l�gicos que podem ser modificados durante a execu��o do programa.

Exemplo:
```
A = true;
B = false;
```

### Impress�o de valores

Os valores l�gicos podem ser impressos utilizando a palavra-chave `print`. Isso permite exibir o resultado de uma opera��o ou o valor de uma vari�vel no console.

Exemplo:
```
A = true;
B = false;
C = and(A, B);
print(C);
```

## Fun��es embutidas

O LogicCode fornece algumas fun��es embutidas que podem ser usadas para manipular valores l�gicos.

- `and(x, y)`: Retorna o resultado da opera��o l�gica "E" entre `x` e `y`.
- `or(x, y)`: Retorna o resultado da opera��o l�gica "OU" entre `x` e `y`.
- `not(x)`: Retorna o resultado da opera��o l�gica "N�O" do valor `x`.
- `xor(x, y)`: Retorna o resultado da opera��o l�gica "OU exclusivo" entre `x` e `y`.

## Exemplo completo

Aqui est� um exemplo completo que demonstra o uso do LogicCode para definir portas l�gicas, criar fun��es e imprimir valores:

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

Neste exemplo, declaramos as vari�veis `A` e `B` com valores l�gicos. Em seguida, definimos a fun��o `mylogic` que realiza opera��es l�gicas com base nos par�metros `a` e `b`. Finalmente, chamamos a fun��o `mylogic` com os valores
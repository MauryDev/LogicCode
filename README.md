# LogicCode Documentation

## Introduction

LogicCode is a programming language developed for the creation and simulation of logical circuits. It provides features for defining logic gates, creating functions, declaring constants and variables, and manipulating logical values.

## Syntax

### Logic Gates Declaration

Logic gates can be declared using the keywords `and`, `or`, `not`, `xor`. They allow combining logical values to obtain a logical result.

Example:
```
A = true;
B = false;
C = and(A, B);
```

### Function Declaration

Functions can be defined using the `fun` keyword. They allow grouping a set of logical instructions that can be reused in different parts of the code.

Example:
```
fun mylogic(a, b) (
    b1 = and(not(a), not(b)),
    b2 = and(not(a), b),
    return or(b1, b2)
);
```

### Constants Declaration

Constants can be defined using the `const` keyword. They represent fixed logical values that cannot be modified during program execution.

Example:
```
const true_value = true;
const false_value = false;
```

### Variables Declaration

Variables can be declared without the `const` keyword. They represent logical values that can be modified during program execution.

Example:
```
A = true;
B = false;
```

### Printing Values

Logical values can be printed using the `print` keyword. This allows displaying the result of an operation or the value of a variable in the console.

Example:
```
A = true;
B = false;
C = and(A, B);
print(C);
```

## Built-in Functions

LogicCode provides some built-in functions that can be used to manipulate logical values.

- `and(x, y)`: Returns the result of the logical "AND" operation between `x` and `y`.
- `or(x, y)`: Returns the result of the logical "OR" operation between `x` and `y`.
- `not(x)`: Returns the result of the logical "NOT" operation on the value `x`.
- `xor(x, y)`: Returns the result of the logical "XOR" operation between `x` and `y`.

## Complete Example

Here's a complete example that demonstrates the use of LogicCode to define logic gates, create functions, and print values:

```
A = true;
B = false;

fun mylogic(a, b) (
    b1 = and(not(a), not(b)),
    b2 = and(not(a), b),
    return or(b1, b2)
);

C = mylogic(A, B);
print(C);
```

In this example, we declare the variables `A` and `B` with logical values. Then, we define the function `mylogic` that performs logical operations based on the parameters `a` and `b`. Finally, we call the `mylogic` function with the values `A` and `B` and print the result.
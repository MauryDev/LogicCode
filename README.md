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
fun mylogic(a, b) @{
    b1 = and(not(a), not(b));
    b2 = and(not(a), b);
    return or(b1, b2);
};
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

fun mylogic(a, b) @{
    b1 = and(not(a), not(b));
    b2 = and(not(a), b);
    return or(b1, b2);
};

C = mylogic(A, B);
print(C);
```

In this example, we declare the variables `A` and `B` with logical values. Then, we define the function `mylogic` that performs logical operations based on the parameters `a` and `b`. Finally, we call the `mylogic` function with the values `A` and `B` and print the result.


Other Examples:

Example 1:
```
truthtable(fun (a,b) @{
	print("A:",a,"B:",b,"Result:", and(a,b));
},int 2);

```
Example 2:
```
fun twobitmax(a1,a2) @{
    if (or(cmpgreater(a1,a2), cmpequal(a1,a2))) @{
        return a1;
    } else @{
        return a2;
    };
};

truthtable(fun(a,b,c,d) @{
    var A = bitset.concat(a,b);
    var B = bitset.concat(c,d);
    var C = twobitmax(A,B);
    debug.log(A,B);
},int 4);



```

Example 3:
```
fun halfadder(A,B,ref_S,ref_C) @{
    const S = xor(A, B);
    const C = and(A, B);
    refbitset.set(ref_S, S);
    refbitset.set(ref_C, C);
};
var carry = none;
var result = none;

halfadder(1,1,ref result,ref carry);
debug.log(result,carry);
```

Example 4:

```
fun fulladder(A,B,C,ref_S,ref_C) @{
    const t1 = xor(A,B);
    const t2 = xor(t1,C);
    const t3 = and(t1,C);
    const t4 = and(A,B);
    const t5 = or(t3,t4);
    refbitset.set(ref_S,t2);
    refbitset.set(ref_C,t5);
};


var result = none;
var CarryIn = none;
fulladder(1,1,0,ref result,ref CarryIn);

debug.log(result,CarryIn);
```

<span style="color:blue">some *blue* text</span>.


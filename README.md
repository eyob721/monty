# 0x19. C - Stacks, Queues - LIFO, FIFO

## Description

In this project we use the concept of stack and queue data structures to implement the Monty interpreter.

Using the standard library is not a restriction for this project, but I have used my implementations of the standard library, so as to learn and be in consistent with previous C projects.

## The Monty language

Monty 0.98 is a scripting language that is first compiled into Monty byte codes (Just like Python). It relies on a unique stack, with specific instructions to manipulate it. The goal of this project is to create an interpreter for Monty ByteCodes files.

### Monty byte code files

Files containing Monty byte codes usually have the `.m` extension. Most of the industry uses this standard but it is not required by the specification of the language. There is not more than one instruction per line. There can be any number of spaces before or after the opcode and its argument:

```bash
eyob721@arhcpapi: cat -e tests/000.m
push 0$
push 1$
push 2$
  push 3$
                   pall    $
push 4$
    push 5    $
      push    6$
pall$
```

Monty byte code files can contain blank lines (empty or made of spaces only), and any additional text after the opcode or its required argument is not taken into account.

## Stacks and Queues

The Monty interpreter operates on a unique stack. The opcodes are the instructions which manipulate this stack. By default the the Monty interpreter uses a stack data structure, a LIFO operation. But this can be changed to a queue data structure as well, by using the `stack` and `queue` opcodes. This opcodes change the mode of operation of the Monty interpreter to LIFO operation, which is the stack data structure, or to a FIFO operation, which the queue data structure.

## Implemented Opcodes

In this project the following opcodes are implemented:

| Opcodes | Description |
| --- | --- |
| push | Pushes an element on the stack. Usage: `push <integer>` |
| pall | Prints all the element in the stack. Starting from the top element. |
| pint | Prints the element at the top.  <br>If the stack is empty, it prints an error message. |
| pop | Removes the top element.  <br>If the stack is empty, it prints an error message. |
| swap | Swaps the top two elements.  <br>If the stack has less than two elements, it prints an error message. |
| nop | Does nothing. |
| add | Adds the top element of the stack on to the second top element of the stack, and removes the top element.  <br>If the stack has less than two elements, it prints an error message. |
| sub | Subtracts the top element of the stack from the second top element of the stack, and removes the top element.  <br>If the stack has less than two elements, it prints an error message. |
| div | Divides the second top element of the stack by the top element of the stack, and removes the top element.  <br>If the stack has less than two elements, it prints an error message. |
| mul | Multiplies the second top element of the stack by the top element of the stack, and removes the top element.  <br>If the stack has less than two elements, it prints an error message. |
| mod | Computes the remainder of the division of the second top element of the stack by the top element of the stack.  <br>The result is assigned to the second top element, and the top element is removed.  <br>If the stack has less than two elements, it prints an error message. |
| pchar | Prints the char at the top of the stack, followed by a new line. The integer stored at the top of the stack is treated as the ascii value of the character to be printed. If the integer is not in the ascii table or if the stack is empty, an error message is displayed. |
| pstr | Prints the string starting at the top of the stack, followed by a new line.  <br>The integer stored in each element of the stack is treated as the ascii value of the character to be printed.  <br>The string stops when either the stack is over, the value of the element is 0, or the value of the element is not in the ascii table.  <br>If the stack is empty it will only print a new line. |
| rotl | Rotates the stack to the left. Meaning that the top element becomes the last element and the second top element becomes the top element. |
| rotr | Rotates the stack to the right. Meaning that the top element becomes the second top element and the last element becomes the top element. |
| stack | Sets the format of the data structure to a stack (LIFO). This is the default data structure of the program. |
| queue | Sets the format of the data structure to a queue (FIFO). |

## Usage

To use the Monty interpreter:

- first clone the repo into you directory
  - `git clone https://github.com/eyob721/monty.git`
- then compile the source code
  - `cd monty`
  - `gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o monty`
- and run the program with your byte code file
  - **USAGE:** `./monty file`
  - You can find sample bytecode files in [bytecodes/](./bytecodes/)

## Contributors

Eyob Melkamu ([eyob721](https://github.com/eyob721))
Ezra Wolderufael ([ezralx](https://github.com/Ezralx))

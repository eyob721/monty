#ifndef MONTY_H
#define MONTY_H

/* === MONTY - HEADERS AND MACROS ====================================== {{{ */

/* STANDARD HEADERS */
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* CUSTOM HEADERS */
#include "lib.h"

/* FILE I/O CONSTANTS  */
#define OPEN_ERR -1
#define READ_EOF 0
#define READ_ERR -1

/* BUFFER CONSTANTS */
#define LINE_BUFF_SIZE 128

/*}}}*/

/* === MONTY - DATA STRUCTURES ========================================= {{{ */

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **top, unsigned int line_number);
} instruction_t;

/**
 * struct monty_s - a data structure used to hold necessary data for
 *                  opcode handlers, and memory cleanup.
 * @cur_opcode: current opcode
 * @cur_oparg: current opcode argument
 * @bottom: pointer to the bottom (last) node in the stack
 * @exit_status: used to hold the exit status of the monty program
 *
 * Description: this data structure is used to share data among the
 *              main function and opcode handler functions.
 */
typedef struct monty_s
{
	char *cur_opcode;
	char *cur_oparg;
	int exit_status;
	stack_t *bottom;
} monty_t;

/*}}}*/

/* === MONTY - GENERAL UTILS =========================================== {{{ */
int read_line(int fd, char **line_buff, int *line_size);
int is_integer(char *str);
void free_stack(stack_t *top);

/*}}}*/

/* === MONTY - OPCODES UTILS =========================================== {{{ */
void push_to_top(stack_t **top, stack_t *new_stack);
/*}}}*/

/* === MONTY - OPCODE HANDLERS ========================================= {{{ */
/* 1 */
void push(stack_t **top, unsigned int lnum);
void pall(stack_t **top, unsigned int lnum);
void pint(stack_t **top, unsigned int lnum);
void pop(stack_t **top, unsigned int lnum);
/*}}}*/

/* === MONTY - MAIN FUNCTIONS ========================================== {{{ */
void get_opcode_oparg(char *line_buf);
void (*get_opcode_function(char *opcode))(stack_t **top, unsigned int line);
/*}}}*/

/* === MONTY - GLOBAL VAIRABLES ======================================== {{{ */
extern monty_t monty;
/*}}}*/

#endif

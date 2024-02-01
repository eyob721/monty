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
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/*}}}*/

/* === MONTY - GENERAL UTILS =========================================== {{{ */

int read_line(int fd, char **line_buff, int *line_size);

/*}}}*/

/* === MONTY - CLEANUP UTILS =========================================== {{{ */
/*}}}*/

/* === MONTY - OPCODES UTILS =========================================== {{{ */
/*}}}*/

/* === MONTY - OPCODE HANDLERS ========================================= {{{ */
/*}}}*/

/* === MONTY - MAIN FUNCTIONS ========================================== {{{ */
/*}}}*/

/* === MONTY - GLOBAL VAIRABLES ======================================== {{{ */
/*}}}*/

#endif

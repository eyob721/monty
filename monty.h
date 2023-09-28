#ifndef MONTY_H
#define MONTY_H

/* ------------------------------------------------------------------------- */
/*                 MONTY - HEADERS AND MACROS                                */
/* ------------------------------------------------------------------------- */
/* STANDARD HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

/* CUSTOM HEADERS */
#include "lib.h"

/* FILE I/O CONSTANTS  */
#define OPEN_ERR -1

/* READ SYSTEM CALL CONSTANTS */
#define READ_EOF 0
#define READ_ERR -1

/* BUFFER CONSTANTS */
#define LINE_BUFF_SIZE 128

/* MACRO TO CHECK IF X IS A VALID ASCII VALUE */
#define IS_VALID_ASCII_VALUE(x) ((x) >= 0 && (x) <= 127)

/* FORMAT OF THE MONTY STACK */
#define STACK_MODE 0
#define QUEUE_MODE 1

/* MACRO TO INITIALIZE MONTY DATA */
#define INITIALIZE_MONTY {NULL, NULL, STACK_MODE, EXIT_SUCCESS, NULL}

/* ------------------------------------------------------------------------- */
/*                 MONTY - DATA STRUCTURES                                   */
/* ------------------------------------------------------------------------- */

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

/**
 * struct monty_s - a data structure used to hold necessary data for
 *                  opcode handlers, and memory cleanup.
 * @cur_opcode: current opcode
 * @cur_oparg: current opcode argument
 * @last_node: pointer to the last node in the stack
 * @mode: used to indicate the mode of the monty data (stack or queue)
 * @exit_status: used to hold the exit status of the monty program
 *
 * Description: this data structure is used to share data among the
 *              main function and other functions.
 */
typedef struct monty_s
{
	char *cur_opcode;
	char *cur_oparg;
	int mode;
	int exit_status;
	stack_t *last_node;
} monty_t;

/* ------------------------------------------------------------------------- */
/*                 MONTY - GENERAL UTILS                                     */
/* ------------------------------------------------------------------------- */
int read_line(int fd, char **line_buff, int *line_size);
char *get_file_line(char *start, char **save_ptr);
void remove_comment(char *line);
int is_integer(char *str);


/* ------------------------------------------------------------------------- */
/*                 MONTY - CLEANUP UTILS                                     */
/* ------------------------------------------------------------------------- */
void free_stack(stack_t *top);


/* ------------------------------------------------------------------------- */
/*                 MONTY - OPCODES UTILS                                     */
/* ------------------------------------------------------------------------- */
int get_stack_len(stack_t *top);
void push_to_top(stack_t **top, stack_t *new_stack);
void push_to_last(stack_t **top, stack_t *new_stack);


/* ------------------------------------------------------------------------- */
/*                 MONTY - OPCODE HANDLERS                                   */
/* ------------------------------------------------------------------------- */
/* 1 */
void push(stack_t **top, unsigned int lnum);
void pall(stack_t **top, unsigned int lnum);
void pint(stack_t **top, unsigned int lnum);
void pop(stack_t **top, unsigned int lnum);
void swap(stack_t **top, unsigned int lnum);

/* 2 */
void nop(stack_t **top, unsigned int lnum);
void add_opcode(stack_t **top, unsigned int lnum);
void sub_opcode(stack_t **top, unsigned int lnum);
void div_opcode(stack_t **top, unsigned int lnum);
void mul_opcode(stack_t **top, unsigned int lnum);

/* 3 */
void mod_opcode(stack_t **top, unsigned int lnum);
void pchar(stack_t **top, unsigned int lnum);
void pstr(stack_t **top, unsigned int lnum);
void rotl(stack_t **top, unsigned int lnum);
void rotr(stack_t **top, unsigned int lnum);

/* 4 */
void change_to_stack(stack_t **top, unsigned int lnum);
void change_to_queue(stack_t **top, unsigned int lnum);


/* ------------------------------------------------------------------------- */
/*                 MONTY - MAIN                                              */
/* ------------------------------------------------------------------------- */
void get_opcode_oparg(char *line_buf);
void (*get_opcode_function(char *opcode))(stack_t **top, unsigned int line);


/* ------------------------------------------------------------------------- */
/*                 MONTY - GLOBAL VAIRABLES                                  */
/* ------------------------------------------------------------------------- */
extern monty_t monty;

/* ------------------------------------------------------------------------- */
#endif

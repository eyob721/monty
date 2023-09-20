#ifndef MONTY_H
#define MONTY_H

/* ------------------------------------------------------------------------- */
/*                 MONTY - HEADERS AND MACROS                       */
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
#define OPEN_FILE_ERR -1

/* READ SYSTEM CALL CONSTANTS */
#define READ_EOF 0
#define READ_ERR -1

/* BUFFER CONSTANTS */
#define FILE_BUF_SIZE 512


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
 * struct queue_s - doubly linked list representation of a queue of
 *                  opcodes and their arguments
 * @opcode: the opcode
 * @oparg: argument of the opcode
 * @line: the line number of the opcode instruction
 * @prev: pointer to the previous node in the queue
 * @next: pointer to the next node in the queue
 *
 * Description: this data structure is used to queue the instructions from
 *              each line of the file.
 */
typedef struct queue_s
{
	char *opcode;
	char *oparg;
	unsigned int line;
	struct queue_s *prev;
	struct queue_s *next;
} queue_t;

/**
 * struct monty_s - a data structure used to hold necessary data for
 *                  opcode handlers, and memory cleanup.
 * @fd: file discriptor
 * @front: pointer to the front of the queue
 * @rear: pointer to the rear of the queue
 * @file_buf: pointer to the file buffer
 * @buf_size: size of the file buffer
 *
 * Description: this data structure is used to share data among the
 *              main function and other functions.
 */
typedef struct monty_s
{
	int fd;
	queue_t *front;
	queue_t *rear;
	char *file_buf;
	int buf_size;
} monty_t;

/* ------------------------------------------------------------------------- */
/*                 MONTY UTILS - GENERAL                                     */
/* ------------------------------------------------------------------------- */
int read_file(int fd, char **buf, int *size);
char *get_file_line(char *start, char **save_ptr);
int is_integer(char *str);


/* ------------------------------------------------------------------------- */
/*                 MONTY UTILS - QUEUE                                       */
/* ------------------------------------------------------------------------- */
void build_queue(void);
queue_t *enqueue(char *opcode, char *oparg, unsigned int lno);
queue_t *dequeue(void);
void print_node(queue_t *node);
void print_queue(void);


/* ------------------------------------------------------------------------- */
/*                 MONTY UTILS - MEMORY                                      */
/* ------------------------------------------------------------------------- */
void free_stack(stack_t *top);
void free_queue(void);
void free_monty(void);


/* ------------------------------------------------------------------------- */
/*                 MONTY - OPCODES                                           */
/* ------------------------------------------------------------------------- */
void push(stack_t **top, unsigned int line_number);


/* ------------------------------------------------------------------------- */
/*                 MONTY - MAIN                                              */
/* ------------------------------------------------------------------------- */
void (*get_opcode_function(char *opcode))(stack_t **top, unsigned int line);


/* ------------------------------------------------------------------------- */
/*                 MONTY - GLOBAL                                            */
/* ------------------------------------------------------------------------- */
/* MONTY DATA */
extern monty_t monty;

/* ------------------------------------------------------------------------- */
#endif

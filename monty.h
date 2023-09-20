#ifndef MONTY_H
#define MONTY_H

/* ------------------------------------------------------------------------- */
/*                 MONTY - HEADERS, GLOBAL, AND CONSTANTS                    */
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
#define BUF_SIZE 512

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
 * @prev: pointer to the previous node in the queue
 * @next: pointer to the next node in the queue
 *
 * Description: this data structure is used to queue the instructions in each
 * line of the file
 */
typedef struct queue_s
{
	char *opcode;
	char *oparg;
	struct queue_s *prev;
	struct queue_s *next;
} queue_t;


/* ------------------------------------------------------------------------- */
/*                 MONTY UTILS - GENERAL                                     */
/* ------------------------------------------------------------------------- */
int read_file(int fd, char **buf, int *size);


/* ------------------------------------------------------------------------- */
/*                 MONTY UTILS - QUEUE                                       */
/* ------------------------------------------------------------------------- */
queue_t *enqueue(queue_t **front, queue_t **rear, char *opcode, char *oparg);
void print_queue(queue_t *front);

/* ------------------------------------------------------------------------- */
/*                 MONTY UTILS - MEMORY                                      */
/* ------------------------------------------------------------------------- */
void free_queue(queue_t *front);


/* ------------------------------------------------------------------------- */
/*                 MONTY UTILS - MAIN                                        */
/* ------------------------------------------------------------------------- */
void build_queue(queue_t **front, queue_t **rear, char *file_buf);

/* ------------------------------------------------------------------------- */
#endif

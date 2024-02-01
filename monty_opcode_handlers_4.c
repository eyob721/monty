#include "monty.h"

/**
 * _stack - handles the stack opcode, which changes the mode of the monty data
 *          stack to stack mode (LIFO)
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void _stack(stack_t **top, unsigned int lnum)
{
	(void)top;
	(void)lnum;
	monty.mode = STACK_MODE;
	monty.exit_status = EXIT_SUCCESS;
}

/**
 * _queue - handles the queue opcode, which changes the mode of the monty data
 *          stack to queue mode (FIFO)
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void _queue(stack_t **top, unsigned int lnum)
{
	(void)top;
	(void)lnum;
	monty.mode = QUEUE_MODE;
	monty.exit_status = EXIT_SUCCESS;
}

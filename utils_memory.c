#include "monty.h"

/**
 * free_stack - frees a stack_t doubly linked list
 * @top: pointer to the top of the stack
 *
 * Return: void
 */
void free_stack(stack_t *top)
{
	stack_t *tmp;

	while (top != NULL)
	{
		tmp = top;
		top = top->prev;
		tmp->prev = tmp->next = NULL;
		free(tmp);
	}
}

/**
 * free_queue - frees a queue_t doubly linked list.
 *
 * Return: void
 */
void free_queue(void)
{
	queue_t *tmp;

	while (monty.front != NULL)
	{
		tmp = monty.front;
		monty.front = monty.front->next;
		tmp->prev = tmp->next = NULL;
		free(tmp);
	}
}

/**
 * free_monty - frees the monty data structure
 *
 * Return: void
 */
void free_monty(void)
{
	close(monty.fd);
	free_queue();
	free(monty.file_buf);
}


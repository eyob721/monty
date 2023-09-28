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

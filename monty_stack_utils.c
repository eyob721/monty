#include "monty.h"

/**
 * reverse_stack - reverses the stack
 * @top: double pointer to the stack
 *
 * Return: void
 */
void reverse_stack(stack_t **top)
{
	stack_t *top_node, *node;

	if (top == NULL || *top == NULL)
		return;

	top_node = *top;
	*top = NULL;
	while (top_node != NULL)
	{
		node = top_node;
		top_node = top_node->prev;
		/* Push on a new stack */
		node->prev = *top;
		node->next = NULL;
		if (*top != NULL)
			(*top)->next = node;
		*top = node;
	}
}

#include "monty.h"

/**
 * push_to_top - function that inserts an element from the top (the front)
 * @top: double pointer to the top of the stack (or queue)
 * @new_node: the new node to be inserted
 *
 * Return: void
 * Description: This is the insertion operation used in stack mode
 */
void push_to_top(stack_t **top, stack_t *new_node)
{
	/* Add the new stack node on the top of the stack */
	new_node->prev = *top;
	new_node->next = NULL;

	if (*top != NULL)
		(*top)->next = new_node;
	if (*top == NULL)
		monty.bottom = new_node;

	*top = new_node;
}

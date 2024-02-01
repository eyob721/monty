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

/**
 * push_to_last - function that inserts an element from the last (the end)
 * @top: double pointer to the top of the stack (or queue)
 * @new_node: the new node to be inserted
 *
 * Return: void
 * Description: This is the insertion operation used in queue mode
 */
void push_to_last(stack_t **top, stack_t *new_node)
{
	/* Add the new stack node at the last node of the stack */
	new_node->prev = NULL;
	new_node->next = monty.bottom;

	if (monty.bottom != NULL)
		monty.bottom->prev = new_node;
	if (monty.bottom == NULL)
		*top = new_node;

	monty.bottom = new_node;
}

/**
 * get_stack_len - returns the length of the stack or queue
 * @top: pointer to the top of the stack
 *
 * Return: length of the stack (i.e. number of elements in the stack)
 */
int get_stack_len(stack_t *top)
{
	int stack_len = 0;

	while (top != NULL)
	{
		++stack_len;
		top = top->prev;
	}
	return (stack_len);
}

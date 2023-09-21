#include "monty.h"

/**
 * get_stack_len - returns the len (number of elements) of the stack.
 * @top: pointer to the top of the stack
 *
 * Return: len of the stack (i.e. number of elements in the stack)
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

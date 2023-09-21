#include "../../monty.h"

/**
 * rotr - handles the rotr opcode
 * @top: double pointer to the top of the stack
 * @lnum: current line number in the file
 *
 * Return: void
 */
void rotr(stack_t **top, unsigned int lnum)
{
	stack_t *top_node, *second_top, *last_node, *second_last, *tmp;

	(void)lnum;
	if (top == NULL || *top == NULL)
		return;

	/* Determine the nodes */
	top_node = *top;
	second_top = top_node->prev;
	last_node = top_node;
	while (last_node->prev != NULL)
		last_node = last_node->prev;
	second_last = last_node->next;
	/* For stacks with 2 nodes, swap second_top and second_last variables */
	if (top_node == second_last && last_node == second_top)
		SWAP_VALUES(second_last, second_top, tmp);

	/* Move the top to the bottom */
	top_node->prev = NULL;
	top_node->next = second_last;
	if (second_last != NULL)
		second_last->prev = top_node;

	/* Move the bottom to the top */
	last_node->prev = second_top;
	last_node->next = NULL;
	if (second_top != NULL)
		second_top->next = last_node;

	/* Update top */
	*top = last_node;

	monty.exit_status = EXIT_SUCCESS;
}


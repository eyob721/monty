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
 * @front: pointer to the front of the queue
 *
 * Return: void
 */
void free_queue(queue_t *front)
{
	queue_t *tmp;

	while (front != NULL)
	{
		tmp = front;
		front = front->next;
		tmp->prev = tmp->next = NULL;
		free(tmp);
	}
}

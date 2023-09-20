#include "monty.h"

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
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
	}
}

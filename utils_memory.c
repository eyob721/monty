#include "monty.h"

/**
 * free_queue - frees a queue_t doubly linked list.
 *
 * Return: void
 */
void free_queue()
{
	queue_t *tmp;

	while (monty.front != NULL)
	{
		tmp = monty.front;
		monty.front = monty.front->next;
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
	}
}

/**
 * free_monty - frees the monty data structure
 *
 * Return: void
 */
void free_monty()
{
	close(monty.fd);
	free_queue();
	free(monty.file_buf);
}

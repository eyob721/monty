#include "monty.h"

/**
 * enqueue - a function that inserts a new node in the queue, from the rear
 * @front: double pointer to the front of the queue
 * @rear: double pointer to the rear of the queue
 * @opcode: the opcode of the new node
 * @oparg: the oparg of the new node
 *
 * Return: pointer to the new node, or NULL if failure occurs
 */
queue_t *enqueue(queue_t **front, queue_t **rear, char *opcode, char *oparg)
{
	queue_t *new_node = NULL;

	if (front == NULL || rear == NULL || opcode == NULL || *opcode == '\0')
		return (NULL);

	/* Allocate memory */
	new_node = malloc(sizeof(queue_t));
	if (new_node == NULL)
		return (NULL);

	/* Build the new node */
	new_node->opcode = opcode;
	new_node->oparg = oparg;
	new_node->prev = *rear;
	new_node->next = NULL;

	/* Insert the new node into the queue, from the rear */
	if (*front == NULL) /* in case of an empty queue */
		*front = new_node;
	if (*rear != NULL)
		(*rear)->next = new_node;
	*rear = new_node;
	return (new_node);
}

#include "monty.h"

/**
 * enqueue - a function that inserts a new node in the queue, from the rear
 * @front: double pointer to the front of the queue
 * @rear: double pointer to the rear of the queue
 * @opcode: the opcode of the new node
 * @oparg: the oparg of the new node
 * @line: the line number of the opecode instruction
 *
 * Return: pointer to the new node, or NULL if failure occurs
 */
queue_t *enqueue(queue_t **front, queue_t **rear,
		char *opcode, char *oparg, int line)
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
	new_node->line = line;
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

/**
 * dequeue - a function that removes and returns the front node in a queue
 * @front: double pointer to the front of the queue
 * @rear: double pointer to the rear of the queue
 *
 * Return: address of the front node, or NULL if the queue is empty or if
 *         failure occurs.
 * Description: In cases where the queue has only one node in it, then the
 *              rear pointer must become NULL. This will make the queue empty.
 *              The front node already is assigned NULL, when advance it.
 */
queue_t *dequeue(queue_t **front, queue_t **rear)
{
	queue_t *tmp = NULL;

	if (front == NULL || *front == NULL)
		return (NULL);
	tmp = *front;
	*front = (*front)->next; /* Advance front to the next node */
	if (*front != NULL)
		(*front)->prev = NULL;
	if (tmp == *rear) /* in case tmp is the only node in the queue */
		*rear = NULL;
	tmp->prev = tmp->next = NULL;
	return (tmp);
}

/**
 * print_queue - prints the opcodes and opargs in a queue
 * @front: points to the front of the queue
 *
 * Return: void
 */
void print_queue(queue_t *front)
{
	while (front != NULL)
	{
		_printf("line: [%d] opcode: [%s] oparg: [%s]\n",
				front->line, front->opcode, front->oparg);
		front = front->next;
	}
}

/**
 * print_node - prints the line number, the opcode and the oparg of a node
 * @node: pointer to a node in the queue
 *
 * Return: void
 */
void print_node(queue_t *node)
{
	if (node != NULL)
		_printf("line:[%d] opcode: [%s] oparg: [%s]\n",
				node->line, node->opcode, node->oparg);
}

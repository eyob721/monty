#include "monty.h"

/**
 * build_queue - builds a queue of instructions from the file buffer.
 * @front: double pointer to the front of the queue
 * @rear: double pointer to the rear of the queue
 * @file_buf: pointer to the file buffer
 *
 * Return: void
 */
void build_queue(queue_t **front, queue_t **rear, char *file_buf)
{
	int line_no = 1;
	char *line = NULL, *opcode = NULL, *oparg = NULL;
	char *line_save = NULL, *op_save = NULL;

	if (file_buf == NULL)
		return;
	line = get_file_line(file_buf, &line_save);
	while (line != NULL)
	{
		opcode = _strtok_r(line, " ", &op_save);
		oparg = _strtok_r(NULL, " ", &op_save);
		enqueue(front, rear, opcode, oparg, line_no);
		line = get_file_line(NULL, &line_save);
		++line_no;
	}
}

/**
 * enqueue - a function that inserts a new node in the queue, from the rear
 * @front: double pointer to the front of the queue
 * @rear: double pointer to the rear of the queue
 * @opcode: the opcode of the new node
 * @oparg: the oparg of the new node
 * @line_no: the line number of the opecode instruction
 *
 * Return: pointer to the new node, or NULL if failure occurs
 */
queue_t *enqueue(queue_t **front, queue_t **rear,
		char *opcode, char *oparg, unsigned int line_no)
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
	new_node->line = line_no;
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
 * Description:
 *     - In cases where the queue has only one node in it, then the
 *       rear pointer must become NULL. So that to make the queue empty.
 *     - As for the front node it will be assigned NULL, when we advance it.
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

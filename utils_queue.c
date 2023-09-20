#include "monty.h"

/**
 * build_queue - builds a queue of instructions from the file buffer.
 * @front: double pointer to the front of the queue
 * @rear: double pointer to the rear of the queue
 * @file_buf: pointer to the file buffer
 *
 * Return: void
 */
void build_queue()
{
	int line_no = 1;
	char *line = NULL, *opcode = NULL, *oparg = NULL;
	char *line_save = NULL, *op_save = NULL;

	if (monty.file_buf == NULL)
		return;
	line = get_file_line(monty.file_buf, &line_save);
	while (line != NULL)
	{
		opcode = _strtok_r(line, " ", &op_save);
		oparg = _strtok_r(NULL, " ", &op_save);
		enqueue(opcode, oparg, line_no);
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
 * @line: the line number of the opecode instruction
 *
 * Return: pointer to the new node, or NULL if failure occurs
 */
queue_t *enqueue(char *opcode, char *oparg, unsigned int lno)
{
	queue_t *new_node = NULL;

	if (opcode == NULL || *opcode == '\0')
		return (NULL);

	/* Allocate memory */
	new_node = malloc(sizeof(queue_t));
	if (new_node == NULL)
		return (NULL);

	/* Build the new node */
	new_node->opcode = opcode;
	new_node->oparg = oparg;
	new_node->line = lno;
	new_node->prev = monty.rear;
	new_node->next = NULL;

	/* Insert the new node into the queue, from the rear */
	if (monty.front == NULL) /* in case of an empty queue */
		monty.front = new_node;
	if (monty.rear != NULL)
		(monty.rear)->next = new_node;
	monty.rear = new_node;
	return (new_node);
}

/**
 * dequeue - a function that removes and returns the front node in a queue
 *
 * Return: address of the front node, or NULL if the queue is empty or if
 *         failure occurs.
 * Description: In cases where the queue has only one node in it, then the
 *              rear pointer must become NULL. This will make the queue empty.
 *              The front node already is assigned NULL, when advance it.
 */
queue_t *dequeue()
{
	queue_t *tmp = NULL;

	if (monty.front == NULL)
		return (NULL);
	tmp = monty.front;
	monty.front = monty.front->next; /* Advance front to the next node */
	if (monty.front != NULL)
		monty.front->prev = NULL;
	if (tmp == monty.rear) /* in case tmp is the only node in the queue */
		monty.rear = NULL;
	tmp->prev = tmp->next = NULL;
	return (tmp);
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

/**
 * print_queue - prints the opcodes and opargs in a queue
 * @front: points to the front of the queue
 *
 * Return: void
 */
void print_queue()
{
	while (monty.front != NULL)
	{
		_printf("line: [%d] opcode: [%s] oparg: [%s]\n",
				monty.front->line, monty.front->opcode, monty.front->oparg);
		monty.front = monty.front->next;
	}
}

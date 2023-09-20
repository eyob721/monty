#include "../monty.h"

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

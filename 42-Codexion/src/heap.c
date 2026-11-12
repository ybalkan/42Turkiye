/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 22:02:12 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:30:26 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

int	heap_init(t_heap *heap, int capacity)
{
	heap->data = (t_request *)malloc(sizeof(t_request) * capacity);
	if (!heap->data)
		return (1);
	heap->size = 0;
	heap->capacity = capacity;
	return (0);
}

void	heap_destroy(t_heap *heap)
{
	free(heap->data);
	heap->data = NULL;
	heap->size = 0;
	heap->capacity = 0;
}

int	heap_push(t_heap *heap, t_request req, t_sched_type type)
{
	if (heap->size >= heap->capacity)
		return (1);
	heap->data[heap->size] = req;
	heap_sift_up(heap, heap->size, type);
	heap->size++;
	return (0);
}

t_request	heap_pop(t_heap *heap, t_sched_type type)
{
	t_request	top;

	memset(&top, 0, sizeof(t_request));
	if (heap->size == 0)
		return (top);
	top = heap->data[0];
	heap->size--;
	if (heap->size > 0)
	{
		heap->data[0] = heap->data[heap->size];
		heap_sift_down(heap, 0, type);
	}
	return (top);
}

t_request	*heap_peek(t_heap *heap)
{
	if (heap->size == 0)
		return (NULL);
	return (&heap->data[0]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybalkan <ybalkan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 19:30:03 by ybalkan           #+#    #+#             */
/*   Updated: 2026/11/07 00:30:14 by ybalkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/codexion.h"

int	compare_requests(t_request *a, t_request *b, t_sched_type type)
{
	if (type == CODEX_EDF)
	{
		if (a->deadline != b->deadline)
			return (a->deadline < b->deadline);
		return (a->seq < b->seq);
	}
	if (type == CODEX_LIFO)
		return (a->seq > b->seq);
	return (a->seq < b->seq);
}

void	heap_swap(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heap_sift_up(t_heap *heap, int index, t_sched_type type)
{
	int	parent;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!compare_requests(&heap->data[index],
				&heap->data[parent], type))
			break ;
		heap_swap(&heap->data[index], &heap->data[parent]);
		index = parent;
	}
}

void	heap_sift_down(t_heap *heap, int index, t_sched_type type)
{
	int	child;
	int	left;
	int	right;

	while (1)
	{
		left = index * 2 + 1;
		right = left + 1;
		if (left >= heap->size)
			break ;
		child = left;
		if (right < heap->size
			&& compare_requests(&heap->data[right],
				&heap->data[left], type))
			child = right;
		if (!compare_requests(&heap->data[child],
				&heap->data[index], type))
			break ;
		heap_swap(&heap->data[child], &heap->data[index]);
		index = child;
	}
}

int	heap_remove(t_heap *heap, int coder_id, t_sched_type type)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->data[i].coder_id == coder_id)
		{
			heap->size--;
			if (i >= heap->size)
				return (1);
			heap->data[i] = heap->data[heap->size];
			if (i > 0 && compare_requests(&heap->data[i],
					&heap->data[(i - 1) / 2], type))
				heap_sift_up(heap, i, type);
			else
				heap_sift_down(heap, i, type);
			return (1);
		}
		i++;
	}
	return (0);
}

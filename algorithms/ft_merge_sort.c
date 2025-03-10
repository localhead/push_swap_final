/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbagg <mbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:20:08 by mbagg             #+#    #+#             */
/*   Updated: 2022/03/10 18:20:09 by mbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	ft_split_list(t_list **stack_a, t_list **stack_b,
							t_status *status)
{
	unsigned long long	i;
	unsigned long long	count;

	i = 0;
	count = (status->max - status->min) / 2;
	while (i < count)
	{
		ft_push(stack_a, stack_b, 'b');
		i++;
	}
	if ((status->max - status->min) % 2)
		ft_push(stack_a, stack_b, 'b');
}

static void	ft_sort_lists(t_list **stack_a, t_list **stack_b)
{
	if ((*stack_a)->value > ((*stack_a)->next)->value
		&& (*stack_b)->value > ((*stack_b)->next)->value)
		ft_both_swap(stack_a, stack_b);
	else if ((*stack_a)->value > ((*stack_a)->next)->value)
		ft_swap(*stack_a, 'a');
	else if ((*stack_b)->value > ((*stack_b)->next)->value)
		ft_swap(*stack_b, 'b');
}

static void	ft_simple_sort_plus(t_list **stack_a, t_list **stack_b)
{
	if (ft_is_swap(stack_a) && ft_is_swap(stack_b))
		ft_both_swap(stack_a, stack_b);
	if (ft_is_swap(stack_a))
		ft_swap(*stack_a, 'a');
	if (ft_is_swap(stack_b))
		ft_swap(*stack_b, 'b');
	if (ft_is_rotate(stack_a) && ft_is_rotate(stack_b))
		ft_both_rotate(stack_a, stack_b);
	if (ft_is_rotate(stack_a))
		ft_rotate(stack_a, 'a');
	if (ft_is_rotate(stack_b))
		ft_reverse_rotate(stack_b, 'b');
	if (ft_is_reverse_rotate(stack_a) && ft_is_reverse_rotate(stack_b))
		ft_both_reverse_rotate(stack_a, stack_b);
	if (ft_is_reverse_rotate(stack_a))
		ft_reverse_rotate(stack_a, 'a');
	if (ft_is_reverse_rotate(stack_b))
		ft_reverse_rotate(stack_b, 'b');
}

static void	ft_merge_stacks(t_list **stack_a, t_list **stack_b)
{
	long long	index;

	index = (*stack_a)->index;
	while ((*stack_b) && (*stack_a)->index == index)
	{
		if ((*stack_b)->value < (*stack_a)->value)
			ft_push(stack_b, stack_a, 'a');
		(*stack_a)->index = -1;
		ft_rotate(stack_a, 'a');
	}
	while (*stack_b)
	{
		ft_push(stack_b, stack_a, 'a');
		(*stack_a)->index = -1;
		ft_rotate(stack_a, 'a');
	}
	while ((*stack_a)->index == index)
	{
		(*stack_a)->index = -1;
		ft_rotate(stack_a, 'a');
	}
}

/*
 * Функция умеет обрабатывать стеки до 6 элементов включительно.
 * t_list **stack_a - стек, который необходимо отсортировать;
 * В основе принципа сортировки лежит алгоритм слияния (merge sort).
 * Можно было бы написать общий случай сортировки, но мы не стали.
 * Это усложнило бы код в разы.
 */

void	ft_merge_sort(t_list **stack_a, t_list **stack_b, t_status *status)
{
	ft_split_list(stack_a, stack_b, status);
	if ((status->max - status->min) < 4)
		ft_sort_lists(stack_a, stack_b);
	else
		ft_simple_sort_plus(stack_a, stack_b);
	ft_merge_stacks(stack_a, stack_b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:30:58 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/10 13:39:06 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_free(t_data *data)
{
	int	n;

	usleep(data->t_eat + data->t_sleep + M);
	free(data->hunger_count);
	free(data->number_meal);
	n = 0;
	while (n < data->len)
	{
		pthread_mutex_destroy(data->mutex[n]);
		n++;
	}
	free(data->mutex);
	free(data->thread);
	free(data->access);
	return ;
}

void	error_out(char *str, t_data *data)
{
	(void)data;
	write(2, str, ft_strlen(str));
	all_free(data);
}

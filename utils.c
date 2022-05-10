/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:26:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/05/10 12:20:06 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(t_access *access)
{
	int				result;
	struct timeval	time;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000 + time.tv_usec / 1000) - access->start_time;
	return (result);
}

void	print_msg(t_access *access, int msg)
{
	pthread_mutex_lock(access->speak);
	ft_putnbr(timestamp(access));
	write(1, " ", 1);
	ft_putnbr(access->num);
	write(1, " ", 1);
	if (msg == MSG_FORK)
		write(1, STR_FORK, 17);
	else if (msg == MSG_EAT)
		write(1, STR_EAT, 10);
	else if (msg == MSG_SLEEP)
		write(1, STR_SLEEP, 12);
	else if (msg == MSG_THINK)
		write(1, STR_THINK, 12);
	else if (msg == MSG_DIED)
		write(1, STR_DIED, 5);
	if (msg != MSG_DIED)
		pthread_mutex_unlock(access->speak);
}

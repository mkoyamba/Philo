/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:26:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/06 12:04:49 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_tempo(int timeout, int time_stamp, t_access *access)
{
	while (timestamp(access) < time_stamp + timeout)
		usleep(100);
}

int	timestamp(t_access *access)
{
	int				result;
	struct timeval	time;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000 + time.tv_usec / 1000) - access->start_time;
	return (result);
}

int	first_timestamp(void)
{
	int				result;
	struct timeval	time;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
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

int	eat_end(t_access *access)
{
	pthread_mutex_lock(access->death_check_mute);
	*(access->last_eat) = timestamp(access);
	pthread_mutex_unlock(access->death_check_mute);
	pthread_mutex_lock(access->nb_meal_mute);
	*(access->meal) += 1;
	pthread_mutex_unlock(access->nb_meal_mute);
	print_msg(access, MSG_EAT);
	time_tempo(access->t_eat, timestamp(access), access);
	pthread_mutex_unlock(access->fork_0);
	pthread_mutex_unlock(access->fork_1);
	return (1);
}

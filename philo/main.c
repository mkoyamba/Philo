/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:34:07 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/10/06 14:44:49 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_start(char *str, pthread_t **thread, pthread_mutex_t **mutex)
{
	if (thread)
		free(thread);
	if (mutex)
		free(mutex);
	write(2, "philo: ", 7);
	write(2, str, ft_strlen(str));
	exit(1);
}

static char	first_char(char *str)
{
	size_t	n;

	n = 0;
	while (str[n] == ' ' || str[n] == '\t' || str[n] == '\n'
		|| str[n] == '\r' || str[n] == '\v' || str[n] == '\f')
		n++;
	if (str[n] == '+' || str[n] == '-')
		n++;
	return (str[n]);
}

static int	check(int ac, char **av)
{
	int	n;
	int	ck;

	n = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (n < ac)
	{
		ck = ft_atoi(av[n]);
		if ((ck == 0 && first_char(av[n]) != '0') || ck < 1)
			return (0);
		n++;
	}
	return (1);
}

static void	alloc_init(t_data *data, int ac, char **av)
{
	int	n;

	n = 0;
	if (!check(ac, av))
		error_start(E_ARG, NULL, NULL);
	data->len = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->t_must = 0;
	if (ac == 6 && ft_atoi(av[5]) > 0)
		data->t_must = ft_atoi(av[5]);
	data->thread = malloc(data->len * sizeof(pthread_t *));
	if (!data->thread)
		error_start(E_ALLOC, NULL, NULL);
	data->mutex = malloc(data->len * sizeof(pthread_mutex_t *));
	if (!data->mutex)
		error_start(E_ALLOC, data->thread, NULL);
	while (n < data->len)
	{
		data->thread[n] = NULL;
		data->mutex[n] = NULL;
		n++;
	}
	data->access = NULL;
}

static void	destroy_mutexes(
				pthread_mutex_t *speak, pthread_mutex_t *nb_meal_mute,
				pthread_mutex_t *death_check_mute)
{
	pthread_mutex_destroy(speak);
	pthread_mutex_destroy(nb_meal_mute);
	pthread_mutex_destroy(death_check_mute);
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_mutex_t	speak;
	pthread_mutex_t	nb_meal_mute;
	pthread_mutex_t	death_check_mute;

	pthread_mutex_init(&speak, NULL);
	pthread_mutex_init(&nb_meal_mute, NULL);
	pthread_mutex_init(&death_check_mute, NULL);
	alloc_init(&data, argc, argv);
	data.hunger_count = malloc(data.len * sizeof(int));
	if (!data.hunger_count)
	{
		destroy_mutexes(&speak, &nb_meal_mute, &death_check_mute);
		error_start(E_ALLOC, data.thread, data.mutex);
	}
	data.number_meal = malloc(data.len * sizeof(int));
	if (!data.number_meal)
	{
		destroy_mutexes(&speak, &nb_meal_mute, &death_check_mute);
		free(data.hunger_count);
		error_start(E_ALLOC, data.thread, data.mutex);
	}
	data.access = malloc(data.len * sizeof(t_access));
	if (!data.access)
	{
		destroy_mutexes(&speak, &nb_meal_mute, &death_check_mute);
		free(data.hunger_count);
		free(data.number_meal);
		error_start(E_ALLOC, data.thread, data.mutex);
	}
	data.stop = malloc(data.len * sizeof(int));
	if (!data.stop)
	{
		destroy_mutexes(&speak, &nb_meal_mute, &death_check_mute);
		free(data.hunger_count);
		free(data.number_meal);
		free(data.access);
		error_start(E_ALLOC, data.thread, data.mutex);
	}
	init(&data);
	philo(&data, &speak, &nb_meal_mute, &death_check_mute);
	pthread_mutex_destroy(&speak);
	return (0);
}

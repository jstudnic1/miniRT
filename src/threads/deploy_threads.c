/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deploy_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 19:51:28 by smelicha          #+#    #+#             */
/*   Updated: 2025-03-15 19:51:28 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <pthread.h>
#include <unistd.h>


int	create_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_THREADS)
	{
		pthread_mutex_init(&data->cores[i].state_mtx, NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	return (0);
}

void	*dummy_function(t_core *core)
{
	while (true)
	{
		pthread_mutex_lock(&core->state_mtx);
		if (core->state == run)
		{
			pthread_mutex_lock(core->print);
			printf("Hello from thread %i!\n", core->id);
			pthread_mutex_unlock(core->print);
		}
		else if (core->state == finish)
		{
			pthread_mutex_unlock(&core->state_mtx);
			break ;
		}
		pthread_mutex_unlock(&core->state_mtx);
		usleep(100000);
	}
	return (NULL);
}

void	init_cores_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_THREADS)
	{
		data->cores[i].id = i;
		data->cores[i].tid = 0;
		data->cores[i].x_start = 0;
		data->cores[i].x_end = 0;
		data->cores[i].y_start = 0;
		data->cores[i].y_end = 0;
		data->cores[i].print = &data->print;
		data->cores[i].state = stop;
		i++;
	}
}

void	change_cores_state(t_data *data, t_e_core_state new_state)
{
	int	i;

	i = 0;
	while (i < N_THREADS)
	{
		pthread_mutex_lock(&data->cores[i].state_mtx);
		data->cores[i].state = new_state;
		pthread_mutex_unlock(&data->cores[i].state_mtx);
		i++;
	}
}


int	deploy_threads(t_data *data)
{
	int	i;

	i = 0;
	create_mutexes(data);
	init_cores_data(data);
	while (i < N_THREADS)
	{
		pthread_create(&data->cores[i].tid, NULL, (void *)&dummy_function, &data->cores[i]);
		i++;
	}
	return (0);
}

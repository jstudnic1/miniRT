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
	printf("mutex before: %i\n", data->print.__data.__lock);
	pthread_mutex_init(&data->print, NULL);
	printf("mutex after: %i\n", data->print.__data.__lock);
	return (0);
}

void	*dummy_function(t_core *core)
{
	while (true)
	{
		pthread_mutex_lock(core->print);
		printf("Hello from thread %i!\n", core->id);
		pthread_mutex_unlock(core->print);
		sleep(2);
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

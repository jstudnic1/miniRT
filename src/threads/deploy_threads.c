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


int	create_mutexes(t_data *data)
{
	pthread_mutex_init(&data->print, NULL);
}

int	deploy_threads(t_data *data)
{

}

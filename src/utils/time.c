#include "../../incl/minirt.h"

uint64_t	ft_get_time(void)
{
	struct timeval	t;

	if (!gettimeofday(&t, NULL))
		return ((uint64_t)((t.tv_sec * 1000000) + t.tv_usec));
	else
		return (0);
}

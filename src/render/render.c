/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:30:08 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 22:25:53 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include "../../incl/render.h"
#include <stdint.h>
#include <math.h>

#define R_SHIFT 24
#define G_SHIFT 16
#define B_SHIFT 8

static uint32_t	rgb_to_int(t_rgb color)
{
	uint32_t	val;

	val = 0;
	val |= color.r << R_SHIFT;
	val |= color.g << G_SHIFT;
	val |= color.b << B_SHIFT;
	val |= 255;
	return (val);
}

typedef struct s_gpv
{
	t_rgb		pixel_value;
	t_ray		ray;
	t_collision	closest_hit;
	t_collision	current_hit;
	t_vector	view_dir;
	int			i;
}	t_gpv;

static t_rgb	gpv_cont(t_gpv *gpv, t_scene *scene)
{
	gpv->i = 0;
	while (gpv->i < scene->num_cylinders)
	{
		gpv->current_hit = cylinder_ray_collision(gpv->ray,
				scene->cylinders[gpv->i]);
		if (gpv->current_hit.hit && gpv->current_hit.t < gpv->closest_hit.t)
			gpv->closest_hit = gpv->current_hit;
		gpv->i++;
	}
	gpv->i = 0;
	if (gpv->closest_hit.hit)
	{
		gpv->view_dir = vec_sub(scene->camera.position, gpv->closest_hit.point);
		gpv->view_dir = vec_normalize(gpv->view_dir);
		gpv->pixel_value = calculate_lighting(gpv->closest_hit, scene,
				gpv->view_dir);
	}
	else
	{
		gpv->pixel_value.r = 0;
		gpv->pixel_value.g = 0;
		gpv->pixel_value.b = 0;
	}
	return (gpv->pixel_value);
}

/**
 * @brief Creates ray from camera through the pixel in a view plane,
 checks if it hits object and returns value of the pixel
 *
 * @param x
 * @param y
 * @param scene
 * @return t_rgb
 */
static t_rgb	get_pixel_val(int x, int y, t_scene *scene)
{
	t_gpv	gpv;

	gpv.ray = generate_primary_ray(x, y, scene);
	gpv.i = 0;
	gpv.pixel_value.b = 0;
	gpv.pixel_value.g = 0;
	gpv.pixel_value.r = 0;
	gpv.closest_hit.hit = false;
	gpv.closest_hit.t = RAY_T_MAX;
	while (gpv.i < scene->num_planes)
	{
		gpv.current_hit = plane_ray_collision(gpv.ray, scene->planes[gpv.i]);
		if (gpv.current_hit.hit && gpv.current_hit.t < gpv.closest_hit.t)
			gpv.closest_hit = gpv.current_hit;
		gpv.i++;
	}
	gpv.i = 0;
	while (gpv.i < scene->num_spheres)
	{
		gpv.current_hit = sphere_ray_collision(gpv.ray, scene->spheres[gpv.i]);
		if (gpv.current_hit.hit && gpv.current_hit.t < gpv.closest_hit.t)
			gpv.closest_hit = gpv.current_hit;
		gpv.i++;
	}
	return (gpv_cont(&gpv, scene));
}

void	render_loop(uint32_t *x, uint32_t *y, t_data *data)
{
	static t_rgb	color;

	while (*y < data->window.height)
	{
		while (*x < data->window.width)
		{
			color = get_pixel_val(*x, *y, data->scene);
			mlx_put_pixel(data->window.image, *x, *y, rgb_to_int(color));
			*x = *x + 1;
		}
		*x = 0;
		*y = *y + 1;
	}
	data->rendering = render_finished;
}

/**
 * @brief Takes scene and its objects, casts rays and puts pixel values
 to the mlx image, checks if the resolution changed and recomputes the image
 if true
 *
 * @param data
 * @return int
 */
int	render(t_data *data)
{
	static uint32_t	x;
	static uint32_t	y;

	if (data->rendering == render_finished)
		return (0);
	else if (data->rendering == render_restart)
	{
		x = 0;
		y = 0;
		data->rendering = render_run;
	}
	else if (data->rendering == render_run)
		render_loop(&x, &y, data);
	return (0);
}

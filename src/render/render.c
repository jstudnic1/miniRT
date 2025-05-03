/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:30:08 by smelicha          #+#    #+#             */
/*   Updated: 2025/05/03 11:57:37 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include "../../incl/render.h"
#include <stdint.h>
#include <math.h>

#define R_SHIFT 24
#define G_SHIFT 16
#define B_SHIFT 8

typedef struct s_gpr
{
	t_ray		ray;
	t_camera	*cam;
	t_vector	cam_forward;
	t_vector	world_up;
	t_vector	cam_right;
	t_vector	cam_up;
	t_vector	direction;
	double		aspect_ratio;
	double		fov_rad;
	double		fov_scale;
	double		ndc_x ;
	double		ndc_y;
	double		screen_x;
	double		screen_y;
}	t_gpr;

void	gpr_cont(t_gpr *gpr, int x, int y, t_scene *scene)
{
	normalize_vec(&gpr->cam_right);
	gpr->cam_up = cross_product(gpr->cam_right, gpr->cam_forward);
	normalize_vec(&gpr->cam_up);
	gpr->ndc_x = (2.0 * ((double)x + 0.5) / *scene->width_pixels - 1.0);
	gpr->ndc_y = (1.0 - 2.0 * ((double)y + 0.5) / *scene->height_pixels);
	gpr->screen_x = gpr->ndc_x * gpr->aspect_ratio * gpr->fov_scale;
	gpr->screen_y = gpr->ndc_y * gpr->fov_scale;
	gpr->direction = gpr->cam_forward;
	gpr->direction = vec_add(gpr->direction,
			vec_mult_scalar(gpr->cam_right, gpr->screen_x));
	gpr->direction = vec_add(gpr->direction,
			vec_mult_scalar(gpr->cam_up, gpr->screen_y));
	normalize_vec(&gpr->direction);
	gpr->ray.origin = gpr->cam->position;
	gpr->ray.direction = gpr->direction;
	gpr->ray.t_min = RAY_T_MIN;
	gpr->ray.t_max = RAY_T_MAX;
}

/**
 * @brief Generates a primary ray from the camera through a pixel.
 *
 * Basic explanation:
 * 1. Map pixel coordinates (x, y) from image space (0 to width/height)
 *    to normalized device coordinates (NDC) space (-1 to 1, usually).
 * 2. Map NDC coordinates to screen space, considering aspect ratio and FOV.
 * 3. Transform screen space coordinates to world space relative to the camera.
 * 4. Calculate the ray direction from camera origin to the world space point.
 * 5. Normalize the direction.
 *
 * NOTE: This implementation assumes a simple setup: camera at scene->camera.
 *       position,
 *       looking towards -Z axis relative to its orientation, with +Y as up.
 *       The camera orientation vector needs to define the look-at direction.
 *       A more robust implementation uses view matrices (lookAt matrix).
 *
 * @param x Pixel x-coordinate.
 * @param y Pixel y-coordinate.
 * @param scene Contains camera information.
 * @param window Contains image width and height.
 * @return t_ray The generated primary ray.
 */
t_ray	generate_primary_ray(int x, int y, t_scene *scene)
{
	t_gpr	gpr;

	gpr.cam = &scene->camera;
	gpr.aspect_ratio = (double)*scene->width_pixels
		/ (double)*scene->height_pixels;
	gpr.fov_rad = gpr.cam->fov * (M_PI / 180.0);
	gpr.fov_scale = tan(gpr.fov_rad / 2.0);
	gpr.cam_forward = gpr.cam->orientation;
	normalize_vec(&gpr.cam_forward);
	gpr.world_up.x = 0.0;
	gpr.world_up.y = 1.0;
	gpr.world_up.z = 0.0;
	gpr.cam_right = cross_product(gpr.cam_forward, gpr.world_up);
	if (vec_len2(gpr.cam_right) < EPSILON * EPSILON)
	{
		gpr.cam_right.x = 1.0;
		gpr.cam_right.y = 0.0;
		gpr.cam_right.z = 0.0;
	}
	gpr_cont(&gpr, x, y, scene);
	return (gpr.ray);
}

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
		normalize_vec(&gpv->view_dir);
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

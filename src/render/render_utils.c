/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:00 by jstudnic          #+#    #+#             */
/*   Updated: 2025/05/03 22:26:06 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

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
	gpr->cam_right = vec_normalize(gpr->cam_right);
	gpr->cam_up = cross_product(gpr->cam_right, gpr->cam_forward);
	gpr->cam_up = vec_normalize(gpr->cam_up);
	gpr->ndc_x = (2.0 * ((double)x + 0.5) / *scene->width_pixels - 1.0);
	gpr->ndc_y = (1.0 - 2.0 * ((double)y + 0.5) / *scene->height_pixels);
	gpr->screen_x = gpr->ndc_x * gpr->aspect_ratio * gpr->fov_scale;
	gpr->screen_y = gpr->ndc_y * gpr->fov_scale;
	gpr->direction = gpr->cam_forward;
	gpr->direction = vec_add(gpr->direction,
			vec_mult_scalar(gpr->cam_right, gpr->screen_x));
	gpr->direction = vec_add(gpr->direction,
			vec_mult_scalar(gpr->cam_up, gpr->screen_y));
	gpr->direction = vec_normalize(gpr->direction);
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
	gpr.cam_forward = vec_normalize(gpr.cam_forward);
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

/**
 * @brief Calculates a point along a ray at distance t.
 *
 * @param ray The ray.
 * @param t The distance along the ray.
 * @return t_vector The calculated point.
 */
t_vector	raypoint(t_ray ray, double t)
{
	t_vector	point;

	point = vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
	return (point);
}

/**
 * @brief Initializes a t_collision struct to default 'no hit' values.
 *
 * @return t_collision The initialized struct.
 */
t_collision	init_collision(void)
{
	t_collision	collision_data;

	collision_data.hit = false;
	collision_data.t = INFINITY;
	collision_data.normal = (t_vector){0, 0, 0};
	collision_data.point = (t_vector){0, 0, 0};
	collision_data.color = (t_rgb){0, 0, 0};
	return (collision_data);
}

/**
 * @brief Solves the quadratic equation at^2 + bt + c = 0.
 * Assumes coefficients and discriminant are pre-calculated in q.
 *
 * @param q Pointer to t_quadratic struct holding coefficients and results.
 * @return true If real roots exist.
 * @return false If no real roots or a is near zero.
 */
bool	solve_quadratic(t_quadratic *q)
{
	if (fabs(q->a) < EPSILON || q->discriminant < 0)
		return (false);
	q->sqrt_discriminant = sqrt(q->discriminant);
	q->t0 = (-q->b - q->sqrt_discriminant) / (2.0 * q->a);
	q->t1 = (-q->b + q->sqrt_discriminant) / (2.0 * q->a);
	return (true);
}

//<<<<<<< render_development_jstudnic
#include "../../incl/render.h"
#include <math.h>

// Placeholder for render_scene - will implement later
// void render_scene(t_data *data)
// {
//     // To be implemented
//     (void)data; // Prevent unused parameter warning for now
//     printf("Placeholder: render_scene called.\n");
// }

/**
 * @brief Renders the entire scene pixel by pixel (single-threaded).
 *
 * @param data Main data structure containing scene and window info.
 */
void render_scene(t_data *data)
{
    int			x, y;
    t_ray		ray;
    t_collision	closest_hit;
    t_collision current_hit;
    uint32_t	pixel_color;
    int			i;
    t_rgb       lit_color;
    t_vector    view_dir;

    if (!data || !data->scene || !data->window.mlx || !data->window.image)
    {
        fprintf(stderr, "Error: Invalid data for rendering.\n");
        return;
    }

    // Debug: Print camera basis vectors for the first pixel
    printf("\n=== Camera Debug Info ===\n");
    t_camera *cam = &data->scene->camera;
    printf("Camera Position: (%f, %f, %f)\n", cam->position.x, cam->position.y, cam->position.z);
    printf("Camera Orientation: (%f, %f, %f)\n", cam->orientation.x, cam->orientation.y, cam->orientation.z);
    printf("Camera FOV: %f\n", cam->fov);

    printf("Starting single-threaded render...\n");
    y = 0;
    while (y < (int)data->window.height)
    {
        x = 0;
        while (x < (int)data->window.width)
        {
            ray = generate_primary_ray(x, y, data->scene, &data->window);

            // Debug: Print ray info for center pixel
            if (x == data->window.width / 2 && y == data->window.height / 2) {
                printf("\n=== Center Pixel Ray Info ===\n");
                printf("Ray Origin: (%f, %f, %f)\n", ray.origin.x, ray.origin.y, ray.origin.z);
                printf("Ray Direction: (%f, %f, %f)\n", ray.direction.x, ray.direction.y, ray.direction.z);
            }

            // Initialize closest hit
            closest_hit.hit = false;
            closest_hit.t = RAY_T_MAX;

            // Check intersection with all planes
            for (i = 0; i < data->scene->num_planes; i++)
            {
                current_hit = plane_ray_collision(ray, data->scene->planes[i]);
                if (current_hit.hit && current_hit.t < closest_hit.t)
                {
                    closest_hit = current_hit;
                }
            }

            // Check intersection with all spheres
            for (i = 0; i < data->scene->num_spheres; i++)
            {
                current_hit = sphere_ray_collision(ray, data->scene->spheres[i]);
                if (current_hit.hit && current_hit.t < closest_hit.t)
                {
                    closest_hit = current_hit;
                }
            }

            // Check intersection with all cylinders
            for (i = 0; i < data->scene->num_cylinders; i++)
            {
                current_hit = cylinder_ray_collision(ray, data->scene->cylinders[i]);
                if (current_hit.hit && current_hit.t < closest_hit.t)
                {
                    closest_hit = current_hit;
                }
            }

            // Set pixel color based on intersection
            if (closest_hit.hit)
            {
                // Calculate view direction (from hit point to camera)
                view_dir = vec_sub(data->scene->camera.position, closest_hit.point);
                normalize_vec(&view_dir);

                // Calculate lighting
                lit_color = calculate_lighting(closest_hit, data->scene, view_dir);
                pixel_color = rgb_to_uint32(lit_color);
            }
            else
            {
                // Background color (black)
                pixel_color = rgb_to_uint32((t_rgb){0, 0, 0});
            }

            mlx_put_pixel(data->window.image, x, y, pixel_color);
            x++;
        }
        y++;
    }
    printf("Rendering complete.\n");
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
 * NOTE: This implementation assumes a simple setup: camera at scene->camera.position,
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
t_ray generate_primary_ray(int x, int y, t_scene *scene, t_window *window)
{
    t_ray ray;
    t_camera *cam = &scene->camera;
    double aspect_ratio = (double)window->width / (double)window->height;

    // Calculate field of view angle in radians
    double fov_rad = cam->fov * (M_PI / 180.0);
    double fov_scale = tan(fov_rad / 2.0);

    // --- Camera Basis Vector Calculation ---
    t_vector cam_forward = cam->orientation;
    normalize_vec(&cam_forward);

    // Calculate right vector using world up (0,1,0)
    t_vector world_up = {0.0, 1.0, 0.0};
    t_vector cam_right = cross_product(cam_forward, world_up);

    // Handle the case where camera is looking straight up/down
    if (vec_len2(cam_right) < EPSILON * EPSILON)
    {
        cam_right = (t_vector){1.0, 0.0, 0.0};
    }
    normalize_vec(&cam_right);

    // Calculate up vector from right and forward
    t_vector cam_up = cross_product(cam_right, cam_forward);
    normalize_vec(&cam_up);

    // --- Ray Direction Calculation ---
    // Convert pixel coordinates to NDC space (-1 to 1)
    double ndc_x = (2.0 * ((double)x + 0.5) / window->width - 1.0);
    double ndc_y = (1.0 - 2.0 * ((double)y + 0.5) / window->height);

    // Apply FOV scaling and aspect ratio correction
    double screen_x = ndc_x * aspect_ratio * fov_scale;
    double screen_y = ndc_y * fov_scale;

    // Calculate final direction vector
    t_vector direction = cam_forward;  // Start with forward direction
    direction = vec_add(direction, vec_mult_scalar(cam_right, screen_x));
    direction = vec_add(direction, vec_mult_scalar(cam_up, screen_y));

    normalize_vec(&direction);

    // Set up ray
    ray.origin = cam->position;
    ray.direction = direction;
    ray.t_min = RAY_T_MIN;
    ray.t_max = RAY_T_MAX;

    return ray;
//=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smelicha <smelicha@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:30:08 by smelicha          #+#    #+#             */
/*   Updated: 2025/04/14 14:49:12 by smelicha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <stdint.h>

#define R_SHIFT 24
#define G_SHIFT 16
#define B_SHIFT 8

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
	t_rgb	pixel_value;
	//TODO collision check with scene things and get the color of the
	//pixel based on the color of the thing it hit and light or the color
	//of background
	x -= 1;
	x += 1;
	y -= 1;
	y += 1;
	scene++;
	scene--;
	pixel_value.r = 0;
	pixel_value.g = 0;
	pixel_value.b = 250;
	return (pixel_value);
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
	t_rgb		color;

	color = get_pixel_val(x, y, data->scene);
	if (data->rendering == render_finished)
		return (0);
	else if (data->rendering == render_restart)
	{
		x = 0;
		y = 0;
		data->rendering = render_run;
	}
	else if (data->rendering == render_run)
	{
		while (x < data->window.width)
		{
			mlx_put_pixel(data->window.image, x, y, rgb_to_int(color));
			x++;
		}
		x = 0;
			y++;
		if (y < data->window.height)
			return (1);
		data->rendering = render_finished;
	}
	return (0);
//>>>>>>> render_development_merge
}

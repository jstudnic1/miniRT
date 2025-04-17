#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

// Function prototypes for rendering
void		render_scene(t_data *data);
t_ray		generate_primary_ray(int x, int y, t_scene *scene, t_window *window);

// Intersection functions
t_collision plane_ray_collision(t_ray inc_ray, t_plane plane);

// Lighting functions
t_rgb calculate_ambient(t_ambient ambient, t_rgb surface_color);
t_rgb calculate_diffuse(t_light light, t_vector light_dir, t_vector normal, t_rgb surface_color);
t_rgb calculate_lighting(t_collision hit, t_scene *scene, t_vector view_dir);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:51:03 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/07 18:10:23 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"

t_rgb calculate_ambient(t_ambient ambient, t_rgb surface_color)
{
    t_rgb ambient_color;

    ambient_color.r = (int)(ambient.intensity * ambient.color.r * surface_color.r / 255.0);
    ambient_color.g = (int)(ambient.intensity * ambient.color.g * surface_color.g / 255.0);
    ambient_color.b = (int)(ambient.intensity * ambient.color.b * surface_color.b / 255.0);
    return (ambient_color);
}

t_rgb calculate_diffuse(t_light light, t_vector light_dir, t_vector normal, t_rgb surface_color)
{
    t_rgb diffuse_color;
    double diffuse_factor;

    // Calculate diffuse factor (dot product of normal and light direction)
    diffuse_factor = dot_product(normal, light_dir);
    if (diffuse_factor < 0)
        diffuse_factor = 0;

    // Calculate diffuse color
    diffuse_color.r = (int)(light.brightness * light.color.r * surface_color.r * diffuse_factor / 255.0);
    diffuse_color.g = (int)(light.brightness * light.color.g * surface_color.g * diffuse_factor / 255.0);
    diffuse_color.b = (int)(light.brightness * light.color.b * surface_color.b * diffuse_factor / 255.0);
    return (diffuse_color);
}

t_rgb calculate_lighting(t_collision hit, t_scene *scene, t_vector view_dir)
{
    t_rgb final_color = {0, 0, 0};
    t_rgb ambient_color;
    t_rgb diffuse_color;
    t_vector light_dir;
    int i;
    double dot_nl;
    static int debug_count = 0;

    (void)view_dir; // Unused for now, will be used for specular lighting later

    // Calculate ambient light
    ambient_color = calculate_ambient(scene->ambient, hit.color);
    final_color = ambient_color;

    // For each light source
    for (i = 0; i < scene->num_lights; i++)
    {
        // Calculate light direction (from hit point to light)
        light_dir = vec_sub(scene->lights[i].position, hit.point);
        normalize_vec(&light_dir);

        // Debug print for key points - limit to 5 outputs to prevent flooding
        if (debug_count < 5) {
            dot_nl = dot_product(hit.normal, light_dir);
            printf("Light debug #%d: pos=(%f,%f,%f) hit=(%f,%f,%f) normal=(%f,%f,%f) dot=%f\n",
                debug_count++,
                scene->lights[i].position.x, scene->lights[i].position.y, scene->lights[i].position.z,
                hit.point.x, hit.point.y, hit.point.z,
                hit.normal.x, hit.normal.y, hit.normal.z,
                dot_nl);
        }

        // Calculate diffuse lighting
        diffuse_color = calculate_diffuse(scene->lights[i], light_dir, hit.normal, hit.color);

        // Add diffuse contribution
        final_color.r = min(final_color.r + diffuse_color.r, 255);
        final_color.g = min(final_color.g + diffuse_color.g, 255);
        final_color.b = min(final_color.b + diffuse_color.b, 255);
    }

    return (final_color);
}

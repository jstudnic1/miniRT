/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <jstudnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:15:23 by jstudnic          #+#    #+#             */
/*   Updated: 2025/03/14 16:11:47 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minirt.h"
#include <assert.h>

void	test_parse_basic_scene(void)
{
	t_scene	*scene;

	printf("\nTesting basic scene parsing...\n");
	scene = parse_scene("scenes/basic.rt");
	assert(scene != NULL);
	assert(scene->ambient.intensity == 0.2);
	assert(scene->ambient.color.r == 255);
	assert(scene->ambient.color.g == 255);
	assert(scene->ambient.color.b == 255);
	assert(scene->camera.fov == 90);
	assert(scene->num_lights == 1);
	assert(scene->num_planes == 0);
	assert(scene->num_cylinders == 0);
	free_scene(scene);
	printf("Basic scene test passed!\n");
}

void	test_parse_full_scene(void)
{
	t_scene	*scene;

	printf("\nTesting full scene parsing...\n");
	scene = parse_scene("scenes/full.rt");
	assert(scene != NULL);
	assert(scene->num_lights == 1);
	assert(scene->num_planes == 3);
	assert(scene->num_cylinders == 1);
	
	// Test cylinder properties
	assert(scene->cylinders[0].diameter == 0.5);
	assert(scene->cylinders[0].height == 2.5);
	
	// Test plane properties
	assert(scene->planes[0].color.r == 125);
	assert(scene->planes[0].color.g == 0);
	assert(scene->planes[0].color.b == 0);
	
	free_scene(scene);
	printf("Full scene test passed!\n");
}

void	test_parse_invalid_scene(void)
{
	t_scene	*scene;

	printf("\nTesting invalid scene parsing...\n");
	scene = parse_scene("scenes/invalid.rt");
	assert(scene == NULL);
	printf("Invalid scene test passed!\n");
}

void	test_parse_empty_scene(void)
{
	t_scene	*scene;

	printf("\nTesting empty scene parsing...\n");
	scene = parse_scene("scenes/empty.rt");
	assert(scene == NULL);
	printf("Empty scene test passed!\n");
}

void	test_scene_validation(void)
{
	t_scene	*scene;

	printf("\nTesting scene validation...\n");
	
	// Test valid scene
	scene = parse_scene("scenes/valid.rt");
	assert(scene != NULL);
	assert(validate_scene(scene) == 1);
	free_scene(scene);
	
	// Test invalid FOV
	scene = parse_scene("scenes/invalid_fov.rt");
	assert(scene != NULL);
	assert(validate_scene(scene) == 0);
	free_scene(scene);
	
	// Test invalid intensity
	scene = parse_scene("scenes/invalid_intensity.rt");
	assert(scene != NULL);
	assert(validate_scene(scene) == 0);
	free_scene(scene);
	
	printf("Scene validation tests passed!\n");
}

int	main(void)
{
	printf("Starting scene parser tests...\n");
	
	test_parse_basic_scene();
	test_parse_full_scene();
	test_parse_invalid_scene();
	test_parse_empty_scene();
	test_scene_validation();
	
	printf("\nAll tests passed successfully!\n");
	return (0);
} 
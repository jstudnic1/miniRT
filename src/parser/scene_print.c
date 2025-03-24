#include "../../incl/minirt.h"



void	print_scene(t_scene *scene)
{
	printf("ambient light: %f; %ir %ig %ib\n", scene->ambient.intensity, \
	scene->ambient.color.r, scene->ambient.color.g, scene->ambient.color.b);

	printf("camera: %ffov; %fxo, %fyo, %fzo; %fxp, %fyp, %fzp\n", \
	scene->camera.fov, scene->camera.orientation.x, scene->camera.orientation.y, \
	scene->camera.orientation.z, scene->camera.position.x, \
	scene->camera.position.y, scene->camera.position.z);

	printf("number of cylinders: %i @array %p\n", scene->num_cylinders, scene->cylinders);

	printf("number of lights: %i @array %p\n", scene->num_lights, scene->lights);

	printf("number of planes: %i @array %p\n", scene->num_planes, scene->planes);
}

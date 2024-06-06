#include <stdlib.h>
#include "parser.h"

void	cleanup_scene_data(t_scene_data *scene)
{
	if (scene->sphere)
		free(scene->sphere);
	if (scene->plane)
		free(scene->plane);
	if (scene->cylinder)
		free(scene->cylinder);
}

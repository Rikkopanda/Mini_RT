

#include "minirt.h"


void 	test_reflect_function();
t_vec4f reflect(t_vec4f normal, t_vec4f incoming);
t_vec4f lerp(t_vec4f a, t_vec4f b, float f);
t_vec4f	sky_box(float y);
t_vec4f clamp_vec4f(t_vec4f v, float low, float high);
t_vec4f generate_random_vec4f_hemisphere(t_vec4f normal);

/**
 * rendering equation(NVIDIA's uitleg):
 * https://www.youtube.com/watch?v=AODo_RjJoUA
 * 
 * Josh's Channel
 * https://www.youtube.com/watch?v=gsZiJeaMO48&t=274s
 * 
 * https://www.umb.edu/spectralmass/terra-aqua-modis/modis/
 * 
 * rendering equation intuitieve animatie
 * https://www.youtube.com/watch?v=eo_MTI-d28s
 * 
 * file:///home/rverhoev/Downloads/ray_tracing_practice.pdf
 * 
 * lange uitleg
 * https://www.youtube.com/watch?v=wawf7Am6xy0
 * 
 */
t_vec4f	trace_ray(t_scene_data *scene, t_ray ray, int bounce_depth)
{
	t_hit_info hit_info;
	t_vec4f IncomingLightColor = (t_vec4f){0,0,0,0};
	check_intersection(scene, ray, &hit_info, bounce_depth);
	// hit_info.emission // == light 0.8, 0.9, 0.8 * emissionstrenght(bijv. 100). dit is direct een lichtsource
	t_vec4f incident_origin = ray.origin;
	ray.origin = hit_info.hit_location;

	//integrate over incoming light(in program is outgoing rays now), compute average
	//material color reflects certain waveforms aka color channel
	// if (hit_info.type == NONE && bounce_depth == 0)
	// 	return ((sky_box(ray.direction[1]) / 255));
	// test_reflect_function();
	if (hit_info.type == NONE)
    {
        if (bounce_depth == 0)
            return (sky_box(ray.direction[1]) / 255);
        else
		    return ((sky_box(ray.direction[1]) / 255) * scene->ambient.ratio);
    }
	else if (bounce_depth == MAX_BOUNCE_DEPTH)
		return (hit_info.emission);
	else if (hit_info.type == LIGHT)
		return (hit_info.emission);
	for(int i = 0; i < REFLECT_RAYS_N; i++)
	{
		// printf("\n_______________\nincident dir ray\n");
		// print_matrix_1_3(ray.direction);
		t_vec4f incident_ray = hit_info.hit_location - incident_origin;
		normalize_vector(&incident_ray);
		// print_matrix_1_3(incident_ray);
		
		
		t_vec4f diffuse_ray = generate_random_vec4f_hemisphere(hit_info.normal);
		// if (dot_product_3d(diffuse_ray, hit_info.normal) < 0.0f) {
		// 	diffuse_ray *= -1.0f;
		// }
		float light_angle_factor = dot_product_3d(hit_info.normal, diffuse_ray);

		normalize_vector(&diffuse_ray);
		// printf("diffuse\n");

		// print_matrix_1_3(diffuse_ray);
		t_vec4f reflection = reflect(hit_info.normal, incident_ray);//using old direction
		// printf("normal\n");

		// print_matrix_1_3(hit_info.normal);
	
		// printf("reflection\n");

		// print_matrix_1_3(reflection);
		// ray.direction = diffuse_ray;
		ray.direction = lerp(diffuse_ray, reflection, hit_info.material.smoothness);
		// printf("result\n");
		normalize_vector(&ray.direction);
		// print_matrix_1_3(ray.direction);
        /**
         * voorbeeld:
         * light_angle_factor = 0.5
         * smoothness = 0;
         * dan:
         * = 0.5
         * smoothness = 1;
         * dan:
         * = 1?
         */
        
		IncomingLightColor += (trace_ray(scene, ray, bounce_depth + 1) * light_angle_factor);// * interpolatef(light_angle_factor, 1.0f, hit_info.material.smoothness)
	}
	t_vec4f result_color = (hit_info.material.color / 255) * (IncomingLightColor / REFLECT_RAYS_N);
	// result_color += (hit_info.material.color / 255) * (IncomingLightColor / REFLECT_RAYS);//material.color in ranges 0-255, incomininglight in ranges of 0-1 finally
	// printf("result color\n");
	result_color += hit_info.emission;

	result_color = clamp_vec4f(result_color, 0, 1);
	return (result_color);
}

// whyyy the do while???
t_vec4f generate_random_vec4f_hemisphere(t_vec4f normal) {
    t_vec4f random_vec;

	// srand(time(0));
    // do {
        random_vec[0] = (float)rand();
        random_vec[1] = (float)rand();
        random_vec[2] = (float)rand();
        random_vec[3] = 0.0f;
    // } while (dot_product_3d(random_vec, random_vec) >= 1.0f);

	// printf("random[2] = %f,   %d\n", random_vec[2], rand());
    // Ensure the vector is in the same hemisphere as the normal
	normalize_vector(&random_vec);
    if (dot_product_3d(random_vec, normal) < 0.0f) {
        random_vec *= -1.0f;
    }
    return (random_vec);
}

t_vec4f reflect(t_vec4f normal, t_vec4f incoming)
{
	t_vec4f reflection;

	reflection = incoming - (2 * dot_product_3d(incoming, normal) * normal);
	return reflection;
}

/**
 * 
 * just a test
 */
void 	test_reflect_function()
{
	t_vec4f incoming = (t_vec4f){0,0,-1,1};

	t_vec4f surface_hit_pos = (t_vec4f){20,40,60,1};

	// t_vec4f surface_normal = (t_vec4f){0.707,0,0.707,1};
	t_vec4f surface_normal = (t_vec4f){0,0,1,1};

	t_vec4f reflection = reflect(surface_normal, incoming);
	printf("reflection\n");

	print_matrix_1_3(reflection);

	t_vec4f diffuse_ray = generate_random_vec4f_hemisphere(surface_normal);
	printf("surface normal\n");

	print_matrix_1_3(surface_normal);

	normalize_vector(&diffuse_ray);
	printf("diffuse_ray\n");

	print_matrix_1_3(diffuse_ray);

	t_vec4f new_direction = lerp(diffuse_ray, reflection, 1);
	printf("result\n");
	normalize_vector(&new_direction);
	print_matrix_1_3(new_direction);


	exit(0);
}

t_vec4f lerp(t_vec4f a, t_vec4f b, float f) 
{
	if (f == 0)
		return a;
	else if (f == 1)
		return b;
	else
    	return (a * (float)(1.0 - f)) + (b * f);
}

t_vec4f	sky_box(float y)
{
	t_vec4f	top_hemi = (t_vec4f){145,224,255,-1};
	t_vec4f	bottom_hemi = (t_vec4f){255,255,255,-1};

	if (y > 0.1)
		return top_hemi;
	else if (y < -0.1)
		return bottom_hemi;
	// 0.1 / 0.1 = 1
	// -0.1 / 0.1 = -1
	// dat + 0.1 / 0.2
	t_vec4f result = lerp(bottom_hemi, top_hemi, (y + 0.1f) / 0.2f);
	result[3] = NONE;
	return (result);
}

t_vec4f clamp_vec4f(t_vec4f v, float low, float high)
{
	t_vec4f result;

	result[0] = fminf(fmaxf(v[0], low), high);
	result[1] = fminf(fmaxf(v[1], low), high);
	result[2] = fminf(fmaxf(v[2], low), high);
	result[3] = fminf(fmaxf(v[3], low), high);
	return result;
}

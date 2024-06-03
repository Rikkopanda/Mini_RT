#include <math.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>

typedef int t_vec4f __attribute__ ((vector_size ((sizeof(int) * 4))));
// typedef float t_vec3f __attribute__ ((vector_size ((sizeof(float) * 3))));
// typedef float t_vec2f __attribute__ ((vector_size ((sizeof(float) * 2))));

int main(void)
{
	t_vec4f a = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
	t_vec4f b = {1, 1, 1, 1};

	t_vec4f c = a + b;
	printf("bla\n");
	return 0;
}


#include "parser.h"

/**
 * https://www.freetext.org/Introduction_to_Linear_Algebra/Basic_Vector_Operations/Normalization/
*/
t_vec4f normalize_vector(t_vec4f *v)
{
	float magnitude;
	double squared;

	squared = pow((double)(*v)[0], 2) + pow((double)(*v)[1], 2) + pow((double)(*v)[2], 2);
	magnitude = (float)sqrt(squared);
	*v = *v * (1.0f / magnitude);
	return (*v);
}

void	print_vec4ftor(float vec[3])
{
	printf("x: %f, y: %f, z: %f\n", vec[0], vec[1], vec[2]);
}

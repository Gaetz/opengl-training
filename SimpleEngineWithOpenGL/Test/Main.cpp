#include "Vector4.h"

int main()
{
	Vector4 v;
	v.set(1.0f, 2.0f, 3.0f, 4.0f);
	printf("Vector: %f %f %f %f \n", v.x, v.y, v.z, v.w);

	printf("x: %f\n", v[0]);
	printf("y: %f\n", v[1]);
	printf("z: %f\n", v[2]);
	printf("w: %f\n", v[3]);

	return 0;
}
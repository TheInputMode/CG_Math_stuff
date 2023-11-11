#define USE_SHORTER_TYPES
#include <iostream>
#include "../head/typedef.hpp"

int main()
{
	Mat4f test1;

	std::cout << degrees_to_rads(160.);

	test1.print_to_console();

	cw_x_rotate4(test1, 40.0f);
	
	test1.print_to_console();


	return 0;
}
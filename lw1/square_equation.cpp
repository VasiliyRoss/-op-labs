#include <cstdio>
#include <cmath>

int main()
{
	// 1. prompt user to enter coefficients
  std::puts("please enter a, b and c for `ax^2 + bx + c = 0`:");

	// 2. read coefficients for equation `ax^2 + bx + c`
  float a = 0;
  float b = 0;
  float c = 0;

  std::scanf("%e %e %e", &a, &b, &c);  
	// 3. solve equation `ax^2 + bx + c`

  float d = b * b - 4 * a * c;

  if(d > 0)
  {
    float x1 = (-b + std::sqrt(d)) / (2 * a);
    float x2 = (-b - std::sqrt(d)) / (2 * a);
    std::printf("x1=%f\nx2=%f\n", x1, x2);
  } else if(d == 0){
    std::printf("x=%f\n", -b/2*a);
  } else {
    std::printf("No solution\n");
  }

}
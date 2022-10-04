// Header Files
#include "v3math.h"
#include "stdio.h"

// Main Function
int main()
{
   // from points test
   float a[] = {1, 0, 0};
   float b[] = {0, 1, 0};
   float c[] = {0, 0, 0};
   float d[] = {-1, 1, 0};

   // TESTS FOR FROM POINTS
   v3_from_points(c, b, a);

   if (!(v3_equals(c, d, .01)))
   {
      printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
   }

   // from points test
   a[0] = 1;
   a[1] = 0;

   // TODO: FIGURE OUT HOW TO MAKE A EQUAL TO ARRAY LIKE ABOVE WITHOUT CREATING IT

   v3_from_points(c, a, b);

   if (!(v3_equals(c, d, .01)))
   {
      printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
   }


   // TESTS FOR ADD
   v3_add(c, b, a);


   // TESTS FOR SUBTRACT
   v3_subtract(c, b, a);


   // TESTS FOR DOT PRODUCT
   v3_dot_product(a, b);


   // TESTS FOR CROSS PRODUCT
   v3_cross_product(c, b, a);


   // TESTS FOR SCALE
   x3_scale(a, 2);


   // TESTS FOR ANGLE
   x3_angle(a, b)


   // TESTS FOR ANGLE QUICK
   x3_quick_angle(a, b);


   // TESTS FOR REFLECT



   // TESTS FOR LENGTH
   x3_length(a);


   // TESTS FOR NORMALIZE



   // TESTS FOR EQUALS




   return 0;
}

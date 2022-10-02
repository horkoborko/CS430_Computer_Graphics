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

   return 0;
}

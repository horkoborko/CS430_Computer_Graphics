// Header Files
#include "v3math.h"
#include "stdio.h"

// Main Function
int main()
{
   // from points test 1
   {
      float a[] = {1, 0, 0};
      float b[] = {0, 1, 0};
      float c[] = {0, 0, 0};
      float d[] = {-1, 1, 0};

      v3_from_points(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }

   // from points test 2
   {
      float a[] = {2, 4, 5};
      float b[] = {-1, 2, 0};
      float c[] = {0, 0, 0};
      float d[] = {-3, -2, -5};

      v3_from_points(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }

   // from points test 3
   {
      float a[] = {200, -100, 505};
      float b[] = {-1, 2, 0};
      float c[] = {0, 0, 0};
      float d[] = {-201, 102, -505};

      v3_from_points(a, a, b);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }

   // add test 1
   {
      float a[] = {0, 1, 0};
      float b[] = {1, 0, 0};
      float c[] = {0, 0, 0};
      float d[] = {1, 1, 0};

      v3_add(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }

   // add test 2
   {
      float a[] = {-1, 3, 4};
      float b[] = {1, -2, 0};
      float c[] = {0, 0, 0};
      float d[] = {0, 1, 4};

      v3_add(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }

   // add test 3
   {
      float a[] = {-20, 13, 2};
      float b[] = {11, -29, 15};
      float c[] = {0, 0, 0};
      float d[] = {-9, -16, 17};

      v3_add(a, a, b);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }
 
   // subtract test 1
   {
      float a[] = {0, 1, 0};
      float b[] = {1, 0, 0};
      float c[] = {0, 0, 0};
      float d[] = {-1, 1, 0};

      v3_subtract(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }
  
   // subtract test 2
   {
      float a[] = {3, 7, -5};
      float b[] = {8, 2, 1};
      float c[] = {0, 0, 0};
      float d[] = {-5, 5, -6};

      v3_subtract(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }
   
   // subtract test 3
   {
      float a[] = {-120, 135, 20};
      float b[] = {150, 180, 40};
      float c[] = {0, 0, 0};
      float d[] = {-270, -45, -20};

      v3_subtract(a, a, b);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }
   // TODO: TEST BELOW TEST
   // dot product test 1
   {
      float a[] = {0, 1, 0};
      float b[] = {1, 0, 0};
      float result = 0;
      float calcResult; 

      calcResult = v3_dot_product(a,b);

      if (result != calcResult)
      {
         printf("ERROR: Got %f, expected %f\n", calcResult, result); 
      }
   }

/*
   // TESTS FOR CROSS PRODUCT
   v3_cross_product(c, b, a);


   // TESTS FOR SCALE
   // Logan: I can do scale and up, if you can do the rest down below. 
   v3_scale(a, 2);
*/

   // TESTS FOR ANGLE
 //  v3_angle(a, b);


   // TESTS FOR ANGLE QUICK
   //v3_angle_quick(a, b);


   // TESTS FOR REFLECT



   // TESTS FOR LENGTH
   //v3_length(a);


   // TESTS FOR NORMALIZE




   return 0;
}

// Header Files
#include "v3math.h"
#include "stdio.h"
#include <math.h>

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
      float d[] = {-201, 102, -505};

      v3_from_points(a, a, b);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], d[0], d[1], d[2]);
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
      float d[] = {-9, -16, 17};

      v3_add(a, a, b);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], d[0], d[1], d[2]);
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
      float d[] = {-270, -45, -20};

      v3_subtract(a, a, b);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], d[0], d[1], d[2]);
      }
   }

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

   // dot product test 2
   {
      float a[] = {2, 7, 5};
      float b[] = {10, 4, 2};
      float result = 58;
      float calcResult;

      calcResult = v3_dot_product(a,b);

      if (result != calcResult)
      {
         printf("ERROR: Got %f, expected %f\n", calcResult, result);
      }
   }

   // dot product test 3
   {
      float a[] = {-1, 2, -112};
      float b[] = {20, 50, 2};
      float result = -144;
      float calcResult;

      calcResult = v3_dot_product(a,b);

      if (result != calcResult)
      {
         printf("ERROR: Got %f, expected %f\n", calcResult, result);
      }
   }

   // cross product test 1
   {
      float a[] = {1, 0, 0};
      float b[] = {0, 1, 0};
      float c[] = {0, 0, 0};
      float d[] = {0, 0, 1};

      v3_cross_product(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }

   // cross product test 2
   {
      float a[] = {2, -1, 4};
      float b[] = {1, 4, 2};
      float c[] = {0, 0, 0};
      float d[] = {-18, 0, 9};

      v3_cross_product(c, a, b);

      if (!(v3_equals(c, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", c[0], c[1], c[2], d[0], d[1], d[2]);
      }
   }

   // cross product test 3
   {
      float a[] = {50, 2, 20};
      float b[] = {100, 9, -5};
      float d[] = {-190, 2250, 250};

      v3_cross_product(a, a, b);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], d[0], d[1], d[2]);
      }
   }

   // scale test 1
   {
      float a[] = {1, 0, 0};
      float d[] = {2, 0, 0};
      int scaling_factor = 2;

      v3_scale(a, scaling_factor);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], d[0], d[1], d[2]);
      }
   }

   // scale test 2
   {
      float a[] = {102, 403, 506};
      float d[] = {0, 0, 0};
      int scaling_factor = 0;

      v3_scale(a, scaling_factor);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], d[0], d[1], d[2]);
      }
   }

   // scale test 3
   {
      float a[] = {20, -10, 40};
      float d[] = {60, -30, 120};
      int scaling_factor = 3;

      v3_scale(a, scaling_factor);

      if (!(v3_equals(a, d, .0001)))
      {
         printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], d[0], d[1], d[2]);
      }
   }

   // TESTS FOR ANGLE QUICK
 // test 1
 {
   float a[] = {10, 10, 10};
   float b[] = {0, 10, 10};
   float result[] = {.816497, 0, 0};
   float calcResult[] = {0, 0, 0};

   calcResult[0] = v3_angle_quick(a, b);

   if (!(v3_equals(result, calcResult, .0001)))
   {
      printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
   }
 }

// test 2
 {
   float a[] = {0, 1, -2};
   float b[] = {2, 4, 0};
   float result[] = {.4, 0, 0};
   float calcResult[] = {0, 0, 0};

   calcResult[0] = v3_angle_quick(a, b);

   if (!(v3_equals(result, calcResult, .0001)))
   {
      printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
   }
 }

// test 3
 {
   float a[] = {14, -7, 23};
   float b[] = {8, 0, 2};
   float result[] = {.688703, 0, 0};
   float calcResult[] = {0, 0, 0};

   calcResult[0] = v3_angle_quick(a, b);

   if ( !(v3_equals(result, calcResult, .0001)))
   {
      printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
   }
 }

   // TESTS FOR ANGLE 
   //test 1
{
  float a[] = {10, 10, 10};
  float b[] = {0, 10, 10};
  float result[] = {.61548, 0, 0};
  float calcResult[] = {0, 0, 0};

  calcResult[0] = v3_angle(a, b);

  if (!(v3_equals(result, calcResult, .0001)))
  {
     printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
  }
}

// test 2
{
  float a[] = {5, 10, 15};
  float b[] = {30, 60, 90};
  float result[] = {0, 0, 0};
  float calcResult[] = {0, 0, 0};

  calcResult[0] = v3_angle(a, b);

  if (!(v3_equals(result, calcResult, .0001)))
  {
     printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
  }
}

// test 3
{
  float a[] = {14, -7, 23};
  float b[] = {20, 8, -2};
  float result[] = {1.2706, 0, 0};
  float calcResult[] = {0, 0, 0};

  calcResult[0] = v3_angle(a, b);

  if (!(v3_equals(result, calcResult, .0001)))
  {
     printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
  }
}

   // TESTS FOR REFLECT
   //test 1
{
  float v[] = {14, 7, 0};
  float n[] = {0, 8, 0};
  float dst[] = {0, 0, 0};
  float result[] = {14, -889, 0};

  v3_reflect(dst, v, n);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", dst[0], dst[1], dst[2], result[0], result[1], result[2]);
  }
}

  //test 2
{
  float v[] = {2, 3, -17};
  float n[] = {2, 7, 0};
  float dst[] = {0, 0, 0};
  float result[] = {-98, -347, -17};

  v3_reflect(dst, v, n);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", dst[0], dst[1], dst[2], result[0], result[1], result[2]);
  }
}

  //test 3
{
  float v[] = {150, 683, 200};
  float n[] = {-43, 270, -92};
  float result[] = {13722310, -86161717, 29359240};

  v3_reflect(v, v, n);

  if (!(v3_equals(v, result, .0001)))
  {
     printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", v[0], v[1], v[2], result[0], result[1], result[2]);
  }
}


   // TESTS FOR LENGTH
   // test 1
{
  float a[] = {1, 2, 3};
  float result[] = {3.74166, 0, 0};
  float calcResult[] = {0, 0, 0};

  calcResult[0] = v3_length(a);

  if (!(v3_equals(result, calcResult, .0001)))
  {
     printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
  }
}

// test 2
{
  float a[] = {-20, 40, 10};
  float result[] = {45.8258, 0, 0};
  float calcResult[] = {0, 0, 0};

  calcResult[0] = v3_length(a);

  if (!(v3_equals(result, calcResult, .0001)))
  {
     printf("ERROR: Got %f, expected %f\n", calcResult[0], result[0]);
  }
}

// test 3
{
  float a[] = {1, 0, 0};
  float result = 1;
  float calcResult = 0;

  calcResult = v3_length(a);

  if (result != calcResult)
  {
     printf("ERROR: Got %f, expected %f\n", calcResult, result);
  }
}

   // TESTS FOR NORMALIZE
   // test 1
{
  float a[] = {8, 6, 4};
  float dst[] = {0, 0, 0};
  float result[] = {0.742781, 0.557086, 0.371391};

  v3_normalize(dst, a);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", dst[0], dst[1], dst[2], result[0], result[1], result[2]);
  }
}

// test 2
{
  float a[] = {0, 0, 0};
  float dst[] = {0, 0, 0};
  float result[] = {0, 0, 0};

  v3_normalize(dst, a);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", dst[0], dst[1], dst[2], result[0], result[1], result[2]);
  }
}

// test 3
{
  float a[] = {-129, 0, 210};
  float result[] = {-0.523418, 0, .852076};

  v3_normalize(a, a);

  if (!(v3_equals(a, result, .0001)))
  {
     printf("ERROR: Got {%f, %f, %f}, expected {%f, %f, %f}\n", a[0], a[1], a[2], result[0], result[1], result[2]);
  }
}

   return 0;
}

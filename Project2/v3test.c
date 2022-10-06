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

   // scale test 1
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




   // TESTS FOR ANGLE
 //  v3_angle(a, b);
 // test 1
 {
   float a[] = {10, 10, 10};
   float b[] = {0, 10, 10};
   float result = (1 / 3) * sqrt(6);
   float calcResult = 0;

   calcResult = v3_angle_quick(a, b);

   if (result != calcResult)
   {
      printf("ERROR: Got %f, expected %f\n", calcResult, result);
   }
 }

// test 2
 {
   float a[] = {5, 10, 15};
   float b[] = {30, 60, 90};
   float result = (2100 / ((5 * sqrt(14)) * (30 * sqrt(14))));
   float calcResult = 0;

   calcResult = v3_angle_quick(a, b);

   if (result != calcResult)
   {
      printf("ERROR: Got %f, expected %f\n", calcResult, result);
   }
 }

// test 3
 {
   float a[] = {14, 7, 23};
   float b[] = {0, 8, 0};
   float result = (7 / 258) * sqrt(86);
   float calcResult = 0;

   calcResult = v3_angle_quick(a, b);

   if (result != calcResult)
   {
      printf("ERROR: Got %f, expected %f\n", calcResult, result);
   }
 }


   // TESTS FOR ANGLE QUICK
   //v3_angle_quick(a, b);
   //test 1
{
  float a[] = {10, 10, 10};
  float b[] = {0, 10, 10};
  float result = 35.26438;
  float calcResult = 0;

  calcResult = v3_angle(a, b);

  if (result != calcResult)
  {
     printf("ERROR: Got %f, expected %f}\n", calcResult, result);
  }
}

// test 2
{
  float a[] = {5, 10, 15};
  float b[] = {30, 60, 90};
  float result = 0;
  float calcResult = 0;

  calcResult = v3_angle(a, b);

  if (result != calcResult)
  {
     printf("ERROR: Got %f, expected %f}\n", calcResult, result);
  }
}

// test 3
{
  float a[] = {14, 7, 23};
  float b[] = {0, 8, 0};
  float result = 75.42720;
  float calcResult = 0;

  calcResult = v3_angle(a, b);

  if (result != calcResult)
  {
     printf("ERROR: Got %f, expected %f}\n", calcResult, result);
  }
}

   // TESTS FOR REFLECT
   //test 1
{
  float v[] = {14, 7};
  float n[] = {0, 8};
  float dst[] = {0, 0};
  float result[] = {14, -889};

  v3_reflect(dst, v, n);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f}, expected {%f, %f}\n", dst[0], dst[1], result[0], result[1]);
  }
}

  //test 2
{
  float v[] = {2, 3};
  float n[] = {4, 5};
  float dst[] = {0, 0};
  float result[] = {-182, -227};

  v3_reflect(dst, v, n);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f}, expected {%f, %f}\n", dst[0], dst[1], result[0], result[1]);
  }
}

  //test 3
{
  float v[] = {0, 1};
  float n[] = {1, 0};
  float dst[] = {0, 0};
  float result[] = {0, 1};

  v3_reflect(dst, v, n);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f}, expected {%f, %f}\n", dst[0], dst[1], result[0], result[1]);
  }
}


   // TESTS FOR LENGTH
   //v3_length(a);
   // test 1
{
  float a[] = {1, 2, 3};
  float result = sqrt(14);
  float calcResult = 0;

  calcResult = v3_length(a);

  if (result != calcResult)
  {
     printf("ERROR: Got %f, expected %f}\n", calcResult, result);
  }
}

// test 2
{
  float a[] = {7, 2, 5};
  float result = sqrt(78);
  float calcResult = 0;

  calcResult = v3_length(a);

  if (result != calcResult)
  {
     printf("ERROR: Got %f, expected %f}\n", calcResult, result);
  }
}

// test 3
{
  float a[] = {1, 0, 0};
  float result = sqrt(1);
  float calcResult = 0;

  calcResult = v3_length(a);

  if (result != calcResult)
  {
     printf("ERROR: Got %f, expected %f}\n", calcResult, result);
  }
}

   // TESTS FOR NORMALIZE
   // test 1
{
  float a[] = {8, 6, 4};
  float dst[] = {0, 0, 0};
  float result[] = {0.74, 0.56, 0.37};

  v3_normalize(dst, a);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f}, expected {%f, %f}\n", dst[0], dst[1], dst[2], result[0], result[1], result[2]);
  }
}

// test 2
{
  float a[] = {1, 73, 4};
  float dst[] = {0, 0, 0};
  float result[] = {0.01, 1, 0.05};

  v3_normalize(dst, a);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f}, expected {%f, %f}\n", dst[0], dst[1], dst[2], result[0], result[1], result[2]);
  }
}

// test 3
{
  float a[] = {12, 12, 12};
  float dst[] = {0, 0, 0};
  float result[] = {0.58, 0.58, 0.58};

  v3_normalize(dst, a);

  if (!(v3_equals(dst, result, .0001)))
  {
     printf("ERROR: Got {%f, %f}, expected {%f, %f}\n", dst[0], dst[1], dst[2], result[0], result[1], result[2]);
  }
}

   return 0;
}

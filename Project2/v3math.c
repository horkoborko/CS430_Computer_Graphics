// Header Files
#include "v3math.h"
#include <math.h>
#include <stdbool.h>


// Function Implementation
void v3_from_points(float *dst, float *a, float *b)
{
   // initialize variables 

   // subtract ax (head) from bx (tail)
   dst[0] = a[0] - b[0];
   
   // subtract ay (head) from by (tail)
   dst[1] = a[1] - b[1];

   // subtract az (head) From bz (tail)
   dst[2] = a[2] - b[2];

   // TODO: ASK IF FUNCTION IS SIMPLY SUBTRACTION OR SOMETHING MORE

}

void v3_add(float *dst, float *a, float *b)
{
   // add x component of a and b
   dst[0] = a[0] + b[0];

   // add y component of a and b
   dst[1] = a[1] + b[1];

   // add z component of a and b
   dst[2] = a[2] + b[2];

}

void v3_subtract(float *dst, float *a, float *b)
{
   // subtract ax from bx 
   dst[0] = a[0] - b[0];

   // subtract ay from by 
   dst[1] = a[1] - b[1];

   // subtract az from bz
   dst[2] = a[2] - b[2];


}

float v3_dot_product(float *a, float *b)
{
   // initialize variables 

   // multiply ax * bx, ay * by, az * bz and add together, and return 
   return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

void v3_cross_product(float *dst, float *a, float *b)
{
   // initalize variables 
   float temp1, temp2, temp3;

   // multiply ay * bz and subtract az * by, store in temp
   temp1 = (a[1] * b[2]) - (a[2] * b[1]);
   
   // multiply az * bx and subtract ax * bz, store in temp
   temp2 = (a[2] * b[0]) - (a[0] * b[2]);

   // mutliply ax * by and subtract ay * bx, store in temp
   temp3 = (a[0] * b[1]) - (a[1] * b[0]);

   // store x in dest
   dst[0] = temp1;

   // store y in dest 
   dst[1] = temp2;

   // store z in dest
   dst[2] = temp3;
   


}

void v3_scale(float *dst, float s)
{
   // take the x of the dest and scale it by s 
   dst[0] = dst[0] * s;

   // take the y of dest and scale it by s 
   dst[1] = dst[1] * s;

   // take the z of dest and scale it by s
   dst[2] = dst[2] * s;

}

float v3_angle(float *a, float *b) // angle between a and b
{
   // return the arccos of the angle after getting from v3_angle_quick
      // function: v3_angle_quick
   return acos( v3_angle_quick( a, b));


}

float v3_angle_quick(float *a, float *b) // angle between a and b; no cos-1
{
   // initialize variables 
   float dotProduct, magA, magB;

   // get the dot product of a and b 
      // function: v3_dot_product
   dotProduct = v3_dot_product( a, b);

   // get the magnitude of a 
      // function: v3_Length
   magA = v3_length(a);

   // get the magnitude of b 
   magB = v3_length(b);

   // calculate value and return it
   return dotProduct / (magA * magB);

}	

void v3_reflect(float *dst, float *v, float *n)
{
   // initialize variables 
   float dotProduct;

   // get the dot product of n and v 
      // function: v3_dot_product
   dotProduct = v3_dot_product(n, v);
     
   // multiply the dot product by 2
   dotProduct = dotProduct * 2;

   // scale n by the above factor
      // function: v3_scale
   v3_scale(n, dotProduct);

   // subtract new n from v
      // function: v3_subtract
   v3_subtract( dst, v, n);



}

float v3_length(float *a)
{
   // return length by calculation
   return sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));

}

void v3_normalize(float *dst, float *a)
{
   // initialize variables 
   float length;

   // get the length of v
      // function: v3_Length 
   length = v3_length(a);

   // scale a by 1 / ||a||
      // function: v3_scale
   v3_scale(a, (1/length)); 

   // put the x of a into dest 
   dst[0] = a[0];

   // put the y of a into dest 
   dst[1] = a[1];

   // put the z of a into dest
   dst[2] = a[2];

}

bool v3_equals(float *a, float *b, float tolerance)
{
   // initialize variables 
   float dst[] = {0, 0, 0};

   // subtract a and b
      // function: v3_subtract 
   v3_subtract(dst, a, b);

   // if the 3 values in the dest array are less than tolerance and greater than negative tolerance
   if (dst[0] < tolerance && dst[0] > (0 - tolerance) && dst[1] < tolerance && dst[1] > (0 - tolerance) 
		   && dst[2] < tolerance && dst[2] > (0 - tolerance))
   {
      // return true
      return true;

   }

   // otherwise 
   else
   {
      // return false
      return false;
   }

}




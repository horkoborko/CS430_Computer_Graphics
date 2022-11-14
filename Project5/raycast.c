// Header Files
#include <stdio.h>  
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "v3math.h"
#include "ppmrw.h"

// Global Constants
const int MAX_OBJ = 128;

// Structures
typedef struct object
{
   // KEY
   // 0 = not an object (default)
   // 1 = camera 
   // 2 = sphere 
   // 3 = plane
   // 4 = light
   int kind; 

      // sphere properties 
      struct 
      {
	float radius;
	float specularColor[3];
      };

      // plane properties 
      struct 
      {
         float pn[3];  // plane normal
      };

      // camera properties 
      struct 
      {
         float width; 
	 float height;

      };

      // light properties 
      struct 
      {
         float theta;
	 float radialA2;
	 float radialA1;
	 float radialA0; 
	 float angularA0;
	 float direction[3];

      };


      float position[3];
      float diffuseColor[3];
      float color[3];
      float reflectivity;

   

} object;

// Function Prototypes
void raycast(int width, int height, char *inputFile, char *outputFile);
float shoot(float *R0, float *Rd, object currentObject, object **closestObject, object *objects);
void illuminate(float *point, object currentObject, object *lights, int numLights, float *red, float *green, float *blue, object *objects, int recLimit);
float clamp(float clampVal, float low, float high);

// Main Function
int main(int argc, char *argv[])
{
   // if the program was called with 5 total arguments
   if (argc == 5)
   {
      // call raycast to raycast the image  
         // function: atoi
      raycast(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
   }

   // otherwise, improper format
   else
   {
      // print error 
      printf("ERROR: Improper Format. Proper Format: raycast IMAGE_WIDTH IMAGE_HEIGHT INPUT_FILE OUTPUT_FILE\n");
   }

   return 0;
}

// Function Implementation
void raycast(int width, int height, char *inputFile, char *outputFile)
{
   // initalize variables

      // create an array of objects
      object objects[MAX_OBJ];

      // create an array of lights 
      object lights[MAX_OBJ];

      // create other variables
      FILE *fh;
      char readVal[20];
      object *closestObject = NULL;
      object tempObject;
      object dummyObject;
      int clearingIndex = 0, storingIndex = 0;
      int rowIndex = 0, colIndex = 0, searchingIndex = 0;
      int red, green, blue;
      int bgColor[] = {0, 0, 0};
      int lightStoringIndex = 0;
      int numLights = 0;
      float cameraWidth, cameraHeight;
      float deltaX, deltaY, P[3], Rd[3]; 
      float t = INFINITY; 
      float R0[] = {0, 0, 0};
      float point[3];
      float redIllum = 0, blueIllum = 0, greenIllum = 0;
      uint32_t *colorMap = (uint32_t *)( malloc(width * height * sizeof(uint32_t)));
      uint32_t tempNum;
      


   // for every object in the array 
   for (clearingIndex = 0; clearingIndex < MAX_OBJ; clearingIndex++)
   {
      // set its type to be nothing 
      objects[clearingIndex].kind = 0;

      // set x position to 0
      objects[clearingIndex].position[0] = 0;

      // set y position to 0
      objects[clearingIndex].position[1] = 0;

      // set z position to 0
      objects[clearingIndex].position[2] = 0; 

      // set radius to 0 
      objects[clearingIndex].radius = 0;

      // set plane normal x to 0 
      objects[clearingIndex].pn[0] = 0;

      // set plane normal y to 0
      objects[clearingIndex].pn[1] = 0;

      // set plane normal z to 0
      objects[clearingIndex].pn[2] = 0;

      // set width to 0
      objects[clearingIndex].width = 0;

      // set height to 0
      objects[clearingIndex].height = 0;
      
      // set color red to 0
      objects[clearingIndex].color[0] = 0;

      // set color green to 0
      objects[clearingIndex].color[1] = 0;

      // set color blue to 0
      objects[clearingIndex].color[2] = 0;

      // set radial a0 to 0 
      objects[clearingIndex].radialA0 = 0;

      // set radial a1 to 0
      objects[clearingIndex].radialA1 = 0;

      // set radial a2 to 0 
      objects[clearingIndex].radialA2 = 0;

      // set theta to 0 
      objects[clearingIndex].theta = 0;

      // set angular a0 to 0 
      objects[clearingIndex].angularA0 = 0;

      // set direction x to 0 
      objects[clearingIndex].direction[0] = 0;

      // set direction y to 0 
      objects[clearingIndex].direction[1] = 0;

      // set direction z to 0
      objects[clearingIndex].direction[2] = 0;

      // set specular color r to 0 
      objects[clearingIndex].specularColor[0] = 0;
      
      // set specular color g to 0      
      objects[clearingIndex].specularColor[1] = 0;
       
      // set specular color b to 0 
      objects[clearingIndex].specularColor[2] = 0;

      // set diffuse color r to 0 
      objects[clearingIndex].diffuseColor[0] = 0;

      // set diffuse color g to 0 
      objects[clearingIndex].diffuseColor[1] = 0;

      // set diffuse color b to 0
      objects[clearingIndex].diffuseColor[2] = 0;       
   }

   // read in data
   
      // open the file
         // function: fopen
      fh = fopen(inputFile, "r");

      // read in the first string
         // function: fscanf
      fscanf(fh, "%s", readVal);

      // while not at end of file
         // function: feof
      while (fh != NULL && !feof(fh))
      {
         // if we are a camera
	    // function: strcmp
	 if (strcmp(readVal, "camera,") == 0)
         {
            // set a camera value for the object
            tempObject.kind = 1;
         }

         // if we are a sphere 
	 if (strcmp(readVal, "sphere,") == 0)
	 { 
            // set a sphere value for the object
	    tempObject.kind = 2;
         }

         // if we are a plane
	 if (strcmp(readVal, "plane,") == 0)
         {
            // set a plane value for the object
	    tempObject.kind = 3;
         }

	 // if we are a light 
	 if (strcmp(readVal, "light,") == 0)
	 {
	    // set a light value for the object
	    tempObject.kind = 4;
	 }
	 
	 // read first data string 
	    // function: fscanf
	 fscanf(fh, "%s", readVal); 

	 // while string is not camera, plane, sphere, or light and not end of file 
	 while (!(strcmp(readVal, "camera,") == 0 || strcmp(readVal, "sphere,") == 0 || 
				 strcmp(readVal, "plane,") == 0 ||
			         strcmp(readVal, "light,") == 0) && !feof(fh))   
										
	 {
	    // if the string is width 
	       // function: strcmp
	    if (strcmp(readVal, "width:") == 0)
            {
	       // store width 
	       fscanf(fh, "%f", &tempObject.width);
	    }

	    // if the string is height 
	       // function: strcmp
	    if (strcmp(readVal, "height:") == 0)
            {
	       // store height 
	       fscanf(fh, "%f", &tempObject.height);
	    }

	    // if the string is color 	    	    
 	       // function: strcmp
	    if (strcmp(readVal, "color:") == 0)   
            {
	       // store color
	       fscanf(fh, " [%f, %f, %f]", &tempObject.color[0], &(tempObject.color[1]), &tempObject.color[2]);

            }

	    // if the string is position
	       // function: strcmp
	    if (strcmp(readVal, "position:") == 0)
            {
	       // store position 
	       fscanf(fh, " [%f, %f, %f]", &tempObject.position[0], &tempObject.position[1], &tempObject.position[2]);
            }

            // if the string is radius 
	       // function: strcmp
	    if (strcmp(readVal, "radius:") == 0)
            {
	       // store read radius
	       fscanf(fh, "%f", &tempObject.radius);
            }

            // if the string is normal	
 	       // function: strcmp
	    if (strcmp(readVal, "normal:") == 0)
            {
	       // store normal
	       fscanf(fh, " [%f, %f, %f]", &tempObject.pn[0], &tempObject.pn[1], &tempObject.pn[2]);

	       // normalize the normal 
	          // function: v3_normalize
	       v3_normalize(tempObject.pn, tempObject.pn);
            }

	    // if the string is radial a0 
	    if (strcmp(readVal, "radial-a0:") == 0)
	    {
	       // store radial a0 
	       fscanf(fh, "%f", &tempObject.radialA0);
            }

	    // if the string is radial a1
	    if (strcmp(readVal, "radial-a1:") == 0)
            {
	       // store radial a1 
	       fscanf(fh, "%f", &tempObject.radialA1);
            }

	    // if the string is radial a2
	    if (strcmp(readVal, "radial-a2:") == 0)
            {
	       // store radial a2
	       fscanf(fh, "%f", &tempObject.radialA2);
            }

	    // if the string is angular a0
	    if (strcmp(readVal, "angular-a0:") == 0)
            {
	       // store angular a0
	       fscanf(fh, "%f", &tempObject.angularA0);
            }

	    // if the string is angular a0
	    if (strcmp(readVal, "theta:") == 0)
            {
	       // store angular a0
	       fscanf(fh, "%f", &tempObject.theta);
            }



	    // if the string is direction 
	    if (strcmp(readVal, "direction:") == 0)
            {
	       // store direction
	       fscanf(fh, " [%f, %f, %f]", &tempObject.direction[0], &tempObject.direction[1], &tempObject.direction[2]);
            }

	    // if the string is specular_color
	       // function: strcmp
	    if (strcmp(readVal, "specular_color:") == 0)
            {
	       // store specular_color
	       fscanf(fh, " [%f, %f, %f]", &tempObject.specularColor[0], &tempObject.specularColor[1], &tempObject.specularColor[2]);
            }

	    // if the string is diffuse_color
	       // function: strcmp
	    if (strcmp(readVal, "diffuse_color:") == 0)
            {
	       // store diffuse_color
	       fscanf(fh, " [%f, %f, %f]", &tempObject.diffuseColor[0], &tempObject.diffuseColor[1], &tempObject.diffuseColor[2]);
            }


	    // if the string is reflectivity
	       // function: strcmp
	    if (strcmp(readVal, "reflectivity:") == 0)
            {
	       // store reflectivity 
	       fscanf(fh, "%f", &tempObject.reflectivity);
	    }

	    // read the next data string 
	       // function: fscanf
	    fscanf(fh, "%s", readVal);

         }

	 // if the object is a light 
	 if (tempObject.kind == 4)
         {

	    // store in light array 
	    lights[lightStoringIndex] = tempObject;

	    // increase number of lights
	    numLights++;

	    // increment index
	    lightStoringIndex++;
         }

	 // otherwise 
         else
         {
	    // store the object in the object array
	    objects[storingIndex] = tempObject;
	    
	    // increment array storing index
	    storingIndex++;
         }

	 // reset temp object type in case no data
	 tempObject.kind = 0;


      }

   // close the input file 
      // function: fclose
   fclose(fh);

   // for every object in the array 
   for (searchingIndex = 0; searchingIndex < MAX_OBJ; searchingIndex++)
   {
      // if it is the camera 
      if (objects[searchingIndex].kind == 1)
      { 
         // bind the camera width 
	 cameraWidth = objects[searchingIndex].width;

         // bind the camera height 
 	 cameraHeight = objects[searchingIndex].height;
      }
   }

   // set dummy object to be kind of none 
   dummyObject.kind = 0;

   // for every row on the image 
   for (rowIndex = 0; rowIndex < height; rowIndex++)
   {
      // for every col on the image
      for (colIndex = 0; colIndex < width; colIndex++)
      {
         // reset r color 
	 redIllum = 0;

	 // reset g color 
	 greenIllum = 0;

	 // reset b color
	 blueIllum = 0;

	 // calc deltaX
         deltaX = cameraWidth / width;

	 // calc deltaY
	 deltaY = cameraHeight / height;

         // calculate x of p value 
	 P[0] = (-cameraWidth / 2.0) + (deltaX / 2.0) + (colIndex * deltaX);

	 // calculate y of p value 
	 P[1] = (cameraHeight / 2.0) - (deltaY / 2.0) - (rowIndex * deltaY);

	 // put z of p value 
	 P[2] = -1;

	 // subtract r0 from p 
	    // function: v3_subtract 
	 v3_subtract(P, P, R0);

	 // normalize p
	    // function: v3_normalize
	 v3_normalize(Rd, P);

	 // shoot a ray for t and closest object, dummyObject signifies skip no object 
	    // function: shoot
	 t = shoot(R0, Rd, dummyObject, &closestObject, objects);

         // if closest object is not NULL
         if (closestObject != NULL) 
         {
   	    // get Rd * t 
	       // function: v3_scale
	    v3_scale(Rd, t); 

	    // get point 
	       // function: v3_add
	    v3_add(point, Rd, R0);

   	    // illuminate the object, get the color 
	       // function: illuminate
	    illuminate(point, *closestObject, lights, numLights, &redIllum, &greenIllum, &blueIllum, objects, 5);

	    // clamp red value 
	       // function: clamp 
            redIllum = clamp(redIllum, 0.0, 1.0); 

	    // clamp green value 
	       // function: clamp
            greenIllum = clamp(greenIllum, 0.0, 1.0); 

	    // clamp blue value 
	       // function: clamp
            blueIllum = clamp(blueIllum, 0.0, 1.0); 

            // get red pixel value 
            red = (int) (redIllum * 255);

	    // get green pixel value 
            green = (int) (greenIllum * 255);

	    // get blue pixel value 
            blue = (int) (blueIllum * 255);

	    // set value of tempNum 
            tempNum = red << 24 | green << 16 | blue << 8 | 0xff;

            // put the color on the closest object into the end pixmap
            colorMap[rowIndex * width + colIndex] = tempNum;
         }

	 // otherwise, no intersection 
	 else
         {
	    // set temp num to black 
	    tempNum = bgColor[0] << 24 | bgColor[1] << 16 | bgColor[2] << 8 | 0xff;

            // put black onto the pixmap
            colorMap[rowIndex * width + colIndex] = tempNum;

         }

         // reset closest object to NULL
  	 closestObject = NULL;
      }
   }

   // write the pixmap to the output file in p3
      // function: writeOutputFile
   writeOutputFile(outputFile, colorMap, 3, width, height, 255); 

   // free the color map
      // function: free
   free(colorMap);

}

float shoot(float *R0, float *Rd, object currentObject, object **closestObject, object *objects)
{

   // initialize variables
   float B, C, X0, Y0, Z0, Xd, Yd, Zd, Xc, Yc, Zc, D, Vd, V0;
   float lowestT = INFINITY;
   float t = INFINITY;
   object tempObject;
   int objIndex = 0;
   float discriminant, t0, t1;

   // set temp object type to 0 
   tempObject.kind = 0;

   // for every object that we have
   for (objIndex = 0; objIndex < MAX_OBJ; objIndex++)
   {
      // bind the object 
      tempObject = objects[objIndex];

      // if temp object is equal to current object 
      if ((tempObject.kind == currentObject.kind && 
		      v3_equals(tempObject.diffuseColor, currentObject.diffuseColor, .0001) && 
		      v3_equals(tempObject.position, currentObject.position, .0001)) ||
		      tempObject.kind == 0)
      {
         // continue to the next loop
	 continue;
      }

      // if the object is a sphere
      if (tempObject.kind == 2)
      {
         // bind X0 
         X0 = R0[0];

         // bind Y0 
         Y0 = R0[1];

         // bind Z0
         Z0 = R0[2];

         // bind Xd 
         Xd = Rd[0];

         // bind Yd 
         Yd = Rd[1]; 

         // bind Zd
         Zd = Rd[2];

         // bind Xc 
         Xc = tempObject.position[0];

         // bind Yc
         Yc = tempObject.position[1];

         // bind Zc
         Zc = tempObject.position[2];

         // calculate b 
         B = 2 * ((Xd * (X0 - Xc)) + (Yd * (Y0 - Yc)) + (Zd * (Z0 - Zc)));

         // calculate c
            // function: pow
         C = pow(X0 - Xc, 2) + pow(Y0 - Yc, 2) + pow(Z0 - Zc, 2) - pow(tempObject.radius, 2);

         // calc discriminant 
            // function: pow
         discriminant = pow(B, 2) - (4 * C);

         // if discriminant non-negative
         if (discriminant >= 0)
         {
            // calculate t0
  	       // function: pow
            t0 = (-B + pow(discriminant, 1/2.0)) / 2.0;

            // calculate t1 
    	    t1 = (-B - pow(discriminant, 1/2.0)) / 2.0;

            // if t0 < t1 and t0 > 0
   	    if (t0 < t1 && t0 > 0)
            {
	       // bind t to t0
	       t = t0;
            }

	    // otherwise, if t0 > t1 and t1 > 0
	    else if (t0 > t1 && t1 > 0)
            {
	       // bind t to t1 
	       t = t1;
            }

            // otherwise, both values negative 
            else
            {
	       // bind t to infinity 
               t = INFINITY;
            }

	  }

   	  // otherwise, discriminant negative, no intersection
	
      }		  
		  
      // if the object is a plane
      if (tempObject.kind == 3)
      {
         // calculate the d value 
            // function: v3_dot_product
         D = -(v3_dot_product(tempObject.position, tempObject.pn));

         // get the value of Vd
            // function: v3_dot_product
         Vd = v3_dot_product(tempObject.pn, Rd);

         // get the value of V0
            // function: v3_dot_product
         V0 = -(v3_dot_product(tempObject.pn, R0) + D);

         // get the value of t
         t0 = V0 / Vd;

         // if t is positive
         if (t0 > 0)
         {
            // bind t to t value 
   	    t = t0;
         }

         // otherwise, t is negative 

            // plane behind camera, do nothing 

      }
   
      // if the t is the lowest t so far and is positive
      if (t < lowestT && t > 0)
      {
         // rebind lowest t to new t
         lowestT = t;

         // set the new closest object
         *closestObject = &objects[objIndex];


      }

   }

   // return the lowest t value
   return lowestT;
}


void illuminate(float *point, object currentObject, object *lights, int numLights, float *red, float *green, float *blue, object *objects, int recLimit)
{
   // initialize variables
   int lightIndex = 0;
   float lightRay[3];
   float t = 0;
   float radAtten = 0;
   float angAtten = 0;
   float Idiff[3];
   float Ispec[3];
   float d = 0;
   float V0[3];
   float dotProduct = 0;
   float normal[3];
   float R[3];
   float V[3];
   float reflection[3];
   float newPoint[3];
   object *dummyObject;
   object *closestObject;
   object light;

   // reset red value 
   //*red = 0;

   // reset green value 
   //*green = 0;

   // reset blue value 
   //*blue = 0;
   

   // if the recursion limit is 0 
   if (recLimit == 0)
   {
      // return from function call
      return;
   }

   // for all lights 
   for (lightIndex = 0; lightIndex < numLights; lightIndex++)
   {
      // store light 
      light = lights[lightIndex];

      // create the ray from point to light 
         // function: v3_from_points
      v3_from_points(lightRay, point, light.position);

      // calculate d value 
         // function: v3_length 
      d = v3_length(lightRay);

      // normalize the light ray 
         // function: v3_normalize
      v3_normalize(lightRay, lightRay);

      // shoot a ray from the point to the light, see if intersectioncurrentObject, closestObject, objects);
         // function: shoot
      t = shoot(point, lightRay, currentObject, &dummyObject, objects);

      // if t is positive and less than distance from point to light 
      if (t > 0.0 && t < d)
      {
         // in shadow, continue
	 continue;
      }

      // otherwise, t not in shadow 

      // calculate raidal attenuation 

         // calculate radial attenuation value 
	 radAtten = 1.0 / ((light.radialA0) + (light.radialA1 * d) + (light.radialA2 * pow(d, 2)));


      // calculate angular attenuation

      // if theta > 0
      if (light.theta > 0.0) 
      {
	 // V0 is vector from light to point 
	    // function: v3_from_points
	 v3_from_points(V0, light.position, point);

	 // normalize v0 
	    // function: v3_normalize
	 v3_normalize(V0, V0);

	 // normalize light direction 
	    // function: v3_normalize 
	 v3_normalize(light.direction, light.direction);

	 // Vl is direction 
	 
         // calculate Vo dot Vl
	    // function: v3_dot_product
	 dotProduct = v3_dot_product(V0, light.direction);

         // if that is less than the cos(theta) 
	 if (dotProduct > cos(light.theta))
         {
            // angular attenuation present, calculate 
	       // function: pow
            angAtten = pow(dotProduct, light.angularA0);

         }

	 // otherwise, outside of cone 
	 else 
         {
	    // set to 0
	    angAtten = 0;
	 }
      }

      // otherwise, not spot light
      else
      {
         // set angular attenuation to 0
	 angAtten = 1;
		
      }

      // calculate Idiff
      
         // if the object is a sphere 
	 if (currentObject.kind == 2)
         {
            // calculate normal, normalize(point - center of sphere)
	       // function: v3_subtract
	    v3_subtract(normal, point, currentObject.position);

       }

	 // otherwise, object is a plane 
	 else 
         {
	    // normal given, set x 
	    normal[0] = currentObject.pn[0];

	    // set y 
	    normal[1] = currentObject.pn[1];

	    // set z
	    normal[2] = currentObject.pn[2];

         }

	 // normalize the normal 
	    // function: v3_normalize
	 v3_normalize(normal, normal);

         // calculate Normal dot L
	    // function: v3_dot_product
	 dotProduct = v3_dot_product(normal, lightRay);

         // if N dot L is greater than 0
	 if (dotProduct > 0)
         {
            // calculate Idiff red 
            Idiff[0] = currentObject.diffuseColor[0] * light.color[0] * dotProduct;

            // calculate Idiff green
            Idiff[1] = currentObject.diffuseColor[1] * light.color[1] * dotProduct;

            // calculate Idiff blue
            Idiff[2] = currentObject.diffuseColor[2] * light.color[2] * dotProduct;
	 }

         // otherwise
	 else
         {
            // set red to 0 
	    Idiff[0] = 0;

            // set blue to 0 
	    Idiff[1] = 0;

            // set green to 0
	    Idiff[2] = 0;
         }

      // calculate Ispec

	 // calculate R
	    // function: v3_reflect
         v3_reflect(R, lightRay, normal);

	 // store V x 
	 V[0] = point[0];

	 // store V y
	 V[1] = point[1];

	 // store V z 
	 V[2] = point[2];

	 // normalize v 
	    // function: v3_normalize 
	 v3_normalize(V, V);

	 // normalize R
	    // function: v3_normalize 
	 v3_normalize(R, R);

         // calculate V dot R
	    // function: v3_dot_product
	 dotProduct = v3_dot_product( V, R);

         // if V dot R and Idiff greater than 0
	 if (dotProduct > 0 && v3_dot_product(normal, lightRay) > 0)
         {
            // calculate Ispec red 
	       // function: pow
	    Ispec[0] = currentObject.specularColor[0] * light.color[0] * pow(dotProduct, 20);

            // calculate Ispec green
	       // function: pow
	    Ispec[1] = currentObject.specularColor[1] * light.color[1] * pow(dotProduct, 20);

            // calculate Ispec blue 
	       // function: pow
	    Ispec[2] = currentObject.specularColor[2] * light.color[2] * pow(dotProduct, 20);
         }

         // otherwise
	 else
         {
            // set red Ispec to 0
	    Ispec[0] = 0;

            // set green Ispec to 0
	    Ispec[1] = 0;

            // set blue Ispec to 0
	    Ispec[2] = 0;
	 }

      // calc value, add to R of color 
      *red += radAtten * angAtten * (Ispec[0] + Idiff[0]);

      // calc value, add to G of color 
      *green += radAtten * angAtten * (Ispec[1] + Idiff[1]);

      // calc value, add to B of color
      *blue += radAtten * angAtten * (Ispec[2] + Idiff[2]);

      // calc reflection vector (view about normal)
         // function: v3_reflect
      v3_reflect(reflection, point, normal);

      // normalize the reflection 
         // function: v3_normalize
      v3_normalize(reflection, reflection);

      // set closest object to nothing 
      closestObject = NULL;

      // shoot from origin with direction of reflection vector 
         // function: shoot
      t = shoot(point, reflection, currentObject, &closestObject, objects);

      // get new Rd * t
         // funciton: v3_scale
      v3_scale(reflection, t);

      // get new point 
         // function: v3_add
      v3_add(newPoint, point, reflection);

      // if closest object exists 
      if (closestObject != NULL)
      { 
         // illuminate with one less than current limit 
            // function: illuminate
         illuminate(newPoint, *closestObject, lights, numLights, red, blue, green, objects, recLimit - 1);
      }
   }
}

float clamp(float clampVal, float low, float high)
{
   // if the value is less than low 
   if (clampVal < low)
   {
      // return low 
      return low;
   }

   // otherwise, if value higher than hi
   else if (clampVal > high)
   { 
      // return high
      return high;
   }

   // otherwise, valid value, return given val 
   return clampVal;
 


}

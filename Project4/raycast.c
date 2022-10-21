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
	 float direction;

      };


      float position[3];
      float diffuseColor[3];
      float color[3];

   

} object;

// Function Prototypes
void raycast(int width, int height, char *inputFile, char *outputFile);

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

      // create other variables
      FILE *fh;
      char readVal[20];
      object tempObject, *closestObject = NULL;
      int clearingIndex = 0, storingIndex = 0, objIndex = 0;
      int rowIndex = 0, colIndex = 0, searchingIndex = 0;
      int red, green, blue;
      int bgColor[] = {0, 0, 0};
      float cameraWidth, cameraHeight;
      float B, C, X0, Y0, Z0, Xd, Yd, Zd, Xc, Yc, Zc, D, Vd, V0;
      float deltaX, deltaY, P[3], Rd[3]; 
      float lowestT = INFINITY, t = INFINITY; 
      float R0[] = {0, 0, 0};
      float discriminant, t0, t1;
      uint32_t *colorMap = (uint32_t *)( malloc(width * height * sizeof(uint32_t)));
      uint32_t tempNum;
      
      // set temp object type to 0 
      tempObject.kind = 0;

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

      // set radial a1 to 0

      // set radial a2 to 0 

      // set theta to 0 

      // set angular a0 to 0 

      // set direction x to 0 

      // set direction y to 0 

      // set direction z to 0
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

	    // set a light value for the object
	 
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

	       // store radial a0 

	    // if the string is radial a1

	       // store radial a1 

	    // if the string is radial a2

	       // store radial a2

	    // if the string is angular a0

	       // store angular a0

	    // if the string is direction 

	       // store direction

	    // read the next data string 
	       // function: fscanf
	    fscanf(fh, "%s", readVal);

         }

	 // if the object is a light 

	    // store in light array 

	    // increase number of lights

	 // othrewise 

	    // store the object in the object array
	    objects[storingIndex] = tempObject;

	 // increment array storing index
	 storingIndex++;
	 
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

   // for every row on the image 
   for (rowIndex = 0; rowIndex < height; rowIndex++)
   {
      // for every col on the image
      for (colIndex = 0; colIndex < width; colIndex++)
      {
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

         // for every object that we have
	 for (objIndex = 0; objIndex < MAX_OBJ; objIndex++)
         {
            // bind the object 
	    tempObject = objects[objIndex];

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
	       closestObject = &(objects[objIndex]);

	    }


	   }

	   // for all lights 

	      // shoot out a ray from the intersection 
	         // function: shoot

	   // if the t from shoot is positive TODO: CONTINUE THINKING HERE

           // reset t 
	   t = INFINITY;

	   // reset lowest t
	   lowestT = INFINITY;

	   // if closest object is not NULL
	   if (closestObject != NULL)
           {

	      // get red pixel value 
	      red = (int) (closestObject->color[0] * 255);

	      // get blue pixel value 
              green = (int) (closestObject->color[1] * 255);

	      // get green pixel value 
              blue = (int) (closestObject->color[2] * 255);

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

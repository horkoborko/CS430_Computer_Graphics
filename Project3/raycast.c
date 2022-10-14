// Header Files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
   int kind; 

   union 
   {
      // sphere properties 
      struct 
      {
        float position[3];
	float radius;
      };

      // plane properties 
      struct 
      {
         float pn[3];  // plane normal
         float d; 

      };

      // camera properties 
      struct 
      {
         float width; 
	 float height;

      };

      float color[3];

   };

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
      FILE *fh;
      char readVal[20];
      object tempObject;
      int clearingIndex = 0, storingIndex = 0, objIndex = 0;
      int rowIndex = 0, colIndex = 0, searchingIndex = 0;
      float cameraWidth, cameraHeight;
//      float B, C, X0, Y0, Z0, Xd, Yd, Zd;
      float t = -INFINITY; 

      // set temp object type to 0 
      tempObject.kind = 0;

   // for every object in the array 
   for (clearingIndex = 0; clearingIndex < MAX_OBJ; clearingIndex++)
   {
      // set its type to be nothing 
      objects[clearingIndex].kind = 0;
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

         // if we are a sphere  TODO CAN WE EXPECT UPPER CASE NAMES OF OBJECTS IN THE FILE?
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
	 
	 // read first data string 
	    // function: fscanf
	 fscanf(fh, "%s", readVal); 

	 // while string is not camera, plane, or sphere and not end of file 
	 while (!(strcmp(readVal, "camera,") == 0 || strcmp(readVal, "sphere,") == 0 || 
				 strcmp(readVal, "plane,") == 0) && !feof(fh))  // TODO: SEE IF FEOF HERE IS CUTTING 
										// OFF LAST INPUT VALUE FROM FILE
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
	       fscanf(fh, " [%f, %f, %f]", &(tempObject.color[0]), &tempObject.color[1], &tempObject.color[2]);
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
            }

	    // read the next data string 
	       // function: fscanf
	    fscanf(fh, "%s", readVal);

         }

	 // store the object in the array
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

   // for every row on the image TODO: THINK IF NEED TO DEAL WITH INCOMPLETE DATA HERE
   for (rowIndex = 0; rowIndex < height; rowIndex++)
   {
      // for every col on the image
      for (colIndex = 0; colIndex < width; colIndex++)
      {
         // for every object that we have
	 for (objIndex = 0; objIndex < MAX_OBJ; objIndex++)
         {
            // bind the object 
	    tempObject = objects[objIndex];

	    // if the object is a sphere
	    if (objects[objIndex].kind == 2)
            {
/*               // normalize Rd (normal vector)

               // bind Xd 
	       Xd = tempObject.pn[0];

	       // bind Yd 
	       Yd = tempObject.pn[1];

	       // bind Zd
	       Zd = tempObject.pn[2];

	       // bind X0 
	       X0 = tempObject.position[0];

               // bind Y0 
	       Y0 = tempObject.position[1];

               // bind Z0
	       Z0 = tempObject.position[2];

	       // calculate b  TODO: IS Rd R0 NORMALIZED?

	       // calculate c

	       // calculate t0

	       // calculate t1 

	       // if t0 < t1 and t0 > 0

	          // bind t to t0

	       // otherwise, if t0 > t1 and t1 > 0

	          // bind t to t1 

               // otherwise, both values negative 

*/	          // bind t to negative infinity 
            }		  
		  
            // if the object is a plane
	    if (tempObject.kind == 3)
            {
	       // calculate single plane t

	    }

            // if the t is the lowest t so far

               // rebind lowest t to new t

               // set the new closest object
	   }

           // reset t

           // put the color on the closest object into the end pixmap

           // reset closest object to first object
      }
   }

   // write the pixmap to the output file in p3


}

// Header Files
#include <stdio.h>
#include <stdbool.h>

// Structures 
struct plane 
{
   int colorArray[3];
   float position[3];
   int normal[3];
   bool closestObject; 

} plane;

struct sphere
{
   int colorArray[3];
   float position[3];
   int radius; 
   bool closestObject;

} sphere; 

struct camera
{
   int width; 
   int height; 
   int position[3];
} camera;

// Function Prototypes
void raycast(int width, int height, char *inputFile, char *outputFile);

// Main Function 
int main()
{
   // if the program was called with 5 total arguments 

      // raycast the input into output 
         // function: raycast
	
   // otherwise, improper format 

      // print improper format

   return 0;
}

// Function Implementation
void raycast(int width, int height, char *inputFile, char *outputFile)
{
   // initalize variables 

   // read in data 
    
      // open the file 
         // function: fopen 

      // while not at end of file 

	 // reset flags

         // read in the first string TODO: CAN THE OBJECTS BE IN ANY ORDER? I>E> SPHERE CAMERA PLANE?

         // if we are a camera 

	    // create struct

            // set a camera flag 
	    
         // if we are a sphere

	    // create struct

            // set a sphere flag 
	    
         // if we are a plane 

	    // create struct

            // set a plane flag 
	        
         // if we are not at the end of the file 

            // if we are a camera 

               // read in width 

	    // otherwise, sphere or plane 

               // read in color 

         // if we are not at the end of the file 

            // if we are a camera 

	       // read in height 

            

   // for every x on the image 

      // for every y on the image 

         // for every object that we have 

            // calculate the t of each object 

            // if the t is the lowest t so far 

               // rebind lowest t to new t 

               // set the new closest object 

           // reset t 

           // put the color on the closest object into the end pixmap 

           // reset closest object to first object 

   // write the pixmap to the output file in p3


}

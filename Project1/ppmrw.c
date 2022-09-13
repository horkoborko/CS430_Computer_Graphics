// Header Files
#include <stdio.h> // fopen, fscanf, and friends
#include <stdlib.h> // malloc and friends 
#include <stdint.h> // standard integer types 
#include <ctype.h> // isspace and friends 
#include <stdbool.h>		   
#include <string.h>

// Global Constants

// Function Prototypes
bool readInputFile( char *inputFile, uint32_t **colorMap, int *width, int *height, int *maxColorVal);
void writeOutputFile( char *outputFile, uint32_t **colorMap, int writingNumber);

// Main Function
int main()
{
   // declare variables 
   
   // find out whether converting to p3 or to p6 via arguments 

   // read in the input file 
      // function: readInputFile

   // if the input was good
	   
      // write out the output 
         // function: writeOutputFile

   // return 0
   return 0;
}

// Function Implementation
bool readInputFile( char *inputFile, uint32_t **colorMap, int *width, int *height, int *maxColorVal)
{
   // initialize variables 
   
   // if the input file opens and we are not at the end of the file 

      // read the first character 

      // if the first character is a P and we are not at the end of the file 
       
	 // read the second character 

         // if the second character is a 3 or a 6

	    // set valid input to true  

	 // if not at end of file and valid input is true
   
            // read the next character

	    // while not at end of file and character is space 

	       // read string until next white space (%s on fscanf)

	    // if the character is a space 

	       // reached end of file, return false 

	    // otherwise, found width, store width

	    // while not at end of file and character is space 

	       // read string until next white space

	    // if the character is a space 

	       // reached end of file, return false 
	
	    // 

	    // while not at end of file and character is space 

	       // read next character 

	    // if the character is a space 

	       // reached end of file, return false 

	    // read max color value 
	 
	    // clear next whitespace 
	 
	    // put the board of data into the passed in array 

	       // if the file is a p3 file 

	          // for every row in the data 

	             // for every column in the data 

	                // pack the data into a single number 
	
	                // store that number in the array 

	          // remove end line 

	       // if the file is a p6 file 

	          // while not at the end of the file 

	              // read the next bit 
		 
	              // insert the next bit into a temporary array 

	              // after the number of bits in the array is 8

	                  // calculate ascii number 

	                  // reset number of bits in array

	                  // insert ascii number into return array 

	       // return true

	 // otherwise, fall through and return false, not p3 or p6

      // otherwise, fall through and return false, not P format
      
      // close the input file 

   // otherwise, no file, return false	

   



   return false; //STUB RETURN   
}


void writeOutputFile( char *outputFile, uint32_t **colorMap, int writingNumber)
{
   // initialize variables 

   // open the output file 
   
   // if the file we are writing is a p3

      // write the magic number into the file 

   // otherwise, if the file we are writing to is a p6 

      // write the magic number into the file 

   // write a space into the file 

   // write the width into the file 

   // write a space into the file 

   // write the height into the file 
   
   // write a space into the file 

   // write the max color value into the file 

   // write a newline into the file 

   // if the file we are writing to is a p3 

      // for every row in the grid 
	
	   // for every column in the grid 

	      // write the red value in ascii

	      // write the blue value in ascii 

	      // write the green value in ascii 

	      // write the alpha value in ascii (100% opacity)

	      // write 2 spaces to the file 

	   // add an endline to the file 

   // otherwise, if the file we are writing to is a p6 

      // for every row in the grid 
	
	   // for every column in the grid 

	      // write the red value in binary

	      // write the blue value in binary 

	      // write the green value in binary 

	      // write the alpha value in binary (100% opacity)

	      // write 2 spaces to the file 

	   // add an endline to the file 




}

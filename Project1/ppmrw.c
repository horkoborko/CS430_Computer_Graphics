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
bool readUntilNextChar( FILE *filePointer, char *readNum);

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
/*
   uint32_t *image; // Storage of read file, adjusted for P3 or P6
   char magicNumber;
   int headerBytes;

   FILE *fh = fopen(inputFile, "r");
   fread(colorMap, sizeof(uint32_t), headerBytes, fh);
   fclose(fh);

   char currentLine;
   while(cursor != '\0') {
     fgets(char *currentLine, int size, FILE *fh);
     for(int i; i <= sizeof(currentLine); i++) {
       if(currentLine[i] == 'P') {
	 char magicNumber = currentLine[i] + currentLine[i+1];
       }
       if(currentLine[i] == '\n') {
	 
       }
     }
   }

*/

   // initialize variables 

   // if the input file opens and we are not at the end of the file 

      // read the first string
         // function: fscanf 

      // if the string is p3 or p6 
       
	 // if not at end of file 
   
	    // get the next numerical value 
	       // function: readUntilNextNum

	    // if the function returned false (no num found)

	       // print error 

	       // reached end of file, return false 

	    // otherwise, found width, store width

            // get the next numerical value 
	       // function: readUntilNextNum
	
	    // if the function returned false (no num found)

	       // print error 

	       // reached end of file, return false    

	    // otherwise, found height, store height

	    // get the next numerical value
	       // function: readUntilNextNum

	    // if the function returned false (no num found)

	       // print error 

	       // reached end of file, return false    

	    // otherwise, found max color val, store value 
	 
	    // clear next whitespace 
	       // function: fgetc

	    // get memory for array 
	    // malloc (width * height * sizeof(uint32_t);
	 
	    // put the board of data into the passed in array 

	       // if the file is a p3 file 
	          // function: strcmp

	          // for every row in the data 

	             // for every column in the data 

	                // pack the data into a single number 
	
	                // store that number in the array 

	          // remove end line 

	       // if the file is a p6 file 

	          // for every row in the file 

	             // for every column in the file 

	                // convert the binary value to ascii 

	                // pack the ascii number into a single number 
			// store that number in the array 
	
	            // remove end line 

	       // return true

      // otherwise

         // print error 

	 // return false, not proper format
      
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
      // function: fprintf

      // for every row in the grid 
	
	   // for every column in the grid 

	      // write the red value in ascii

	      // write the blue value in ascii 

	      // write the green value in ascii 

	      // write the alpha value in ascii (100% opacity)

	      // write 2 spaces to the file 

	   // add an endline to the file 

   // otherwise, if the file we are writing to is a p6 
      // function: fprintf

      // for every row in the grid 
	
	   // for every column in the grid 

	      // write the red value in binary

	      // write the blue value in binary 

	      // write the green value in binary 

	      // write the alpha value in binary (100% opacity)

	      // write 2 spaces to the file 

	   // add an endline to the file 




}

bool readUntilNextNum( FILE *filePointer, char *readNum)
{
   
   // read the next character

   // while not at end of file and character is space or end of line character or a pound sign  

      // if the character was a pound sign 

         // fgets in order to remove the comment line 

      // read string until next white space (%s on fscanf)

      // if the character is a space 

         // reached end of file, return false 

   // after leaving loop, have valid value, put value to return 

   // return true

   return false; // STUB RETURN
}


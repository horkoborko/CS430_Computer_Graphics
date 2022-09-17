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
   uint32_t *image; // Storage of read file, adjusted for P3 or P6
   char magicNumber;
   int maxColorValue; 

   FILE *fh = fopen(inputFile, "r");
   fread(colormap, sizeof(uint32_t), headerBytes, fh);
   fclose(fh);

   fgets(char *currentLine, int size, FILE *fh);
   if(currentLine[0] == 'P' && (currentLine[1] == '3' || currentLine[1] == '6')) {
     magicNumber = currentLine[0] + currentline[1];
   }
   else {
     fprint("ERROR: Invalid PPM Magic Number");
   }\
   
   char currentLine;

   // Reading Header Section
   while(currentLine != '\0') {
     fgets(char *currentLine, int size, FILE *fh);
       for(int i; i <= sizeof(currentLine); i++) {
	 if(currentLine[i] == '#' || currentLine[i] == '\n') {
	   break;
	 }
	 elif(currentLine[i] == ' ') {
	   continue;
	 }
	 else {
	   // I would like your commentary as to how we can reliably detect the correct width/height/max_color_value,
	   // in case Palmer throws in an extra value somewhere in the header or lacks information
	 }
       }
   }

   //Reading Image Data
   while(currentLine != '\0') {
     return //dummy value for now
   }

	       // read string until next white space (%s on fscanf)

	    // if the character is a space 

	       // reached end of file, return false 

	    // otherwise, found width, store width

	    // while not at end of file and character is space 

	       // read string until next white space

	    // if the character is a space 

	       // reached end of file, return false 

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
      
      // close the input file 

   // otherwise, no file, return false	

   



   return false; //STUB RETURN   
}


void writeOutputFile( char *outputFile, uint32_t **colorMap, int writingNumber)
{
  FILE *fh = fopen(outputFile, "w");
  if(writingNumber == 3) {
    fwrite(fh, 
  }
  elif(writingNumber == 6) {

  }
  else {

  }
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

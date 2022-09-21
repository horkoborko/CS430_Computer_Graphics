// Header Files
#include <stdio.h> // fopen, fscanf, and friends
#include <stdlib.h> // malloc and friends 
#include <stdint.h> // standard integer types 
#include <ctype.h> // isspace and friends 
#include <stdbool.h>		   
#include <string.h>
#include <inttypes.h>

// Global Constants
const int MAX_IN_LENGTH = 40;

// Function Prototypes
bool readInputFile( char *inputFile, uint32_t *colorMap, int *width, int *height, int *maxColorVal);
void writeOutputFile( char *outputFile, uint32_t *colorMap, int writingNumber);
bool readUntilNextNum( FILE *filePointer, int *readNum);
void checkResult(bool inputBool);

// Main Function

int main(int argc, char **argv)
{
   // declare variables 
   bool goodInputFile = false;
   int magicNumToConvert;
   char inputFileName[MAX_IN_LENGTH], outputFileName[MAX_IN_LENGTH];
   int width, height, maxColorVal;
   uint32_t *colorMap = NULL;
   
   // if we have 4 arguments
   if (argc == 4)
   {
      // find out whether converting to p3 or to p6 via arguments 
      magicNumToConvert = (int)(*argv[1]) - '0';

      // get the input file to read from arguments 
         // function: strcpy
      strcpy(inputFileName, argv[2]);

      // get the output file to write to from arguments 
         // function: strcpy
      strcpy(outputFileName, argv[3]);

      // read in the input file 
         // function: readInputFile
      goodInputFile = readInputFile( inputFileName, colorMap, &width, &height, &maxColorVal);

      // if the input was good
      if (goodInputFile)
      { 
         // write out the output 
            // function: writeOutputFile
         writeOutputFile( outputFileName, colorMap, magicNumToConvert);

      }
   }

   // otherwise, invalid num of arguments 
   else 
   {   
      // print error 
         // function: printf
      printf("ERROR: Improper num of argument recieved. Expected 4, got %d\n", argc);
   }

   // return 0
   return 0;
}

// Function Implementation
bool readInputFile( char *inputFile, uint32_t *colorMap, int *width, int *height, int *maxColorVal)
{
   // initialize variables 
   bool goodVal = false;
   char magicNum[5];
   int nextValue, red, green, blue, readValues;
   uint8_t red8, green8, blue8;
   FILE *fh;
   int rowIndex = 0, colIndex = 0;
   uint32_t tempNum = 0;
   
   // open the input file 
      // function: fopen
   fh = fopen(inputFile, "r");

   // if the input file opens and we are not at the end of the file 
      // function: feof
   if (fh != NULL && !feof(fh) )
   {
      // read the first string
         // function: fscanf 
      fscanf(fh, "%s", magicNum); 

      // if the string is p3 or p6 
         // function: strcmp
      if (strcmp("P3", magicNum) == 0 || strcmp("P6", magicNum) == 0)
      {
       
	 // if not at end of file 
	    // function: feof
	 if (!feof(fh))
         { 
	    // get the next numerical value 
	       // function: readUntilNextNum
	    goodVal = readUntilNextNum(fh, &nextValue);

	    // check result 
	       // function: checkResult
	    checkResult(goodVal);

	    // found width, store width
            *width = nextValue;

            // get the next numerical value 
	       // function: readUntilNextNum
            goodVal = readUntilNextNum(fh, &nextValue);

	    // check result 
	       // function: checkResult
	    checkResult(goodVal);

	    // found height, store height
            *height = nextValue;

	    // get the next numerical value
	       // function: readUntilNextNum
            goodVal = readUntilNextNum(fh, &nextValue);

	    // check result 
	       // function: checkResult
	    checkResult(goodVal);

	    // found max color val, store value 
	    *maxColorVal = nextValue; 

	    // if the max val is greater than 255 
	    if (*maxColorVal > 255)
            {
	       // set good val to false 
	       goodVal = false;
            }

	    // check result 
	       // function: checkResult
	    checkResult(goodVal);
	 
	    // get memory for array 
	    colorMap = (uint32_t *)( malloc(*width * *height * sizeof(uint32_t)));

	    // put the board of data into the passed in array 

	       // if the file is a p3 file 
	          // function: strcmp
               if (strcmp("P3", magicNum) == 0)
               {
	          // for every row in the data 
		  for (rowIndex = 0; rowIndex < *height; rowIndex++)
		  {
	             // for every column in the data 
                     for (colIndex = 0; colIndex < *width; colIndex++)
		     {

	                // read the 3 rgb values in with fscanf
			   // function: fscanf
			readValues = fscanf(fh, " %d %d %d ", &red, &green, &blue);

	                // if we read 3 values with fscanf 
			if (readValues == 3)
                        {
	                   // if any value is greater than the max value 
			   if (red > *maxColorVal || green > *maxColorVal || blue > *maxColorVal)
                           {
	                      // print error 
			         // function: fprintf
			      fprintf(stderr, "ERROR: Value in file over max color val.\n");

			      // exit 0
			      exit(0);
                           }

	                   // pack the 3 values into a single 32 bit int number 
			   tempNum = red << 24 | green << 16 | blue << 8 | 0xff;


	                   // store that number in the array 
			   colorMap[rowIndex * *width + colIndex] = tempNum;

			}

	                // otherwise, end of file 
			else
			{ 
			   // print error 
			      // function: checkResult
			   checkResult(false);

		        }

		     }
		  }

	       }

	       // if the file is a p6 file  
	       if (strcmp("P6", magicNum) == 0)
               {
	          // for every row in the file 
                  for (rowIndex = 0; rowIndex < *height; rowIndex++)
	          {
	             // for every column in the file 
                     for (colIndex = 0; colIndex < *width; colIndex++)
		     {
	                // read the next 3 bytes in
			   // function: fread
			readValues = fread(&red8, 1, 1, fh);
                        fread(&blue8, 1, 1, fh);
                        fread(&green8, 1, 1, fh);

	                // if fread could read the number 
	
     	                   // if the value is greater than the max value 

	                      // print error 
			         // function: printf

	                      // return false 

	                   // pack the ascii number into a single number 

			   // store that number in the array 

	                // otherwise, end of input file 

	                   // print error 
			      // function: printf
			   
	                   // return false, bad input file 	    
	
		     }
                  }
	       }
	 }

	       // return true TODO: SEE IF NEEDS TO BE HERE
      }
   }

      // otherwise

         // print error 
	    // function: fgetc

	 // return false, not proper format
      
      // close the input file 
         // function: fclose

   // otherwise, no file, return false	

   



   return false; //STUB RETURN   
}


void writeOutputFile( char *outputFile, uint32_t *colorMap, int writingNumber)
{
   // initialize variables 

   // open the output file 
      // function: fopen
   
   // if the file we are writing is a p3

      // write the magic number into the file 
         // function: fprintf

   // otherwise, if the file we are writing to is a p6 

      // write the magic number into the file 
         // function: fprintf

   // write a space, then width, then space, then height, then space, then max color val, ended by newline
      // function: fprintf

   // if the file we are writing to is a p3 
      // function: fprintf

      // for every row in the grid 
	
	   // for every column in the grid 

	      // write the red value in ascii, followed by blue, followed by green TODO: NEED ALPHA HERE?

	      // write 2 spaces to the file 

	   // add an endline to the file 

   // otherwise, if the file we are writing to is a p6 
      // function: fprintf

      // for every row in the grid 
	
	   // for every column in the grid 

	      // write the red value in binary
	         // function: fwrite

	      // write the blue value in binary 
	         // function: fwrite

	      // write the green value in binary 
	         // function: fwrite

	      // write the alpha value in binary (100% opacity) TODO: NEED TO DO THIS?
	         // function: fwrite

	   // add an endline to the file 




}

bool readUntilNextNum( FILE *filePointer, int *readNum)
{
   // initialize variables  
   int nextChar, stringLength = 0, clearingIndex = 0;
   char tempStr[100], tempNum[10];
   int calcInt = 0, convertingIndex = 0;
   float multiplier = 0.0;

   // for every number in the temp num from 0 to 10
   for (clearingIndex = 0; clearingIndex < 10; clearingIndex++)
   { 
      // clear it 
      tempNum[clearingIndex] = 0;
   }

   // read the next character
      // function: fgetc
   nextChar = fgetc(filePointer);

   // while not at end of file and character is space or end of line character or a pound sign  
      // function: isspace
   while (!feof(filePointer) && (isspace((char)(nextChar)) || nextChar == (int)'#'))
   {

      // if the character was a pound sign 
      if (nextChar == (int)('#'))
      {
         // fgets in order to remove the comment line 
	    // function: fgets
	 fgets(tempStr, 100, filePointer); 
      }

      // read string until next white space (%s on fscanf)
         // function: fscanf
      nextChar = fgetc(filePointer);

   }

   // if the character is a space, pound sign, or newline
      // function: isspace
   if ( isspace((char)(nextChar)) || nextChar == (int)'#')
   {
      // reached end of file, print error 
         // function: checkResult
      checkResult(false);
   }

   // insert first number in string 
   tempNum[0] = nextChar;

   // set str len to 1
   stringLength = 1;

   // set multiplier to .1
   multiplier = .1;

   // while not at whitespace or pound 
   while (! (isspace((char)(nextChar)) || nextChar == (int)'#'))
   {
      // get next char 
         // function: fgetc
      nextChar = fgetc(filePointer);

      // append to temp string 
         // function: strcat
      strcat(tempNum, (char *)&nextChar);

      // add to str len
      stringLength++;

      // mulitply multiplier by 10
      multiplier = multiplier * 10;

   }

   // set read num to 0
   *readNum = 0;

   // for every number in temp num, from 0 to strlen - 1
   for (convertingIndex = 0; convertingIndex < stringLength - 1; convertingIndex++)
   { 
      // turn value in string into int
      calcInt = tempNum[convertingIndex] - '0';

      // multiply by multiplier and add to return 
      *readNum += calcInt * multiplier;

      // divide multiplier by 10
      multiplier = multiplier / 10;
   }

   // return true
   return true;
}

void checkResult(bool inputBool)
{
   // initialize variables 
   
   // if the bool is false 
   if (!inputBool)
   {
      // print error code to std error 
         // function: fprintf
      fprintf(stderr, "Error: %s\n", strerror(errno));

      // exit 0
      exit(0);
   }

   // otherwise, do nothing 

}

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
bool readInputFile( char *inputFile, uint32_t **colorMap, int *width, int *height, int *maxColorVal);
void writeOutputFile( char *outputFile, uint32_t *colorMap, int writingNumber, int width, int height, int maxColorVal);
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
      goodInputFile = readInputFile( inputFileName, &colorMap, &width, &height, &maxColorVal);

      // if the input was good
      if (goodInputFile)
      { 
         // write out the output 
            // function: writeOutputFile
         writeOutputFile( outputFileName, colorMap, magicNumToConvert, width, height, maxColorVal);

      }
   }

   // otherwise, invalid num of arguments 
   else 
   {   
      // print error 
         // function: printf
      printf("Input Format: ppmrw MAGIC_NUM INPUT_FILE OUTPUT_FILE\n");
   }

   // return 0
   return 0;
}

// Function Implementation
bool readInputFile( char *inputFile, uint32_t **colorMap, int *width, int *height, int *maxColorVal)
{
   // initialize variables 
   bool goodVal = false;
   char magicNum[5];
   int nextValue, red, green, blue, readValues;
   int redRead, blueRead, greenRead;
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
	 // if the string is p6 
	 if (strcmp("P6", magicNum) == 0)
         {

	    // close the input file 
	       // function: fclose 
	    fclose(fh);

	    // reopen the input file in binary 
	       // function: fopen
	    fh = fopen(inputFile, "rb");

	    // re-read the magic number to put the file handle at the proper place
	       // function: fscanf
	    fscanf(fh, "%s", magicNum);        
	 }
       
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
	       // function: malloc
	    *colorMap = (uint32_t *)( malloc(*width * *height * sizeof(uint32_t)));

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
			   (*colorMap)[rowIndex * *width + colIndex] = tempNum;

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
			redRead = fread(&red8, 1, 1, fh);
                        greenRead = fread(&green8, 1, 1, fh); 
                        blueRead = fread(&blue8, 1, 1, fh);

	                // if fread could read the number and not on last run
			if (redRead && blueRead && greenRead )
                        {	
     	                   // if the value is greater than the max value 
			   if (red8 > *maxColorVal || blue8 > *maxColorVal || green8 > *maxColorVal)
                           {
	                      // print error 
			         // function: printf
			      fprintf(stderr, "ERROR: Value found higher than max value.\n");

	                      // return false 
			      return false;
			   }

	                   // pack the 3 values into a single 32 bit int number 
			   tempNum = red8 << 24 | green8 << 16 | blue8 << 8 | 0xff;

	                   // store that number in the array 
			   (*colorMap)[rowIndex * *width + colIndex] = tempNum;

			}

	                // otherwise, end of input file 
			else
                        {
			   // print error 
			      // function: checkResult
			   checkResult(false);
			}
	
		     }
                  }
	       }
	 }

	 // return true 
	 return true;
      }
   }

      // otherwise
      else
      {

         // print error 
	    // function: fprintf
	 fprintf(stderr, "ERROR: Not proper file format.\n");

	 // return false, not proper format
	 return false;
      }
      
      // close the input file 
         // function: fclose
      fclose(fh);

   // otherwise, no file, return false	
   return false;

}


void writeOutputFile( char *outputFile, uint32_t *colorMap, int writingNumber, int width, int height, int maxColorVal)
{
   // initialize variables 
   FILE *fh;
   int rowIndex = 0, colIndex = 0;
   uint32_t tempNum;
   uint8_t red, blue, green;

   // if the file is p3 
   if (writingNumber == 3)
   {
      // open the output file in ascii
         // function: fopen
      fh = fopen(outputFile, "w");
   }

   // otherwise, file is p6 
   else 
   {
      // open output file in binary 
      fh = fopen(outputFile, "wb");
   }

   // write magic number to file 
      // function: fprintf
   fprintf(fh, "P%d\n", writingNumber);

   // write a space, then width, then space, then height, then space, then max color val, ended by newline
      // function: fprintf
   fprintf(fh, "%d %d %d\n", width, height, maxColorVal);

   // if the file we are writing to is a p3 
   if (writingNumber == 3)
   {
      // for every row in the grid 
      for (rowIndex = 0; rowIndex < height; rowIndex++)
      {	
	   // for every column in the grid 
	   for (colIndex = 0; colIndex < width; colIndex++)
           {

	      // get color map value 
              tempNum = colorMap[rowIndex * width + colIndex];

	      // write the red value in ascii, followed by blue, followed by green 
	         // function: fprintf
	      fprintf(fh, "%d %d %d \n", tempNum >> 24, tempNum >> 16 & 0xff, tempNum >> 8 & 0xff);

	   }

      }
   } 

   // otherwise, file is p6
   else 
   {
      // for every row in the grid 
      for (rowIndex = 0; rowIndex < height; rowIndex++)
      {	
	   // for every column in the grid 
	   for (colIndex = 0; colIndex < width; colIndex++)
           {

	      // get color map value 
              tempNum = colorMap[rowIndex * width + colIndex];

	      // get red value 
	      red = tempNum >> 24;

	      // get green value 
	      green = tempNum >> 16 & 0xff;

	      // get blue value 
	      blue = tempNum >> 8 & 0xff;

	      // write the red value in binary
	         // function: fwrite
	      fwrite(&red, 1, 1, fh);

	      // write the green value in binary 
	         // function: fwrite
	      fwrite(&green, 1, 1, fh);

	      // write the blue value in binary 
	         // function: fwrite
	      fwrite(&blue, 1, 1, fh);
            }
      }
   }




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
      // print error 
         // function: printf
      fprintf(stderr, "Error: End of File Unexpectedly Reached.\n");
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
      fprintf(stderr, "Error: Improper Result from File.\n");

      // exit 0
      exit(0);
   }

   // otherwise, do nothing 

}

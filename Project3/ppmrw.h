// Function Prototypes
bool readInputFile( char *inputFile, uint32_t **colorMap, int *width, int *height, int *maxColorVal);
void writeOutputFile( char *outputFile, uint32_t *colorMap, int writingNumber, int width, int height, int maxColorVal);
bool readUntilNextNum( FILE *filePointer, int *readNum);
void checkResult(bool inputBool);

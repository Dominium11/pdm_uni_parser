#include "tsCommon.h"
#include "tsTransportStream.h"

//=============================================================================================================================================================================

int main(int argc, char *argv[ ], char *envp[ ])
{
  FILE * pFile;
  char * buffer;
  uint8_t * pHeaderBuffer;
  /*
  char * input_file;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input_file> [options]\n", argv[0]);
    return EXIT_FAILURE;
  }
  input_file = "example_new.ts";
  */

  pFile = fopen ("example_new.ts", "rb" );
  if (pFile==NULL) {printf("File Error on open"); exit (1);}

  buffer = (char*) malloc (sizeof(char)*188);
  if (buffer == NULL) {printf("File Error on memory allocate"); exit (2);}

  xTS_PacketHeader    TS_PacketHeader;
  int32_t TS_PacketId = 0;

  while(fread(buffer,1,188,pFile) == 188)
  {
    pHeaderBuffer = (uint8_t*)buffer;

    TS_PacketHeader.Reset();
    TS_PacketHeader.Parse(pHeaderBuffer);

    printf("%010d ", TS_PacketId);
    TS_PacketHeader.Print();
    printf("\n");

    TS_PacketId++;
  }
  
  // terminate
  fclose (pFile);
  free (buffer);

  return EXIT_SUCCESS;
}

//=============================================================================================================================================================================

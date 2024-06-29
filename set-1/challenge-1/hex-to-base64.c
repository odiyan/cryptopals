#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common.h"

#define MAX_INPUT_LENGTH 100

char *Base64String = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


char *base64_encode(unsigned char* buffer, size_t InputLength) {
  size_t OutputLength = ((InputLength + 2) / 3) * 4;
  char *OutputBuffer;
  size_t i;
  size_t j;
  size_t v;

  if (InputLength == 0)
    return NULL;

  if ((OutputBuffer = (char *)malloc(OutputLength)) == NULL) {
    printf("memory allocation for base64 encoding failed");
    exit(1);
  }
  OutputBuffer[OutputLength] = '\0';

  for (i = 0, j = 0; i < InputLength; i += 3, j += 4) {
    v = buffer[i];
    v = i+1 < InputLength ? v << 8 | buffer[i+1] : v << 8;
    v = i+2 < InputLength ? v << 8 | buffer[i+2] : v << 8;
    OutputBuffer[j] = Base64String[(v >> 18) & 0x3f];
    OutputBuffer[j+1] = Base64String[(v >> 12) & 0x3f];
    if ((i+1) < InputLength)
      OutputBuffer[j+2] = Base64String[(v >> 6) & 0x3f];
    else
      OutputBuffer[j+2] = '=';
    if ((i+2) < InputLength)
      OutputBuffer[j+3] = Base64String[v & 0x3f];
    else
      OutputBuffer[j+3] = '=';
  }
 
  return OutputBuffer;
}

int main() {
  char HexArray[MAX_INPUT_LENGTH + 1];
  unsigned char BinaryArray[MAX_INPUT_LENGTH / 2 + 1];

  printf("enter a hex (Max 100 char): ");
  if (fgets(HexArray, sizeof(HexArray), stdin) == NULL) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }
  HexArray[strcspn(HexArray, "\n")] = '\0';
  size_t InputLength = strlen(HexArray);

  if (InputLength % 2 != 0) {
    printf("not a valid hex");
    exit(1);
  }

  if (hex_to_bytes(HexArray, BinaryArray, InputLength) < 0) {
    printf("not a valid hex");
    exit(1);
  }

  for(size_t i = 0; i < InputLength / 2; ++i) {
    printf("%02x", BinaryArray[i]);
  }
  printf("\n");

  char *Base64EncodedString = base64_encode(BinaryArray, InputLength / 2);
  printf("%s\n", Base64EncodedString);
  return 0;
}

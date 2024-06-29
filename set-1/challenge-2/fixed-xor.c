#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../common.h"

#define MAX_INPUT_LENGTH 100

char *xor_buffers(unsigned char *Buffer1, unsigned char *Buffer2, size_t InputLength) {
  char* result;
  if ((result = (char *)malloc(InputLength)) == NULL) {
    printf("memory allocation  failed");
    exit(1);
  }

  result[InputLength] = '\0';
  for(size_t i = 0; i < InputLength; i++) {
    result[i] = Buffer1[i] ^ Buffer2[i];
  }
  return result;
}

int main() {

  char CharBuffer1[MAX_INPUT_LENGTH + 1];
  unsigned char HexBuffer1[MAX_INPUT_LENGTH / 2 + 1];
  char CharBuffer2[MAX_INPUT_LENGTH + 1];
  unsigned char HexBuffer2[MAX_INPUT_LENGTH / 2 + 1];

  printf("please enter the first hex string (Max 100 chars):\n");
  if (fgets(CharBuffer1, sizeof(CharBuffer1), stdin) == NULL) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }

  CharBuffer1[strcspn(CharBuffer1, "\n")] = '\0';
  size_t InputLength = strlen(CharBuffer1);

  if (InputLength % 2 != 0) {
    printf("not a valid hex");
    exit(1);
  }
  if (hex_to_bytes(CharBuffer1, HexBuffer1, InputLength) < 0) {
    printf("not a valid hex");
    exit(1);
  }

  printf("input 1: ");
  for(size_t i = 0; i < InputLength / 2; ++i) {
    printf("%02x", HexBuffer1[i]);
  }
  printf("\n");

  printf("please enter the second hex string (Max 100 chars):\n");
  if (fgets(CharBuffer2, sizeof(CharBuffer2), stdin) == NULL) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }
  CharBuffer2[strcspn(CharBuffer1, "\n")] = '\0';
  assert (InputLength == strlen(CharBuffer2));

  if (hex_to_bytes(CharBuffer2, HexBuffer2, InputLength) < 0) {
    printf("not a valid hex");
    exit(1);
  }
  printf("input 2: ");
  for(size_t i = 0; i < InputLength / 2; ++i) {
    printf("%02x", HexBuffer2[i]);
  }
  printf("\n");
  printf("xord result: ");
  char *ResultBuffer = xor_buffers(HexBuffer1, HexBuffer2, InputLength / 2);
  for(size_t i = 0; i < InputLength / 2; ++i) {
    printf("%02x", ResultBuffer[i]);
  }
  printf("\n");

}

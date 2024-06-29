#include "common.h"


int hex_char_to_int(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}

int hex_to_bytes(char* input, unsigned char* output, size_t InputLength) {
  int LowerNibble;
  int HigherNibble;

  for (int i = 0; i < InputLength / 2; i++) {
    HigherNibble = hex_char_to_int(input[i*2]);
    LowerNibble = hex_char_to_int(input[i*2+1]);
    if (HigherNibble == -1 || LowerNibble == -1)
      return -1;

    output[i] = (HigherNibble << 4) | LowerNibble;
  }
  return 0;
}

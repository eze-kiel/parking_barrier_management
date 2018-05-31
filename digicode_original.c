#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define SECRET "98765"

#define TRUE 1
#define FALSE 0

char code[sizeof(SECRET)-1];
int  code_index;

int secret_size(void) {
  return (sizeof(SECRET) - 1);
}

int digit_is_valid(char c) {
  if ((c < '0') || (c > '9')) {
    return FALSE;
  } else {
    return TRUE;
  }

}

int read_digit(void) {
  do
    code[code_index] = getchar();
  while ( !digit_is_valid(code[code_index]) );

  code_index = (code_index+1) % secret_size();

  return TRUE;
}

int check_code() {
  int i;


  for(i = 0; i < secret_size(); i++) {
    if (SECRET[i] != code[(code_index + i) % secret_size()])
      return FALSE;
  }

  return TRUE;
}

void debug_digits(void) {
  int i;
  printf("code_index: %d\n", code_index);

  printf("digits: ");
  for (i=0; i < secret_size(); i++) {
    printf("%c ", code[i]);
  }
  printf("\n");
}

int main (void) {
  code_index = 0;

  printf("sizeof: %ld\n", sizeof(SECRET));
  printf("3emechar: %c\n", SECRET[3]);
  printf("%s\n", SECRET);
  while (TRUE) {
    read_digit();

    // REMOVE BEFORE USE
    debug_digits();

    if (check_code()) {
      printf("OUVERTURE!\n");
      fflush(stdout);
      sleep(5);
      printf("FERMETURE\n");
      fflush(stdout);
    }

  }
}
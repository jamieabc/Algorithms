#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTS 100000
#define DEBUG 0

/* exit program if not input file is provided */
void check_input_parameter(int argc) {
  if (argc == 1) {
    printf("Usage: a.out [file_name]\n");
    printf("file_name is not found!");
    exit(-1);
  }
}

int read_file(const char *file_name, int *array) {
  FILE *fp = fopen(file_name, "r");
  int integer = 0;

  /* exit if file not exist */
  if (!fp) {
    printf("file '%s' doesn not exist, please check it!", file_name);
    exit(-1);
  }

  for (int i = 0; i < MAX_INTS; ++i) {
    fscanf(fp, "%d", &integer);
    if (!feof(fp)) {
      array[i] = integer;
    } else {
      return i;
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  int array[MAX_INTS], array_size = 0;

  check_input_parameter(argc);
  array_size = read_file(argv[1], array);
#ifdef DEBUG
  printf("array size %d with following content:\n", array_size);
  for (int i = 0; i < array_size; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
#endif

  return 0;
}

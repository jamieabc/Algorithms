#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #define MAX_INTS 100000 */
#define MAX_INTS 10
#define DEBUG 1

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
  return MAX_INTS;
}

void swap(int *a, int *b) {
  int temp;
  temp = *b;
  *b = *a;
  *a = temp;
}

void quick_sort(int *array, int pivot_idx, int left_idx, int right_idx) {
  int compared_idx = left_idx + 1, sorted_idx = left_idx;

#if DEBUG
  printf("pivot is %d, sort range from %d to %d, original array: \n", array[pivot_idx], array[left_idx], array[right_idx]);
  for (int i = 0; i < MAX_INTS; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
#endif

  if (right_idx - left_idx < 1) return;
  while (right_idx - compared_idx > 0) {
    if (array[compared_idx] < array[pivot_idx]) {
      swap(&array[sorted_idx], &array[compared_idx]);
      sorted_idx++;
    }
    compared_idx++;
  }

  swap(&array[pivot_idx], &array[sorted_idx - 1]);

#if DEBUG
  printf("sorted array: \n");
  for (int i = 0; i < MAX_INTS; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
#endif

  quick_sort(array, pivot_idx, pivot_idx + 1, left_idx);
  quick_sort(array, sorted_idx, sorted_idx + 1, right_idx);
}

int main(int argc, char **argv) {
  int array[MAX_INTS], array_size = 0;

  check_input_parameter(argc);
  array_size = read_file(argv[1], array);

#if DEBUG
  printf("array size %d with following content:\n", array_size);
  for (int i = 0; i < array_size; ++i) {
    printf("%d ", array[i]);
  }
  printf("\n");
#endif

  quick_sort(array, 0, 1, array_size - 1);
  return 0;
}

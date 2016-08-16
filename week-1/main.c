#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000
#define DEBUG 0

void merge(int *array, int size_left, int size_right, long long *inversions) {
  int temp_array[size_left + size_right];
  int ptr_left = 0, ptr_right = 0;

  while(ptr_left + ptr_right < size_left + size_right) {

    /* when integer on left size is smaller than integer on right size, choose left size integer */
    if ((ptr_left < size_left && array[ptr_left] < array[size_left + ptr_right]) || (ptr_right == size_right && ptr_left < size_left)) {
      temp_array[ptr_left + ptr_right] = array[ptr_left];
      ptr_left++;
    }

    /* when integer on right size is smaller than integer on left size, choose right size integer */
    /* also , inversion count equals to left size remaining integer size, cause when choose right size integer */
    if ((ptr_right < size_right && array[size_left + ptr_right] < array[ptr_left]) || (ptr_left == size_left && ptr_right < size_right)) {
      temp_array[ptr_left + ptr_right] = array[size_left + ptr_right];
      *inversions += size_left - ptr_left;
      ptr_right++;
    }
  }

  /* print new array content */
  if (DEBUG) {
    printf("print tem array content\n");
    for (int i = 0; i < size_left + size_right; ++i) {
      printf("%d ", temp_array[i]);
    }
    printf("\n");
  }

  /* assign sorted integers back to original array */
  for (int i = 0; i < size_left + size_right; ++i){
    *(array + i) = temp_array[i];
  }
}

void merge_sort(int *array, int size, long long *inversions) {
  int size_left = size / 2, size_right = size - size_left;

  if (size == 1) {
    return;
  }

  /* print array content */
  if (DEBUG) {
    printf("print left array content\n");
    for (int i = 0; i < size_left; ++i) {
      printf("%d ", array[i]);
    }
    printf("\nprint right array content\n");
    for (int i = 0; i < size_right; ++i) {
      printf("%d ", array[size_left + i]);
    }
    printf("\n");
  }

  merge_sort(array, size_left, inversions);
  merge_sort(array + size_left, size_right, inversions);
  merge(array, size_left, size_right, inversions);
}

void read_file(const char *file_name, int *array) {
  FILE *fp = fopen(file_name, "r");
  int integer = 0;
  if (!fp) {
    printf("%s does not exist, abort!", file_name);
    exit(0);
  }

  for (int i = 0; i < ARRAY_SIZE; ++i) {
    fscanf(fp, "%d", &integer);
    array[i] = integer;
  }
  fclose(fp);
}

int main(int argc, char **argv) {
  const char file_name[] = "IntegerArray.txt";
  int array[ARRAY_SIZE];
  /* int test_array[] = {5, 4, 3, 2, 1}; /\* ans: 10 *\/ */
  int test_array1[] = {9, 12, 3, 1, 6, 8, 2, 5, 14, 13, 11, 7, 10, 4, 0}; /* ans: 56 */
  long long inversions = 0;
  read_file(file_name, array);

  /* check array content */
  if (DEBUG) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
      printf("%d ", array[i]);
    }
  }

  if (DEBUG) {
    merge_sort(test_array1, sizeof(test_array1)/sizeof(test_array1[0]), &inversions);
  } else {
    merge_sort(array, ARRAY_SIZE, &inversions);
  }

  printf("sorting array has %lld inverisons", inversions);
}

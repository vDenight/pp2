//
// Created by mrybczynski on 5/7/2025.
//

#include "crosswords.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display(char** words) {
  while (*words != NULL) {
    printf("%s\n", *words);
    words++;
  }
}

void destroy(char** words) {
  while (*words != NULL) {
    free(*words);
    words++;
  }
  free(words);
}

int create_leading_word_cross(const char *first, const char *second, char ***result) {
  if (first == NULL || second == NULL || result == NULL)
    return CREATE_WRONG_INPUT;

  // second - horizontal
  // first - vertical

  const char* second_common_char = second;
  const char* first_common_char = NULL;

  while (*second_common_char != '\0') {
    for (int i = 0; i < strlen(first); i ++) {
      if (*second_common_char == *(first + i)) {
        first_common_char = first + i;
        break;
      }
    }
    if (first_common_char) break;
    second_common_char++;
  }

  if (!first_common_char) return CREATE_CANT_CROSS;

  // now some calculation
  int row_amount = (int) (strlen(first));
  int row_min_length = (int) (second_common_char - second) + 1;
  int row_max_length = (int) (strlen(second));
  int max_row_index = (int) (first_common_char - first) ;

  // now mem alloc

  *result = calloc(row_amount + 1, sizeof(char *));
  if (*result == NULL) return CREATE_ALLOC_FAIL;

  int alloc_amount = 0;
  for (int i = 0; i < row_amount; i ++) {

    if (i == max_row_index) {
      alloc_amount = row_max_length + 1;
    } else {
      alloc_amount = row_min_length + 1;
    }

    *((*result) + i) = calloc(alloc_amount, sizeof(char));
    if (*((*result) + i) == NULL) {
      for (int j = 0; j < i; j++) {
        free(*(*result) + j);
      }
      free(*result);
      return CREATE_ALLOC_FAIL;
    }
  }

  // mem alloc complete, now fill
  strcpy(*((*result) + max_row_index), second);
  int x = {0};
  for (int i = 0; i < row_amount; i ++) {
    if ( i == max_row_index) continue;
    x = row_min_length - 1;
    *(*(*result + i) + x) = *(first + i);
    x--;
    // fill with spaces
    while (x >= 0) {
      *(*(*result + i) + x) = ' ';
      x--;
    }
  }

  return max_row_index;
}

int get_cross_vert_len(char** cross) {
  int vert_len = 0;
  while (*cross != NULL) {
    vert_len++;
    cross++;
  }
  return vert_len;
}

int get_cross_horiz_len(char** cross) {
  int horiz_len = 0;
  while (*cross != NULL) {
    if (strlen(*cross) > horiz_len) {
      horiz_len = (int) strlen(*cross);
    }
    cross++;
  }
  return horiz_len;
}

int get_cross_vert_x(char** cross) {
  int min_len = 0;
  while (*cross != NULL) {
    // check if the line in the max_len
    if (*(*cross) == '\0') return 0; // 0 len

    if (*(*cross) == ' ') {
      // good
      while (*(*cross) == ' ') min_len ++;
      return min_len + 1;
    }

    if (*(*cross) != ' ') {
      // bad but maybe
      if (*(*cross + 1) == ' ') {
        // good
        while (*(*cross) == ' ') min_len ++;
        return min_len + 1;
      }
      // bad
      continue;
    }
    cross++;
  }
  return min_len;
}

int create_double_leading_word_cross(
    const char *first, const char *second, const char *third, const char *fourth,
    char ***result, char ***first_cross, char ***second_cross) {
  if (first == NULL || second == NULL || third == NULL || fourth == NULL || result == NULL)
    return DCREATE_WRONG_INPUT;

  int f_horiz_y = create_leading_word_cross(second, first, first_cross);
  if (f_horiz_y < 0) {
    if (f_horiz_y == CREATE_WRONG_INPUT) return DCREATE_WRONG_INPUT;
    if (f_horiz_y == CREATE_CANT_CROSS) return DCREATE_CANT_CROSS;
    if (f_horiz_y == CREATE_ALLOC_FAIL) return DCREATE_ALLOC_FAIL;
  }

  int s_horiz_y = create_leading_word_cross(fourth, third, second_cross);
  if (s_horiz_y < 0) {
    if (s_horiz_y == CREATE_WRONG_INPUT) { destroy(*first_cross); return DCREATE_WRONG_INPUT; }
    if (s_horiz_y == CREATE_CANT_CROSS) { destroy(*first_cross); return DCREATE_CANT_CROSS; }
    if (s_horiz_y == CREATE_ALLOC_FAIL) { destroy(*first_cross); return DCREATE_ALLOC_FAIL; }
  }

  // now lovely callculations again
  int f_vert_x = get_cross_vert_x(*first_cross);
  int s_vert_x = get_cross_vert_x(*second_cross);

  int f_vert_len = get_cross_vert_len(*first_cross);
  int s_vert_len = get_cross_vert_len(*second_cross);
  int f_horiz_len = get_cross_horiz_len(*first_cross);
  int s_horiz_len = get_cross_horiz_len(*second_cross);

  // let's move things down
  if (f_horiz_y > s_horiz_y) {
    s_horiz_y = f_horiz_y;

  } else if (f_horiz_y < s_horiz_y) {
    f_horiz_y = s_horiz_y;
  }

  // now let's move the second cross left

}

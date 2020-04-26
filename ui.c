#include <stdio.h>
#include "arrays.h"
#include "ui.h"

/* The variable "filename" is the default file name that save file will
   save to and load file will load from */
char filename[80] = "test";

/* 1d array for testing */
int array_1d_length = 3;
float array_1d[80] = {1, 2, 3};

/* 2d array for testing */
int array_2d_row = 3;
int array_2d_col = 3;
float array_2d[80][80] = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}};

/* 2d arrays for multiplication */
float Amatrix[80][80];
float Bmatrix[80][80];
float Cmatrix[80][80];

/* Values for multiplication. AcolBrow contains the number of rows in
   A and the number of columns in B of the two matrices A and B that
   are to be multiplied. Arow contains the number of rows in A' Bcol
   contains the number of columns in B. */
int AcolBrow;
int Arow;
int Bcol;

/*
 * Execute command
 * Return value: FALSE means that the user want to exit. The loop
 * calling the execute command should terminate
*/

int execute_command(char command)
{
  int search_target = 0;

  switch (command) {
  case 'x':
    return FALSE;
  case 'p':
    /* Story 1 */
    print_1d_array(array_1d, array_1d_length);
    return TRUE;
  case 'r':
    /* Story 2 */
    array_1d_length = get_int("Enter array length");
    read_1d_array(array_1d, array_1d_length);
    return TRUE;
  case 's':
    /* Story 3 */
    save_1d_array(filename, array_1d, array_1d_length);
    return TRUE;
  case 'l':
    /* Story 3 */
    load_1d_array(filename, array_1d, &array_1d_length);
    return TRUE;
  case 'i':
    /* Story 4 */
    insert_1d_array(get_float("Enter value to insert"),
                   get_int("Enter position for value"),
                   array_1d, &array_1d_length);
    return TRUE;
  case 'd':
    /* Story 5 */
    delete_1d_array(get_int("Enter position to delete"),
                   array_1d, &array_1d_length);
    return TRUE;
case 'P':
    /* Story 6 */
    print_2d_array(array_2d, array_2d_col, array_2d_row);
    return TRUE;
  case 'R':
    /* Story 7 */
    array_2d_col = get_int("Enter 2D array number of columns");
    array_2d_row = get_int("Enter 2D array number of rows");
    read_2d_array(array_2d, array_2d_col, array_2d_row);
    return TRUE;
  case '*':
    /* Story 8 */
    AcolBrow = get_int("Enter number of columns for matrix A");
    Arow = get_int("Enter number of rows for matrix A");
    Bcol = get_int("Enter number of columns for matrix B");
    read_2d_array(Amatrix, AcolBrow, Arow);
    read_2d_array(Bmatrix, Bcol, AcolBrow);
    multiply(Amatrix, Arow, Bmatrix, Bcol, Cmatrix, AcolBrow);
    print_2d_array(Cmatrix, Bcol, Arow);
    return TRUE;
  case 'S':
    switch(get_command("Enter sub-command (b, s, i, m, or q)")) {
    /* Story 9 */
    case 'b':
      bubble_sort(array_1d, array_1d_length);
      break;
    /* Story 10 */
    case 's':
      selection_sort(array_1d, array_1d_length);
      break;
    /* Story 11 */
    case 'i':
      insertion_sort(array_1d, array_1d_length);
      break;
    default:
      printf("Unknown sub-command %c\n", command);
    }
    return TRUE;
  case 'F':
    search_target = get_int("Search for");
    switch(get_command("Enter sub-command (l or b)")) {
    /* Story 12 */
    case 'l':
      linear_search(search_target, array_1d, array_1d_length);
      break;
    /* Story 13 */
    case 'b':
      binary_search(search_target, array_1d, array_1d_length);
      break;
    default:
      printf("Unknown sub-command %c\n", command);
    }
    return TRUE;
  case 't':
    load_1d_array(filename, array_1d, &array_1d_length);
    bubble_sort(array_1d, array_1d_length);
    for (int i = 0; i < array_1d_length; i++) {
      binary_search(i, array_1d, array_1d_length);
    }
    return TRUE;
  default:
    printf("Unknown command %c\n", command);
    return TRUE;
  }
  /* Should never reach here */
  printf("Error: execute command failed\n");
  return FALSE;
}

/*
 * Get command
 * Returns the first non-white character from the line the user
 * enters. By reading the entire line and returning only the first
 * character the function avoids processing the newline character at
 * the end of the line.
*/
int is_whitespace(char c) {
  return (' ' == c || '\t' == c || '\n' == c);
}

char get_first_non_white(char *s) {
  for (int i = 0; '\0' != s[i] && i < 80; i++) {
    if (!is_whitespace(s[i])) {
      return(s[i]);
    }
  }
  return('\0');
}

char get_command(char *msg) {
  char buffer[80];

  printf("%s> ", msg);
  scanf("%80s", buffer);
  return get_first_non_white(buffer);
}

/*
  read numbers: float and int
*/
int consume_digits(char *s)
{
  int i = 0;
  while (i < 80 && ('0' == s[i] ||
                    '1' == s[i] ||
                    '2' == s[i] ||
                    '3' == s[i] ||
                    '4' == s[i] ||
                    '5' == s[i] ||
                    '6' == s[i] ||
                    '7' == s[i] ||
                    '8' == s[i] ||
                    '9' == s[i] )
         ) {
    i++;
  }
  return i;
}

int can_be_float(char *s)
{
  int i = 0;
  i = consume_digits(s);
  if ('\0' == s[i]) {
    return TRUE;
  }
  if ('.' == s[i]) {
    i += consume_digits(&s[i+1]) + 1;
  }
  if ('\0' == s[i]) {
    return TRUE;
  }
  return FALSE;
}

float get_float(char *msg)
{
  char buf[80] = "x";
  float f = 0.0;

  printf("%s> ", msg);
  scanf("%80s", buf);
  while(!can_be_float(buf)) {
    printf("%s is not a number", buf);
    printf("Enter number (with optional decimal point)> ");
    scanf("%80s", buf);
  }
  sscanf(buf, "%f", &f);
  return f;
}

int can_be_int(char *s)
{
  int i = 0;
  i = consume_digits(s);
  if ('\0' == s[i]) {
    return TRUE;
  }
  return FALSE;
}

int get_int(char *msg)
{
  char buf[80] = "x";
  int i = 0;

  printf("%s> ", msg);
  scanf("%80s", buf);
  while(!can_be_int(buf)) {
    printf("%s is not an integer", buf);
    printf("Enter integer> ");
    scanf("%80s", buf);
  }
  sscanf(buf, "%d", &i);
  return i;
}

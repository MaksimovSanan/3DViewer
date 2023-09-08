#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct Matrix {
  double **matrix;
  unsigned int rows;
  unsigned int cols;
} matrix_t;

typedef struct {
  unsigned int count_of_vertexes;
  unsigned int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
} data;

typedef struct {
  double max_x;
  double max_y;
  double max_z;
  double max;
} maxima;

int parse(const char *filepath, data *data);
int pre_parse(data *data, char *str, FILE *file, maxima *max);
int parse_vertexes(data *data, char *str, int *i, maxima *max);
int parse_facets(data *data, char *str, int *j);
void destroy_data(data *data);

#endif
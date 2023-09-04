#include "parser.h"

int parse(const char *filepath, data *data) {
  data->count_of_facets = 0;
  data->count_of_vertexes = 0;
  data->matrix_3d.cols = 0;
  data->matrix_3d.rows = 0;
  int status = 0;
  maxima normalization = {0, 0, 0};
  FILE *file;
  file = fopen(filepath, "r");
  if (file != NULL) {
    char str[256];
    pre_parse(data, str, file, &normalization);
    normalization.max =
        (normalization.max_x > normalization.max_y)
            ? (normalization.max_x > normalization.max_z) ? normalization.max_x
                                                          : normalization.max_z
        : (normalization.max_y > normalization.max_z) ? normalization.max_y
                                                      : normalization.max_z;
    data->matrix_3d.cols = 3;
    data->matrix_3d.rows = (data->count_of_vertexes) + 1;
    data->matrix_3d.matrix = calloc(data->matrix_3d.rows, sizeof(double *));
    *(data->matrix_3d.matrix) =
        calloc((data->matrix_3d.rows) * (data->matrix_3d.cols), sizeof(double));
    for (int i = 1; i < data->matrix_3d.rows; i++) {
      data->matrix_3d.matrix[i] =
          *(data->matrix_3d.matrix) + ((i - 1) * data->matrix_3d.cols);
    }
    data->polygons = calloc(data->count_of_facets, sizeof(polygon_t));
    for (int i = 0; i < data->count_of_facets; i++) {
      data->polygons[i].numbers_of_vertexes_in_facets = 0;
      data->polygons[i].vertexes = NULL;
    }

    status = fseek(file, 0, SEEK_SET);
    int i = 1;
    int j = 0;
    while (fgets(str, 255, file) && !status) {
      if (str[0] == 'v' && str[1] == ' ') {
        status = parse_vertexes(data, str, &i, &normalization);
      } else if ((*str) == 'f' && *(str + 1) == ' ') {
        status = parse_facets(data, str, &j);
      }
    }
    fclose(file);
  } else
    status = 1;
  return status;
}

int pre_parse(data *data, char *str, FILE *file, maxima *max) {
  int status = 0;
  while (fgets(str, 255, file) && !status) {
    if (*str == 'v' && *(str + 1) == ' ') {
      data->count_of_vertexes = data->count_of_vertexes + 1;
      double tmp_x = 0;
      double tmp_y = 0;
      double tmp_z = 0;
      sscanf(str, "v %lf %lf %lf", &tmp_x, &tmp_y, &tmp_z);
      if (fabs(tmp_x) > max->max_x) max->max_x = fabs(tmp_x);
      if (fabs(tmp_y) > max->max_y) max->max_y = fabs(tmp_y);
      if (fabs(tmp_z) > max->max_z) max->max_z = fabs(tmp_z);
    } else if (*str == 'f' && *(str + 1) == ' ') {
      data->count_of_facets = data->count_of_facets + 1;
    }
  }
  return status;
}

int parse_vertexes(data *data, char *str, int *i, maxima *max) {
  double tmp_x = 0;
  double tmp_y = 0;
  double tmp_z = 0;
  sscanf(str, "v %lf %lf %lf", &tmp_x, &tmp_y, &tmp_z);
  double tmp1 = tmp_x / max->max_x;
  data->matrix_3d.matrix[*i][0] = (tmp_x / max->max);
  double tmp2 = tmp_y / max->max_y;
  data->matrix_3d.matrix[*i][1] = (tmp_y / max->max);
  double tmp3 = tmp_z / max->max_z;
  data->matrix_3d.matrix[*i][2] = (tmp_z / max->max);
  (*i)++;
  return 0;
}

int parse_facets(data *data, char *str, int *j) {
  int k = 0;
  int flag = 0;
  int counter = 0;
  str++;
  char *str_cpy = str;
  while (*str != '\n' && *str != '\0') {
    if (*str == ' ') flag = 1;
    if ((*str >= '0' && *str <= '9') && flag) {
      counter++;
      flag = 0;
    }
    str++;
  }
  flag = 0;
  data->polygons[*j].numbers_of_vertexes_in_facets = counter;
  data->polygons[*j].vertexes =
      calloc(data->polygons[*j].numbers_of_vertexes_in_facets, sizeof(int));

  while (*str_cpy != '\n' && *str_cpy != '\0') {
    if (*str_cpy == ' ') flag = 1;
    if ((*str_cpy >= '0' && *str_cpy <= '9') && flag) {
      data->polygons[*j].vertexes[k] = atoi(str_cpy);
      k++;
      flag = 0;
    }
    str_cpy++;
  }

  (*j)++;
  return 0;
}

void destroy_data(data *data) {
  for (int i = 0; i < data->count_of_facets; i++) {
    data->polygons[i].numbers_of_vertexes_in_facets = 0;
    free(data->polygons[i].vertexes);
  }
  free(data->polygons);

  free(*(data->matrix_3d.matrix));
  free(data->matrix_3d.matrix);
  data->matrix_3d.cols = 0;
  data->matrix_3d.rows = 0;
  data->count_of_facets = 0;
  data->count_of_vertexes = 0;
}

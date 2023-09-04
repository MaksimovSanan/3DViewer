#include "glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget *parent)
#if QT_VERSION > 0x060000
    : QOpenGLWidget(parent)
#else
    : QGLWidget(parent)
#endif
{
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);
  //  Line_r = 0.0;
  //    Line_g = 0.0;
  //    Line_b = 1.0;
  //    Dot_r = 1.0;
  //    Dot_g = 0;
  //    Dot_b = 0;
  //    Bg_r = 0.0;
  //    Bg_g = 1.0;
  //    Bg_b = 0.0;
  //    Line_type = 0;
  //    Dot_size = 10;
  //    Line_thickness = 2;
  //    Dot_type = 2;
status = 1;
}

void GLWidget::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f,
               1.0f);  // Set background color to black and opaque
  glClearDepth(1.0f);  // Set background depth to farthest
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glDepthFunc(GL_LEQUAL);   // Set the type of depth-test
  glShadeModel(GL_SMOOTH);  // Enable smooth shading
  glHint(GL_PERSPECTIVE_CORRECTION_HINT,
         GL_NICEST);  // Nice perspective corrections
  const char *path = "test.obj";
  parse(path, &my_data);
  //    std::cout << "im here";
  //    std::cout << "COF" <<my_data.count_of_facets << std::endl;
  //    std::cout << "COV" <<my_data.count_of_facets << std::endl;
}
void GLWidget::resizeGL(int nWidth, int nHeight) {
  glViewport(0, 0, (GLsizei)nWidth, (GLsizei)nHeight);

  // glPerspective(120,1,2,50.0);
  // glMatrixMode(GL_MODELVIEW);
}

void GLWidget::slot(int line_r, int line_g, int line_b, int dot_r, int dot_g,
                    int dot_b, int bg_r, int bg_g, int bg_b, int line_type,
                    int dot_size, int line_thickness, int dot_type,
                    int projection_type) {
  Line_r = (float)line_r / 255;
  Line_g = (float)line_g / 255;
  Line_b = (float)line_b / 255;
  Dot_r = (float)dot_r / 255;
  Dot_g = (float)dot_g / 255;
  Dot_b = (float)dot_b / 255;
  Bg_r = (float)bg_r / 255;
  Bg_g = (float)bg_g / 255;
  Bg_b = (float)bg_b / 255;
  Line_type = line_type;
  Dot_size = dot_size;
  Line_thickness = line_thickness;
  Dot_type = dot_type;
  Projection_type = projection_type;
  update();
}

void GLWidget::get_file_name(char *file_name) {
  status = parse(file_name, &my_data);
  update();
}

void GLWidget::flip_x(double flip_angle) {
  if(!status) flip_rel_x(*(my_data.matrix_3d.matrix + 1), my_data.count_of_vertexes * 3,
             flip_angle);
  if(!status)update();
}

void GLWidget::flip_y(double flip_angle) {
  if(!status)flip_rel_y(*(my_data.matrix_3d.matrix + 1), my_data.count_of_vertexes * 3,
             flip_angle);
  if(!status)update();
}

void GLWidget::flip_z(double flip_angle) {
  if(!status)flip_rel_z(*(my_data.matrix_3d.matrix + 1), my_data.count_of_vertexes * 3,
             flip_angle);
  if(!status)update();
}

void GLWidget::move_X(double movement) {
  if(!status)move_x(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, movement);
  if(!status)update();
}

void GLWidget::move_Y(double movement) {
  if(!status)move_y(my_data.matrix_3d.matrix[0], my_data.count_of_vertexes * 3, movement);
  if(!status)update();
}

void GLWidget::move_Z(double movement) {
  if(!status)move_z(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, movement);
  if(!status)update();
}

void GLWidget::size_increase() {
  if(!status)increase_size(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3);
  if(!status)update();
}

void GLWidget::size_decrease() {
  if(!status)deacrease_size(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3);
  if(!status)update();
}

void GLWidget::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (Projection_type == 0) {
    glOrtho(-1, 1, -1, 1, -10, 10);
  } else if (Projection_type == 1) {
    glFrustum(-1, 1, -1, 1, 0.5, 40);
  }
  glMatrixMode(GL_MODELVIEW);
  glClearColor(Bg_r, Bg_g, Bg_b, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (Dot_type) {
    if (Dot_type == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(Dot_size);
    glColor3f(Dot_r, Dot_g, Dot_b);
    glBegin(GL_POINTS);
    for (uint i = 0; i < my_data.count_of_vertexes; i++) {
      if (Projection_type) {
          glVertex3f((*(my_data.matrix_3d.matrix + 1))[3 * i],
                     (*(my_data.matrix_3d.matrix + 1))[3 * i + 1],
                     (*(my_data.matrix_3d.matrix + 1))[3 * i + 2] - 1);
      }
      else {
          glVertex3f((*(my_data.matrix_3d.matrix + 1))[3 * i],
                     (*(my_data.matrix_3d.matrix + 1))[3 * i + 1],
                     (*(my_data.matrix_3d.matrix + 1))[3 * i + 2]);
      }
    }
    glEnd();
  }
  glEnable(GL_LINE);
  if (Line_type) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0FF0);
  } else
    glDisable(GL_LINE_STIPPLE);
  glLineWidth(Line_thickness);
  glColor3f(Line_r, Line_g, Line_b);
  for (uint i = 0; i < my_data.count_of_facets; i++) {
    glBegin(GL_LINE_LOOP);
    for (int j = 0; j < my_data.polygons[i].numbers_of_vertexes_in_facets;
         j++) {
        if (Projection_type) {
            glVertex3f(*((*my_data.matrix_3d.matrix) - 3 +
                         my_data.polygons[i].vertexes[j] * 3 + 0),
                       *((*my_data.matrix_3d.matrix) - 3 +
                         my_data.polygons[i].vertexes[j] * 3 + 1),
                       *((*my_data.matrix_3d.matrix) - 3 +
                         my_data.polygons[i].vertexes[j] * 3 + 2) - 1);
        }
        else {
            glVertex3f(*((*my_data.matrix_3d.matrix) - 3 +
                         my_data.polygons[i].vertexes[j] * 3 + 0),
                       *((*my_data.matrix_3d.matrix) - 3 +
                         my_data.polygons[i].vertexes[j] * 3 + 1),
                       *((*my_data.matrix_3d.matrix) - 3 +
                         my_data.polygons[i].vertexes[j] * 3 + 2));
        }
    }
    glEnd();
  }
}

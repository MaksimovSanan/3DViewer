#ifndef GLWIDGET_H
#define GLWIDGET_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../parser.h"
#include "../afine.h"
#ifdef __cplusplus
}
#endif

#include <QtGlobal>
#if QT_VERSION >= 0x060000
#include <GLUT/glut.h>
#include <QOpenGLWidget>
#else
#include <GL/glut.h>
#include <QGLWidget>
#endif

#include <QSurfaceFormat>
#include <QWidget>

#define GL_SILENCE_DEPRECATION

#if QT_VERSION > 0x060000
class GLWidget : public QOpenGLWidget
#else
class GLWidget : public QGLWidget
#endif
{
  Q_OBJECT
public:
  GLWidget(QWidget *parent = nullptr);
  int status;
  ::data my_data;

protected:
  void initializeGL() override;
  void paintGL() override;
  // void resizeGL(int nWidth, int nHeight);
  void resizeGL(int nWidth, int nHeight) override;

public slots:
  void slot(int line_r, int line_g, int line_b, int dot_r, int dot_g, int dot_b,
            int bg_r, int bg_g, int bg_b, int line_type, int dot_size,
            int dine_thickness, int dot_type, int projection_type);
  void get_file_name(char *);
  void flip_x(double flip_angle);
  void flip_y(double flip_angle);
  void flip_z(double flip_angle);
  void move_Z(double movement);
  void move_Y(double movement);
  void move_X(double movement);
  void size_increase();
  void size_decrease();

private:
  float Line_r, Line_g, Line_b, Dot_r, Dot_g, Dot_b, Bg_r, Bg_g, Bg_b;
  int Line_type, Dot_size, Line_thickness, Dot_type, Projection_type;
};

#endif // GLWIDGET_H

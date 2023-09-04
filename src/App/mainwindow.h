#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QThread>
#include <QTimer>
#define pressed_loop(mov) any_button_pressed = 1; \
while(any_button_pressed == 1) { \
  QEventLoop loop;  \
  QTimer::singleShot(1, &loop, &QEventLoop::quit); \
  emit mov; \
  loop.exec(); \
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  int line_r, line_g, line_b, dot_r, dot_g, dot_b, bg_r, bg_g, bg_b, line_type,
      dot_size, line_thickness, dot_type, projection_type;
  void save_settings();
  void load_settings();

signals:
  void change_GL(int line_r, int line_g, int line_b, int dot_r, int dot_g,
                 int dot_b, int bg_r, int bg_g, int bg_b, int line_type,
                 int dot_size, int line_thickness, int dot_type,
                 int projection_type);
  void change_model(char *);

  void flip_x(double flip_angle);

  void flip_y(double flip_angle);

  void flip_z(double flip_angle);

  void move_x(double movement);

  void move_y(double movement);

  void move_z(double movement);

  void increase_size();

  void decrease_size();

  void stop_move_x();

private slots:
  void changeGL();

  void on_screenshot_clicked();

  void on_GIF_clicked();

  void on_openFile_clicked();

  void on_flip_x_l_pressed();

  void on_flip_x_l_released();

  void on_flip_x_r_pressed();

  void on_flip_x_r_released();

  void on_flip_y_l_pressed();

  void on_flip_y_r_pressed();

  void on_flip_z_l_pressed();

  void on_flip_z_r_pressed();

  void on_move_x_l_pressed();

  void on_move_x_r_pressed();

  void on_move_y_l_pressed();

  void on_move_y_r_pressed();

  void on_move_z_l_pressed();

  void on_move_z_r_pressed();

  void on_increase_pressed();

  void on_decrease_released();

  void on_move_x_l_released();

  void on_move_x_r_released();

  void on_flip_y_l_released();

  void on_flip_y_r_released();

  void on_move_y_l_released();

  void on_move_y_r_released();

  void on_flip_z_l_released();

  void on_flip_z_r_released();

  void on_move_z_l_released();

  void on_move_z_r_released();

  void on_increase_released();

  void on_decrease_pressed();

private:
  Ui::MainWindow *ui;
  QGifImage *gifim;
  QSettings *settings;
  int any_button_pressed;
};
#endif // MAINWINDOW_H

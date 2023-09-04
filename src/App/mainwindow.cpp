#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(this, &MainWindow::change_GL, ui->openGLWidget, &GLWidget::slot);
  settings = new QSettings("hesiso", "viewer", this);
  load_settings();
  connect(ui->Line_r, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->Line_g, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->Line_b, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->Dot_r, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->Dot_g, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->Dot_b, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->BG_r, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->BG_g, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->BG_b, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->Line_type, SIGNAL(currentTextChanged(QString)), this,
          SLOT(changeGL()));
  connect(ui->Dot_type, SIGNAL(currentTextChanged(QString)), this,
          SLOT(changeGL()));
  connect(ui->Projection_type, SIGNAL(currentTextChanged(QString)), this,
          SLOT(changeGL()));
  connect(ui->Dot_size, SIGNAL(valueChanged(int)), this, SLOT(changeGL()));
  connect(ui->Line_thickness, SIGNAL(valueChanged(int)), this,
          SLOT(changeGL()));
  connect(this, &MainWindow::change_model, ui->openGLWidget,
          &GLWidget::get_file_name);
  connect(this, &MainWindow::flip_x, ui->openGLWidget, &GLWidget::flip_x);
  connect(this, &MainWindow::flip_y, ui->openGLWidget, &GLWidget::flip_y);
  connect(this, &MainWindow::flip_z, ui->openGLWidget, &GLWidget::flip_z);
  connect(this, &MainWindow::move_z, ui->openGLWidget, &GLWidget::move_Z);
  connect(this, &MainWindow::move_x, ui->openGLWidget, &GLWidget::move_X);
  connect(this, &MainWindow::move_y, ui->openGLWidget, &GLWidget::move_Y);
  connect(this, &MainWindow::increase_size, ui->openGLWidget,
          &GLWidget::size_increase);
  connect(this, &MainWindow::decrease_size, ui->openGLWidget,
          &GLWidget::size_decrease);
}

MainWindow::~MainWindow() {
  save_settings();
  delete ui;
}

void MainWindow::save_settings() {
  settings->setValue("line_r", ui->Line_r->value());
  settings->setValue("line_g", ui->Line_g->value());
  settings->setValue("line_b", ui->Line_b->value());
  settings->setValue("dot_r", ui->Dot_r->value());
  settings->setValue("dot_g", ui->Dot_g->value());
  settings->setValue("dot_b", ui->Dot_b->value());
  settings->setValue("bg_r", ui->BG_r->value());
  settings->setValue("bg_g", ui->BG_g->value());
  settings->setValue("bg_b", ui->BG_b->value());
  settings->setValue("line_type", ui->Line_type->currentIndex());
  settings->setValue("dot_size", ui->Dot_size->value());
  settings->setValue("line_thickness", ui->Line_thickness->value());
  settings->setValue("dot_type", ui->Dot_type->currentIndex());
  settings->setValue("projection_type", ui->Projection_type->currentIndex());
}

void MainWindow::load_settings() {
  line_r = settings->value("line_r", 0).toInt();
  line_g = settings->value("line_g", 0).toInt();
  line_b = settings->value("line_b", 255).toInt();
  dot_r = settings->value("dot_r", 255).toInt();
  dot_g = settings->value("dot_g", 0).toInt();
  dot_b = settings->value("dot_b", 0).toInt();
  bg_r = settings->value("bg_r", 0).toInt();
  bg_g = settings->value("bg_g", 255).toInt();
  bg_b = settings->value("bg_b", 0).toInt();
  line_type = settings->value("line_type", 0).toInt();
  dot_size = settings->value("dot_size", 10).toInt();
  line_thickness = settings->value("line_thickness", 2).toInt();
  dot_type = settings->value("dot_type", 2).toInt();
  projection_type = settings->value("projection_type", 0).toInt();
  ui->Line_r->setValue(line_r);
  ui->Line_g->setValue(line_g);
  ui->Line_b->setValue(line_b);
  ui->Dot_r->setValue(dot_r);
  ui->Dot_g->setValue(dot_g);
  ui->Dot_b->setValue(dot_b);
  ui->BG_r->setValue(bg_r);
  ui->BG_g->setValue(bg_g);
  ui->BG_b->setValue(bg_b);
  ui->Line_type->setCurrentIndex(line_type);
  ui->Dot_size->setValue(dot_size);
  ui->Line_thickness->setValue(line_thickness);
  ui->Dot_type->setCurrentIndex(dot_type);
  ui->Projection_type->setCurrentIndex(projection_type);
  emit change_GL(line_r, line_g, line_b, dot_r, dot_g, dot_b, bg_r, bg_g, bg_b,
                 line_type, dot_size, line_thickness, dot_type,
                 projection_type);
}

void MainWindow::changeGL() {
  line_r = ui->Line_r->value();
  line_g = ui->Line_g->value();
  line_b = ui->Line_b->value();
  dot_r = ui->Dot_r->value();
  dot_g = ui->Dot_g->value();
  dot_b = ui->Dot_b->value();
  bg_r = ui->BG_r->value();
  bg_g = ui->BG_g->value();
  bg_b = ui->BG_b->value();
  dot_size = ui->Dot_size->value();
  line_type = ui->Line_type->currentIndex();
  line_thickness = ui->Line_thickness->value();
  dot_type = ui->Dot_type->currentIndex();
  projection_type = ui->Projection_type->currentIndex();
  emit change_GL(line_r, line_g, line_b, dot_r, dot_g, dot_b, bg_r, bg_g, bg_b,
                 line_type, dot_size, line_thickness, dot_type,
                 projection_type);
}

void MainWindow::on_screenshot_clicked() {
#if QT_VERSION > 0x060000
  uint date = QDateTime::currentDateTime().toSecsSinceEpoch();
#else
  uint date = QDateTime::currentDateTime().toTime_t();
#endif
  if (ui->img_format->currentIndex()) {
#if QT_VERSION > 0x060000
    ui->openGLWidget->grabFramebuffer().save("./screenshots/" +
                                             QString::number(date) + ".bmp");
#else
    ui->openGLWidget->grabFrameBuffer().save("./screenshots/" +
                                             QString::number(date) + ".bmp");
#endif
  } else {
#if QT_VERSION > 0x060000
    ui->openGLWidget->grabFramebuffer().save("./screenshots/" +
                                             QString::number(date) + ".jpeg");
#else
    ui->openGLWidget->grabFrameBuffer().save("./screenshots/" +
                                             QString::number(date) + ".jpeg");
#endif
  }
}

void MainWindow::on_GIF_clicked() {
  gifim = new QGifImage();
  int delay = 100;
#if QT_VERSION > 0x060000
  uint date = QDateTime::currentDateTime().toSecsSinceEpoch();
#else
  uint date = QDateTime::currentDateTime().toTime_t();
#endif
  gifim->setDefaultDelay(delay);
  int frames = 50;
  for (int i = 0; i < frames; i++) {
#if QT_VERSION > 0x060000
    QImage img = ui->openGLWidget->grabFramebuffer();
#else
    QImage img = ui->openGLWidget->grabFrameBuffer();
#endif
    QEventLoop loop;
    QTimer::singleShot(100, &loop, &QEventLoop::quit);
    loop.exec();
    gifim->addFrame(img, -1);
  }
#if QT_VERSION > 0x060000
  gifim->save("./screenshots/" + QString::number(date) + ".gif");
#else
  gifim->save("./screenshots/" + QString::number(date) + ".gif");
#endif
}

void MainWindow::on_openFile_clicked() {
  QString temp =
      QFileDialog::getOpenFileName(this, "OBJ model selector", "./../");
  QByteArray data = (temp + "\0").toUtf8();
  char* file_name = data.data();
  const QFileInfo info(file_name);
  ui->FILENAME->setText(info.fileName());
  emit change_model(file_name);
  std::cout << ui->openGLWidget->my_data.count_of_vertexes;
  ui->vertex_count->setText(
      QString::number(ui->openGLWidget->my_data.count_of_vertexes));
  uint edges_count = 0;
  for (uint i = 0; i < ui->openGLWidget->my_data.count_of_facets; i++) {
    edges_count +=
        ui->openGLWidget->my_data.polygons->numbers_of_vertexes_in_facets;
  }
  ui->edges_count->setText(QString::number(edges_count));
}

void MainWindow::on_flip_x_l_pressed() {
  pressed_loop(emit flip_x(FLIP_ANGLE_L));
}

void MainWindow::on_flip_x_l_released() { any_button_pressed = 0; }

void MainWindow::on_flip_x_r_pressed() {
  pressed_loop(emit flip_x(FLIP_ANGLE_R));
}

void MainWindow::on_flip_x_r_released() { any_button_pressed = 0; }

void MainWindow::on_flip_y_l_pressed() {
  pressed_loop(emit flip_y(FLIP_ANGLE_L));
}

void MainWindow::on_flip_y_r_pressed() {
  pressed_loop(emit flip_y(FLIP_ANGLE_R));
}

void MainWindow::on_flip_z_l_pressed() {
  pressed_loop(emit flip_z(FLIP_ANGLE_L));
}

void MainWindow::on_flip_z_r_pressed() {
  pressed_loop(emit flip_z(FLIP_ANGLE_R));
}

void MainWindow::on_move_x_l_pressed() { pressed_loop(emit move_x(MOVEMENT)); }

void MainWindow::on_move_x_r_pressed() { pressed_loop(emit move_x(-MOVEMENT)); }

void MainWindow::on_move_y_l_pressed() { pressed_loop(emit move_y(MOVEMENT)); }

void MainWindow::on_move_y_r_pressed() { pressed_loop(emit move_y(-MOVEMENT)); }

void MainWindow::on_move_z_l_pressed() { pressed_loop(emit move_z(MOVEMENT)); }

void MainWindow::on_move_z_r_pressed() { pressed_loop(emit move_z(-MOVEMENT)); }

void MainWindow::on_increase_pressed() { pressed_loop(emit increase_size()); }

void MainWindow::on_decrease_released() { any_button_pressed = 0; }

void MainWindow::on_move_x_l_released() { any_button_pressed = 0; }

void MainWindow::on_move_x_r_released() { any_button_pressed = 0; }

void MainWindow::on_flip_y_l_released() { any_button_pressed = 0; }

void MainWindow::on_flip_y_r_released() { any_button_pressed = 0; }

void MainWindow::on_move_y_l_released() { any_button_pressed = 0; }

void MainWindow::on_move_y_r_released() { any_button_pressed = 0; }

void MainWindow::on_flip_z_l_released() { any_button_pressed = 0; }

void MainWindow::on_flip_z_r_released() { any_button_pressed = 0; }

void MainWindow::on_move_z_l_released() { any_button_pressed = 0; }

void MainWindow::on_move_z_r_released() { any_button_pressed = 0; }

void MainWindow::on_increase_released() { any_button_pressed = 0; }

void MainWindow::on_decrease_pressed() { pressed_loop(emit decrease_size()); }

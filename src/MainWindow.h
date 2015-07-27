#pragma once

#include <QMainWindow>

#include "ui_LevelEditor.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);

private slots:
  void on_actionEnableGrid_toggled(bool checked);
  void on_actionDrawPath_triggered();

private:  
  Ui::LevelEditor mUi;
};

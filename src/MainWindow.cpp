#include "MainWindow.h"

#include "EditAction.h"
#include "PathEditAction.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  mUi.setupUi(this);
}

void MainWindow::on_actionEnableGrid_toggled(bool checked)
{
  mUi.mazeEdit->setEnableGrid(checked);
}

void MainWindow::on_actionDrawPath_triggered()
{
  int width = mUi.mazeEdit->tileWidth();
  int height = mUi.mazeEdit->tileHeight();

  EditAction* action = new PathEditAction(width, height);
  mUi.mazeEdit->setEditAction(action);
}

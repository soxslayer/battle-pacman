#include "MainWindow.h"

#include "LineSelection.h"
#include "QuantizedSelection.h"

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

  LineSelection* lSel = new LineSelection(true);
  QuantizedSelection* qSel = new QuantizedSelection(*lSel, QRectF(width / 2,
                                                                  height / 2,
                                                                  width,
                                                                  height));

  mUi.mazeEdit->setSelection(qSel);
}

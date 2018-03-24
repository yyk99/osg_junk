//
//
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow() : m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::addViewer(QWidget *viewer)
{
    m_ui->horizontalLayout->addWidget(viewer);
}


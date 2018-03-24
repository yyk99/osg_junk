//
//
//


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();

public slots:
    void on_actionExit_triggered();

public:
    void addViewer(QWidget *viewer);


private:
    std::unique_ptr<Ui::MainWindow> m_ui;
};


#endif

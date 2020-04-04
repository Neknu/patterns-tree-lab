#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../Src/Tree.h"

#include <QMainWindow>

#include <variant>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionreset_window_triggered();

    void on_action_to_start_page_triggered();

private:
    Ui::MainWindow *ui;


//    std::variant<int, string context;

};
#endif // MAINWINDOW_H

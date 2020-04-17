#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <variant>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class DataType {Int, String, Double, Char};

enum class TreeType {Splay, B, Bplus};

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

    DataType data_type;
    TreeType tree_type;
    int min_degree = 3; // for BTree and BplusTree
    void* context;

};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../Src/BTree.h"
#include "../../Src/SplayTree.h"

#include <QButtonGroup>
#include <QDebug>

#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    BalancedTreeContext<BTree, int> context(std::make_shared<BTree<int>>(3));

    QButtonGroup group;
    QList<QRadioButton *> allButtons = ui->groupBox->findChildren<QRadioButton *>();
    for(int i = 0; i < allButtons.size(); ++i)
    {
        group.addButton(allButtons[i],i);
    }

    int id_data_type = ui->combo_box_data_type->currentIndex();
    int id_tree_type = group.checkedId();

    qDebug() << "id of data type: " << id_data_type;
    qDebug() << "id of tree type: " << id_tree_type;
//    qDebug() << group.checkedButton();

    if(id_tree_type >= 0) {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_actionreset_window_triggered()
{

}


void MainWindow::on_action_to_start_page_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/*
    id_data_type:
    0 - int
    1 - string
    2 - double
    3 - char

    id_tree_type:
    0 - SplayTree
    1 - BTree
    2 - BplusTree
*/
//template<template <typename T> typename TreeType, typename DataType>
//BalancedTreeContext<TreeType, DataType> create_tree(int id_data_type, int id_tree_type) {
//    switch (id_data_type) {
//    case 0:
//        switch (id_tree_type) {
//        case 0:
//            SplayTree<int> tree_int;
//            BalancedTreeContext<SplayTree, int> context_int(std::make_shared<SplayTree<int>>(tree));
//            return context_int;

//        case 1:
//            SplayTree<std::string> tree_string;
//            BalancedTreeContext<SplayTree, std::string> context_string(std::make_shared<SplayTree<std::string>>(tree_string));
//            return context_string;

//        case 2:
//            SplayTree<double> tree_double;
//            BalancedTreeContext<SplayTree, std::string> context_double(std::make_shared<SplayTree<std::string>>(tree_double));
//            return context_double;


//        case 3:
//            SplayTree<char> tree_char;
//            BalancedTreeContext<SplayTree, std::string> context_char(std::make_shared<SplayTree<std::string>>(tree_char));
//            return context_char;

//    }
//}

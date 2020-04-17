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
    data_type = DataType(id_data_type);
    tree_type = TreeType(id_tree_type);

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
    data_type:
    0 - int
    1 - string
    2 - double
    3 - char

    tree_type:
    0 - SplayTree
    1 - BTree
    2 - BplusTree
*/

//template<template <typename T> typename Type, typename Data>
void* create_tree(DataType data_type, TreeType tree_type, int min_degree) {
    if(tree_type == TreeType::Splay) {

        if(data_type == DataType::Int) {
            SplayTree<int> tree;
            BalancedTreeContext<SplayTree, int> context(std::make_shared<SplayTree<int>>(tree));
            return context;
        } else
        if(data_type == DataType::String) {
            SplayTree<std::string> tree;
            BalancedTreeContext<SplayTree, std::string> context(std::make_shared<SplayTree<std::string>>(tree));
            return context;
        } else
        if(data_type == DataType::Double) {
            SplayTree<double> tree;
            BalancedTreeContext<SplayTree, double> context(std::make_shared<SplayTree<double>>(tree));
            return context;
        }
        if(data_type == DataType::Char) {
            SplayTree<char> tree;
            BalancedTreeContext<SplayTree, char> context(std::make_shared<SplayTree<char>>(tree));
            return context;
        }

    } else

    if(tree_type == TreeType::B) {
        if(data_type == DataType::Int) {
            BalancedTreeContext<BTree, int> context(std::make_shared<BTree<int>>(min_degree));
            return context;
        } else
        if(data_type == DataType::String) {
            BalancedTreeContext<BTree, std::string> context(std::make_shared<BTree<std::string>>(min_degree));
            return context;
        } else
        if(data_type == DataType::Double) {
            BalancedTreeContext<BTree, double> context(std::make_shared<BTree<double>>(min_degree));
            return context;
        }
        if(data_type == DataType::Char) {
            BTree<char> tree(min_degree);
            BalancedTreeContext<BTree, char> context(std::make_shared<BTree<char>>(min_degree));
            return context;
        }
    }
//    else
//
//    if(tree_type == TreeType::Bplus) {
//        if(data_type == DataType::Int) {
//            BalancedTreeContext<BplusTree, int> context(std::make_shared<BplusTree<int>>(min_degree));
//            return context;
//        } else
//        if(data_type == DataType::String) {
//            BalancedTreeContext<BplusTree, std::string> context(std::make_shared<BplusTree<std::string>>(min_degree));
//            return context;
//        } else
//        if(data_type == DataType::Double) {
//            BalancedTreeContext<BplusTree, double> context(std::make_shared<BplusTree<double>>(min_degree));
//            return context;
//        }
//        if(data_type == DataType::Char) {
//            BTree<char> tree(min_degree);
//            BalancedTreeContext<BplusTree, char> context(std::make_shared<BplusTree<char>>(min_degree));
//            return context;
//        }
//    }
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include "DocFile.h"

MainWindow::MainWindow(DocFile* document, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , a_document(document)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDocFile(DocFile* document){
    a_document = document;
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "hello" << std::endl;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Microsoft Word Documents (*.docx)");
    dialog.setViewMode(QFileDialog::List);
    if(dialog.exec()){
        a_document->setFilePath(dialog.selectedFiles().at(0));
    }

    a_document->openFile();
    a_document->findReplace("hello");
    a_document->saveFile();
}


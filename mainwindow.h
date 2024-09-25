#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DocFile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DocFile* document = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

    void setDocFile(DocFile* document);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DocFile* a_document;
};
#endif // MAINWINDOW_H

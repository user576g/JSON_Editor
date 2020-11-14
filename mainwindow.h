#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include "file_operations.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
             }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    static MainWindow* get_instance(QWidget *parent = nullptr);

private:
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    CodeEditor *code_editor = nullptr;

    friend void file_op::open(),
        file_op::new_file(),
        file_op::save() ;
};
#endif // MAINWINDOW_H

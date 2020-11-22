#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "codeeditor.h"
#include "file_operations.h"
#include "stbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
             }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ~MainWindow();
    CodeEditor *code_editor = nullptr;
    static MainWindow* get_instance(QWidget *parent = nullptr);
    static void set_stbar_text(QString text);


private:
    QLineEdit *line_edit = nullptr;
    bool isFirstTime = true;

    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    void verify_msg();
    void on_find_clicked();
};
#endif // MAINWINDOW_H

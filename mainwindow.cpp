#include <QToolBar>
#include <QTextEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codeeditor.h"
#include <QFileDialog>
using namespace std::placeholders;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap newpix(":images/filenew.png");
    QPixmap openpix(":images/fileopen.png");
    QPixmap savepix(":images/filesave.png");

    QAction *new_ac = new QAction(newpix, "&New", this);
    QAction *open_ac = new QAction(openpix, "&Open", this);
    QAction *save_ac = new QAction(savepix, "&Save", this);
    QAction *close_ac = new QAction("&Close", this);

    QAction *quit = new QAction("&Quit", this);

    QMenu *file = menuBar()->addMenu("&File");

    file->addAction(new_ac);
    file->addAction(open_ac);
    file->addAction(save_ac);
    file->addAction(close_ac);
    file->addSeparator();
    file->addAction(quit);

    QToolBar *toolbar = addToolBar("main toolbar");

    QPixmap undopix(":images/undo.png");
    QPixmap redopix(":images/redo.png");
    QPixmap valpix(":images/validate.png");
    QPixmap findpix(":images/find.svg");

    toolbar->addAction(QIcon(undopix), "Undo");
    toolbar->addAction(QIcon(redopix), "Redo");
    toolbar->addAction(QIcon(savepix), "Save");
    toolbar->addAction(QIcon(valpix), "Validate JSON file");
    toolbar->addAction(QIcon(findpix), "Find");

    code_editor= new CodeEditor(this);
    setCentralWidget(code_editor);

    // long notation
    connect(new_ac, &QAction::triggered, qApp, file_op::new_file);
    connect(save_ac, &QAction::triggered, qApp, file_op::save);
    connect(save_ac, &QAction::triggered, qApp, file_op::save);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);

    statusBar()->showMessage("Words: 34, Characters: 161");
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow* MainWindow::get_instance(QWidget *parent) {
    static MainWindow *main_window = nullptr;
    if (nullptr == main_window) {
        main_window = new MainWindow(parent);
    }
    return main_window;
}

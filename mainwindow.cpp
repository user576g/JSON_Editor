#include <QToolBar>
#include <QTextEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codeeditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap newpix(":images/filenew.png");
    QPixmap openpix(":images/fileopen.png");
    QPixmap savepix(":images/filesave.png");

    QAction *newa = new QAction(newpix, "&New", this);
    QAction *open = new QAction(openpix, "&Open", this);
    QAction *save_ac = new QAction(savepix, "&Save", this);
    QAction *close_ac = new QAction("&Close", this);

    QAction *quit = new QAction("&Quit", this);

    QMenu *file = menuBar()->addMenu("&File");

    file->addAction(newa);
    file->addAction(open);
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

    CodeEditor *code_editor= new CodeEditor(this);
    setCentralWidget(code_editor);

    connect(quit, &QAction::triggered, qApp, QApplication::quit);

    statusBar()->showMessage("Words: 34, Characters: 161");
}

MainWindow::~MainWindow()
{
    delete ui;
}


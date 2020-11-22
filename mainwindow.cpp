#include <QToolBar>
#include <QTextEdit>
#include <QFileDialog>
#include <QLineEdit>
#include <sstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codeeditor.h"
#include "text_proc.h"

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

    connect(new_ac, &QAction::triggered, file_op::new_file);
    connect(open_ac, &QAction::triggered, file_op::open);
    connect(save_ac, &QAction::triggered, file_op::save);
    connect(close_ac, &QAction::triggered, file_op::close);
    connect(quit, &QAction::triggered, this, &QWidget::close);

    QToolBar *toolbar = addToolBar("main toolbar");

    QPixmap undopix(":images/undo.png");
    QPixmap redopix(":images/redo.png");
    QPixmap valpix(":images/validate.png");
    QPixmap findpix(":images/find.svg");

//    toolbar->addAction(QIcon(undopix), "Undo");
//    toolbar->addAction(QIcon(redopix), "Redo");
    save_ac = toolbar->addAction(QIcon(savepix), "Save");
    QAction *val_ac = toolbar->addAction(QIcon(valpix),
                                         "Validate JSON file");
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer);
    line_edit = new QLineEdit("Write something to find...", this);
    line_edit->setFixedWidth(200);
    toolbar->addWidget(line_edit);
    QAction *find_ac = toolbar->addAction(QIcon(findpix), "Find");

    connect(save_ac, &QAction::triggered, file_op::save);
    connect(val_ac, &QAction::triggered, this, &MainWindow::verify_msg);
    connect(find_ac, &QAction::triggered, this, &MainWindow::on_find_clicked);
    connect(line_edit, &QLineEdit::textChanged,
            this, [=]() {isFirstTime = true;});

    code_editor= new CodeEditor(this);
    setCentralWidget(code_editor);
    code_editor->setUndoRedoEnabled(true);

    statusBar()->showMessage("Welcome to JSON Editor.");
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

void MainWindow::set_stbar_text(QString text){
    auto window = get_instance();
    window->statusBar()->showMessage(text);
}

void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply = file_op::close();
    if (QMessageBox::Cancel == reply) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::verify_msg(){
    QString text = code_editor->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::information(this,
                                 "File is empty.",
                                 "File is empty.");
        return;
    }
    std::stringstream ss;
    ss << "The file is ";
    text_proc::val_res result = text_proc::isValid(text);
    if (result.isValid) {
        ss << "VALID ";
    } else {
        ss << "NOT valid ";
    }
    ss << "JSON file!";
    if (!result.isValid) {
        ss << "\nThe reason can be somewhere near line "
              << result.row
              << ", character " << result.at;
    }
    QMessageBox::information(this,
                             "Validation result",
                             QString(ss.str().c_str()));
}

void MainWindow::on_find_clicked() {
    QString searchString = line_edit->text();
    QTextDocument *document = code_editor->document();

    bool found = false;

    if (isFirstTime == false)
        document->undo();

    if (searchString.isEmpty()) {
        QMessageBox::information(this, tr("Empty Search Field"),
                "The search field is empty. Please enter a word and click Find.");
        return;
    } else if (document->isEmpty()) {
        QMessageBox::information(this, tr("File is empty."),
                "File is empty.");
        return;
    } else {

        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::darkGreen);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
            highlightCursor = document->find(searchString, highlightCursor);

            if (!highlightCursor.isNull()) {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight,
                                       QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();
        isFirstTime = false;

        if (found == false) {
            QMessageBox::information(this, tr("Word Not Found"),
                "Sorry, the word cannot be found.");
        }
    }
}

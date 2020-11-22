#include <QFileDialog>
#include <QToolBar>
#include <string>
#include <QMessageBox>
#include "file_operations.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "text_proc.h"

namespace file_op {

bool is_on_disk = 0, is_changed = 0;
QString file_path = "";

void new_file() {
    close();
}

void open()
{
    MainWindow *window = MainWindow::get_instance();
    file_path = QFileDialog::getOpenFileName(
                            window,
                            "Select one file to open",
                            "",
                            "JSON format (*.txt *.json)");
    if (file_path != "") {
        QFile file(file_path);
        file.open(QFile::ReadOnly | QFile::Text);
        QString text = file.readAll();
        window->code_editor->setPlainText(text);
        stbar::show_full_info();
        file.close();
        is_on_disk = true;
    }
}

void save() {
    auto window = MainWindow::get_instance();
    QString content = window->code_editor->toPlainText();

    if (!is_on_disk) {
        file_path = QFileDialog::getSaveFileName(
                    window,
                    "Save File",
                    "",
                    "JSON format (*.txt *.json)"
        );
    }

    if ("" != file_path) {
        QFile file(file_path);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(content.toUtf8());
            is_on_disk = true;
            is_changed = false;
            MainWindow::set_stbar_text("File was saved.");
        } else {
          qWarning("Could not open file");
        }
    }
}

QMessageBox::StandardButton close() {
    MainWindow *window = MainWindow::get_instance();
    bool is_action_canceled = false;
    QMessageBox::StandardButton reply = QMessageBox::NoButton;
    if (is_changed) {
        reply = QMessageBox::question(window,
            "File is changed", "Do you want to save it?",
            QMessageBox::Cancel|QMessageBox::No|QMessageBox::Yes
        );
        if (reply == QMessageBox::Cancel){
            is_action_canceled = true;
        } else {
            is_changed = false;
            if (reply == QMessageBox::Yes) {
                save();
            }
        }
    }
    if (!is_action_canceled) {
        window->code_editor->clear();
        file_path = "";
        window->set_stbar_text("File is closed.");
    }
    return reply;
}

}

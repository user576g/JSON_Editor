#include <QFileDialog>
#include "file_operations.h"
#include "mainwindow.h"

namespace file_op {

bool is_on_disk = 0;
QString file_path = "";

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
        window->code_editor->setPlainText(file.readAll());
        file.close();
        is_on_disk = true;
    }
}

void new_file() {
    MainWindow *window = MainWindow::get_instance();
    window->code_editor->clear();
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
        } else {
          qWarning("Could not open file");
        }
    }
}

}

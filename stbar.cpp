#include <QString>
#include "stbar.h"
#include "mainwindow.h"
#include "text_proc.h"

namespace stbar
{

QString make_str(){
    auto window = MainWindow::get_instance();
    QString text = window->code_editor->toPlainText();
    int chars_number = text.size();
    auto words_number = text_proc::count_words(text);
    return "Words: " + QString::number(words_number)
        + ", All symbols: " + QString::number(chars_number);
}

void show_full_info()
{
    MainWindow::set_stbar_text( make_str() );
}

void key_press_react() {
    MainWindow::set_stbar_text("File is not saved. " + make_str());
}

}

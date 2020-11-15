#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <QMessageBox>

namespace file_op {
    extern bool is_changed;

    void open();
    void new_file();
    void save();
    QMessageBox::StandardButton close();
};

#endif // FILE_OPERATIONS_H

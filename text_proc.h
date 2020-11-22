#ifndef TEXT_PROC_H
#define TEXT_PROC_H
#include <QString>

namespace text_proc
{
unsigned long long count_words(QString text);

struct val_res {
    //line number where file is not valid
    int row = 1;

    //symbol poistion where file is not valid
    int at = 1;

    bool isValid = false;
};

val_res isValid(QString);
};

#endif // TEXT_PROC_H

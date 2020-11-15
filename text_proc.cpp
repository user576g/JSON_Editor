#include <cstring>
#include "text_proc.h"

namespace text_proc
{
unsigned long long count_words(QString text) {
    char separators[] = " ,.!?:;)([]'\n";
    unsigned long long counter = 0;
    bool wasChar = false;
    for (QChar const &c : text) {
        if (std::strchr(separators, c.toLatin1()) == NULL) {
            wasChar = true;
        } else {
            if (wasChar) {
                ++counter;
                wasChar = false;
            }
        }
    }
    if (wasChar) {
        ++counter;
    }
    return counter;
}
}

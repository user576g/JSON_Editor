#include <cstring>
#include "text_proc.h"
#include <stack>

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

val_res isValid(QString text) {
    std::stack<char> stack;
    val_res result;
    char last = 0;

    for (QChar qch : text) {
        char ch = qch.toLatin1();

    // ignore symbols in double quotes
        if (!stack.empty()
                && '"' == stack.top()
                && '"' != ch
                ) {
            ++result.at;
            continue;
        }

        switch (ch) {
        case '\"':
           if (stack.empty()) {
                return result;
           }
           last = stack.top();
           if (last == '\"') {
                // It's a closing quote
                stack.pop();
           } else {
                // It's an opening quote
                stack.push(ch);
           }
           break;
        case ':':
            if (stack.empty()) {
                 return result;
            }
            last = stack.top();
            if ('"' != last) {
                stack.push(ch);
            }
            break;
        case ',':
            if (stack.empty()) {
                 return result;
            }
            last = stack.top();
            if (':' == last) {
                stack.pop();
            } else {
                stack.push(ch);
            }
            break;
        case '{':
            stack.push(ch);
            break;
        case '}':
            if (stack.empty()) {
                return result;
            }
            last = stack.top();
            if (last == '{') {
                stack.pop();
            } else {
                if (last == ':') {
                    stack.pop();
                    last = stack.top();
                    if ('{' == last) {
                        stack.pop();
                    } else {
                        return result;
                    }
                } else {
                    return result;
                }
            }
            break;
        case '[':
            stack.push(ch);
            break;
        case ']':
            if (stack.empty()) {
                return result;
            }
            last = stack.top();
            while (',' == last) {
                stack.pop();
                last = stack.top();
            }
            if (last == '[') {
                stack.pop();
            } else {
                return result;
            }
            break;
        case '\n':
            ++result.row;
            result.at = 1;
        }
        ++result.at;
    }
    result.isValid = stack.empty();
    return result;
}
}

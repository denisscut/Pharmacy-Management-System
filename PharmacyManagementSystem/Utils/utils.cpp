#include <climits>
#include <string>

using std::string;

int strtoint(string str) {
    string::iterator it = str.begin();
    if (*it == '\n')
        return INT_MAX;
    int num = 0;
    int isNegetive = 0;
    if (*it == '-') {
        isNegetive = 1;
        it++;
    }
    while (it != str.end() && (*it >= '0' && *it <= '9')) {
        num = num * 10 + (*it - '0');
        it++;
    }
    if (it != str.end() && *it != '\n')
        return INT_MAX;
    if (isNegetive)
        num = -1 * num;
    return num;
}
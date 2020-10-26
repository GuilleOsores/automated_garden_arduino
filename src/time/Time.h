#ifndef MY_TIME_H
#define MY_TIME_H

#include <TimeLib.h>

inline time_t getNow() {
    return now();
}

inline int timeDiff (time_t t1, time_t t2) {
    return t1 - t2;
}

#endif

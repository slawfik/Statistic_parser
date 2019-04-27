#include "miestnosti_tele.h"

miestnosti_tele::miestnosti_tele() {
    n_akcii = 0;
}

miestnosti_tele::~miestnosti_tele()     {
    while((n_akcii-1) >= 0) {
        delete array[--n_akcii];
    }
}

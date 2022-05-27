#include <time.h>
#include <stdbool.h>

static bool ascent_request = false;

void ascentRequest() {
    ascent_request = true;
}

bool getAscentRequest() {
    return ascent_request;
}

void clearAscentRequest() {
    ascent_request = false;
}


void getDate(time_t* date) {
    time(date);
}

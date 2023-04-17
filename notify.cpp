#include <stdio.h>
#include <time.h>
#include <iostream>
#include <systemd/sd-bus.h>

using namespace std;

int main() {

    sd_bus_message* m = NULL;
    sd_bus* bus = NULL;
    sd_bus_default_user(&bus);
    int ret = sd_bus_message_new_method_call(bus, &m, "org.freedesktop.Notifications",
        "/org/freedesktop/Notifications",
        "org.freedesktop.Notifications", "Notify");
    if (ret < 0) {
        fprintf(stderr, "sd_bus_message_new_method_call: %s\n", strerror(-ret));
        return -1;
    }
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    ret = sd_bus_message_append(m, "susssasa{sv}i",
        "system-notify", // STRING app_name
        0, // UINT32 replaces_id
        "dialog-information", // STRING app_icon
        "Time now:", // STRING summary
        asctime (timeinfo), // STRING body
        0, // ARRAY actions
        0, // DICT hints
        -1 // INT32 expire_timeout
    );
     if (ret < 0) {
        fprintf(stderr, "sd_bus_message_append: %s\n", strerror(-ret));
        sd_bus_message_unref(m);
        return -1;
    }

    ret = sd_bus_call(bus, m, 0, NULL, NULL);
    return 0;
}
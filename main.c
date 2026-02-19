#include <linux/uinput.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct libevdev *dev;
struct libevdev_uinput *uidev;

int main(void) {
  int fd, uifd, err;
  // replace with mouse input file
  fd = open("/dev/input/event14", O_RDONLY);
  if (fd == -1) {
    perror("failed to read file");
    exit(EXIT_FAILURE);
  }

  err = libevdev_new_from_fd(fd, &dev);
  if (err != 0) {
    perror("failed to initalize device");
    exit(EXIT_FAILURE);
  }

  uifd = open("/dev/uinput", O_RDWR);
  if (uifd == -1) {
    perror("failed to read file");
    exit(EXIT_FAILURE);
  }

  err = libevdev_uinput_create_from_device(dev, uifd, &uidev);
  if (err != 0) {
    perror("failed to initalize device");
    exit(EXIT_FAILURE);
  }

  printf("mouse jiggler running\n");

  while(1) {
    libevdev_uinput_write_event(uidev, EV_REL, REL_X, 4);
    libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
    libevdev_uinput_write_event(uidev, EV_REL, REL_X, -4);
    libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
    sleep(10);
  }

  libevdev_uinput_destroy(uidev);
  libevdev_free(dev);
  close(uifd);
  close(fd);
  return 0;
}

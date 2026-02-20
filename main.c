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
  dev = libevdev_new();
  libevdev_set_name(dev, "new mouse");
  libevdev_enable_event_type(dev, EV_REL);
  libevdev_enable_event_code(dev, EV_REL, REL_X, NULL);
  libevdev_enable_event_code(dev, EV_REL, REL_Y, NULL);
  libevdev_enable_event_type(dev, EV_KEY);
  libevdev_enable_event_code(dev, EV_KEY, BTN_LEFT, NULL);

  int new_dev = libevdev_uinput_create_from_device(dev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uidev);
  if (new_dev != 0) {
    perror("failed to create device");
    exit(EXIT_FAILURE);
  }

  printf("mouse wiggler running\n");

  while(1) {
    libevdev_uinput_write_event(uidev, EV_REL, REL_X, 4);
    libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
    libevdev_uinput_write_event(uidev, EV_REL, REL_X, -4);
    libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
    sleep(10);
  }

  libevdev_uinput_destroy(uidev);
  libevdev_free(dev);
  return 0;
}

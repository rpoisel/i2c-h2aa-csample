#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>

#include <linux/i2c-dev.h>

#define I2C_LINUX_DEV "/dev/i2c-1"
#define I2C_H2AA_ADDR 0x58
#define I2C_H2AA_NUM_CHANNELS 4

int main(void)
{
  int fd = 0;
  ssize_t num_written = 0;
  uint8_t buf[11] = { 0 };
  int cnt = 0;

  /* see http://www.horter.de/blog/i2c-analog-output-4-kanaele-10-bit/ */
  buf[0] = 0; /* pointer */
  for (cnt = 0; cnt < I2C_H2AA_NUM_CHANNELS; cnt++)
  {
    buf[cnt * 2 + 1] = 0x00; /* low byte */
    buf[cnt * 2 + 2] = 0x01; /* high byte */
  }

  fd = open(I2C_LINUX_DEV, O_RDWR);

  if (fd < 0)
  {
    fprintf(stderr, "Could not open device (%s): %s\n", I2C_LINUX_DEV, strerror(errno));
    return 1;
  }

  if (ioctl(fd, I2C_SLAVE, I2C_H2AA_ADDR) < 0)
  {
    fprintf(stderr, "Could not set device address (0x%02x) %s\n", I2C_H2AA_ADDR, strerror(errno));
    return 1;
  }

  num_written = write(fd, buf, sizeof(buf));

  if (num_written < 0)
  {
    fprintf(stderr, "Could not write to I2C bus (%s): %s", I2C_LINUX_DEV, strerror(errno));
    return 1;
  }

  if (num_written != sizeof(buf))
  {
    fprintf(stderr, "Could not write %zu bytes. %zd have been written instead.\n", sizeof(buf), num_written);
  }

  return 0;
}

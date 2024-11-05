#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define DEVICE_PATH "/dev/simple_char_dev"

int main() {
    int fd;
    char write_buffer[] = "SHIFANA_B221204CS";
    char read_buffer[1024];
    // Open the device file
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return EXIT_FAILURE;
    }
    // Write to the device
    if (write(fd, write_buffer, strlen(write_buffer)) < 0) {
        perror("Failed to write to the device");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Written to the device: %s\n", write_buffer);
    // Read from the device
    if (read(fd, read_buffer, sizeof(read_buffer)) < 0) {
        perror("Failed to read from the device");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Read from the device: %s\n", read_buffer);
    // Close the device
    close(fd);
    return EXIT_SUCCESS;
}


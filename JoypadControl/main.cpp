
#include <iostream>
#include <csignal>
#include <thread>

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <libevdev-1.0/libevdev/libevdev.h>

#include <lcm/lcm-cpp.hpp>
#include <rovertypes/twist_t.hpp>

using namespace std::chrono_literals;

bool stop = false;
void signalHandler(int s)
{
    stop = true;
}

int main(int argc, char* argv[])
{

    signal(SIGINT, signalHandler);

    lcm::LCM lcm;

    if(!lcm.good()) return 1;


    struct libevdev *dev = NULL;
    int fd;

    // Open the joystick device
    fd = open("/dev/input/event10", O_RDONLY|O_NONBLOCK);
    if (fd < 0) {
        std::cerr << "Failed to open device\n";
        return 1;
    }

    // Create libevdev device
    int rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        std::cerr << "Failed to init libevdev (" << rc << ")\n";
        close(fd);
        return 1;
    }

    struct input_event ev;
    rovertypes::twist_t tw;
    double percentage = 0;

    while(!stop)
    {
        tw.timestamp = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count();

        if(libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL | LIBEVDEV_READ_FLAG_BLOCKING, &ev) < 0){ continue; }
        
         if (ev.type == EV_ABS) {

            const struct input_absinfo *abs = libevdev_get_abs_info(dev, ev.code);
            
            if (abs) {
                percentage = ((double)(ev.value - abs->minimum) / 
                                    (abs->maximum - abs->minimum)) * 100.0 - 50;
            }

            switch (ev.code)
            {
            case ABS_Y:
                tw.v = percentage;
                break;
            case ABS_RX:
                tw.w = percentage;
                break;
            default:
                break;
            }
        }
        lcm.publish("/twist.set", &tw);
        std::this_thread::sleep_for(5ms);
    }

    libevdev_free(dev);
    close(fd);

    std::cout << "Closing joystick..." << std::endl;

    return 0;
}

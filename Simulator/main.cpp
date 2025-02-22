#include <lcm/lcm-cpp.hpp>
#include <rovertypes/twist_t.hpp>

#include <iostream>
#include <csignal>
#include <thread>

using namespace std::chrono_literals;

bool stop = false;
void signalHandler(int s)
{
    stop = true;
}

int main(int argc, char *argv[])
{

    signal(SIGINT, signalHandler);

    lcm::LCM lcm;

    if (!lcm.good())
        return 1;

    rovertypes::twist_t tw = {
        .timestamp = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
        ).count(), 
        .v = 3, 
        .w = 2.5
    };

    while (!stop)
    {
        lcm.publish("/twist", &tw);
        std::this_thread::sleep_for(30ms);
        std::cout << "pub" << std::endl;
    }
    return 0;
}


#include <iostream>
#include <csignal>
#include <thread>

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

    rovertypes::twist_t tw = {.timestamp = 100, .v = 3, .w = 2.5};

    while(!stop)
    {
        lcm.publish("inputs.twist_refs", &tw);
        std::this_thread::sleep_for(100ms);
        std::cout << "pub" << std::endl;
    }
    return 0;
}

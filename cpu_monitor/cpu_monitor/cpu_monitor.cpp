#include <windows.h>
#include <iostream>
#include <thread>

class CpuMonitor
{
public:
    double getCpuUsage()
    {
        FILETIME idleTime, kernelTime, userTime;

        if (!GetSystemTimes(&idleTime, &kernelTime, &userTime))
            return -1.0;

        auto idle = fileTimeToUint64(idleTime);
        auto kernel = fileTimeToUint64(kernelTime);
        auto user = fileTimeToUint64(userTime);

        auto idleDiff = idle - lastIdle;
        auto totalDiff = (kernel + user) - lastTotal;

        lastIdle = idle;
        lastTotal = kernel + user;

        if (totalDiff == 0)
            return 0.0;

        return (1.0 - (double)idleDiff / totalDiff) * 100.0;
    }

private:
    uint64_t lastIdle = 0;
    uint64_t lastTotal = 0;

    static uint64_t fileTimeToUint64(FILETIME ft)
    {
        return (static_cast<uint64_t>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
    }
};

int main()
{
    CpuMonitor cpu;

    std::cout << "CPU Usage Monitor (Press Ctrl+C to quit)" << std::endl;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        double usage = cpu.getCpuUsage();

        system("cls");   // clear console (Windows)

        std::cout << "Current CPU Load: " << usage << " %" << std::endl;
    }
}

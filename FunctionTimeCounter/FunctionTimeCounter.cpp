// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/CppExamples

#include <iostream>
#include <chrono>

class TimeCounter
{
public:
    TimeCounter() = default;

    ~TimeCounter()
    {
        std::cout << "Count result: " << getCurrentTime() - m_start_time << "ms" << std::endl;
    }

    void startCount()
    {
        std::cout << "Starting counting time" << std::endl;
        m_start_time = getCurrentTime();
    }

private:
    const std::uint64_t getCurrentTime() const
    {
        const auto current_time = std::chrono::system_clock::now();
        const auto time_since_epoch = current_time.time_since_epoch();
        const auto current_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_since_epoch);

        return current_time_ms.count();
    }

    std::uint64_t m_start_time = 0;
};

int main()
{
    const auto counter = std::make_unique<TimeCounter>();
    counter->startCount();
    
    constexpr unsigned int loop_max = 999u;
    std::cout << "Starting loop with max value: " << loop_max << std::endl << std::endl;
    
    for (unsigned int iterator = 0u; iterator < loop_max; ++iterator)
    {
        std::cout << iterator << ", ";
    }

    std::cout << std::endl << std::endl;

    /* The time spent will be printed in the counter destruction when the function scope reaches the end */

    return 0;
}
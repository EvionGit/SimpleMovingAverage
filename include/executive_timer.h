#ifndef EXECUTIVE_TIMER_RAII_H
#define EXECUTIVE_TIMER_RAII_H

#include <chrono>
#include <stdio.h>
#include <string>

class ExecTimer final
{
    using clock = std::chrono::high_resolution_clock;
    std::chrono::time_point<clock> start_;
    std::string msg_;
public:
    ExecTimer() : start_(clock::now()){}
    ExecTimer(std::string msg) : start_(clock::now()), msg_(msg){}
    ~ExecTimer()
    {   
        std::chrono::duration<float> dur = clock::now() - start_;
        if(!msg_.empty())
            printf("[%s] ",msg_.c_str());
        printf("%.5f sec\n",dur.count());
    }
};

#endif

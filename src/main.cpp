#include "../include/sma.h"
#include "../include/random_generator.h"
#include "../include/executive_timer.h"

#include <stdint.h>
#include <cmath>
#include <assert.h>


#define SMA_TEST template<typename T> void

SMA_TEST tester(const std::vector<T>& input, const std::vector<T>& expected, T epsilon=0.00001)
{
    assert(input.size() == expected.size() || !input.empty());
    for(auto it = input.begin(), it2 = expected.begin(), end = input.end(); it != end;++it,++it2)
    {
        /* round at .000001 by default */
        float abs_dif = fabs(*it - *it2);
        assert(abs_dif <= epsilon);

    }
}

int main()
{
    
    auto data_f = rand_generate<float>(10000000,-10,10);
    auto data_d = rand_generate<double>(10000000,-10,10);


    std::vector<int> winsize {4,8,16,32,64,128};

    for(int i = 0; i < winsize.size(); ++i)
    {
        {
            ExecTimer timer("float -n 10`000`000 -w " + std::to_string(winsize[i]));
            auto avg = sma(data_f.begin(),data_f.end(),winsize[i]);
        }
        {
            ExecTimer timer("double -n 10`000`000 -w " + std::to_string(winsize[i]));
            auto avg = sma(data_d.begin(),data_d.end(),winsize[i]);
        }
    }
    
   
   
    return 0;
}
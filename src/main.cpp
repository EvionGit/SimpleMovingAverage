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
    /* generate floats and doubles */
    auto data_f = rand_generate<float>(10000000,-10,10);
    auto data_d = rand_generate<double>(10000000,-10,10);

    /* testing for correct parallel work*/
    auto single = sma(data_d.begin(), data_d.end(),16);
    auto multi = sma_parallel(data_d.begin(), data_d.end(),16,8);
    tester(multi,single);

    /* testing performances */
    std::vector<int> winsize {4,8,16,32,64,128};
    std::vector<int> threadsize {2,4,16,32,128,1024};

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

        for(int j = 0; j < threadsize.size(); ++j)
        {
            ExecTimer timer("double -t "+ std::to_string(threadsize[j]) +"-n 10`000`000 -w " + std::to_string(winsize[i]));
            auto avg = sma_parallel(data_d.begin(),data_d.end(),winsize[i],threadsize[j]);
        }
        
    }
    
   
   
    return 0;
}
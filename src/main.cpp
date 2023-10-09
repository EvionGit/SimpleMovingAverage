#include "../include/sma.h"
#include "../include/random_generator.h"

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
    auto data = rand_generate<float>(100000,1,10);
   
    auto avg = sma(data.begin(),data.end(),4);
   
    

    return 0;
}
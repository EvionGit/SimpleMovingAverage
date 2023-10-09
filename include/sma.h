#ifndef SIMPLE_MOVING_AVERAGE_HEADER_H
#define SIMPLE_MOVING_AVERAGE_HEADER_H

#include <vector>
#include <numeric>

/*
    ALGORITHM:

        Simple Moving Average - O(n)
        
            - Size: 5
            - Window: 3

        1) calc average sum for first window 
            [[1 2 3] 4 5] --> 6/3

        2) slide window
            [1 [2 3 4] 5]

        3) substract from the last average prev left-bounded element devided by the window size
            --> 6/3 - 1/3 = 5/3
        
        4) increase average by the new right-bounded element devided by window size 
            --> 5/3 + 4/3 = 9/3
*/

/* base algo-func */
template <typename Iterator>
std::vector<typename Iterator::value_type> sma(Iterator begin, Iterator end, size_t window)
{
     using T = typename Iterator::value_type;
    size_t count = std::distance(begin,end);
    
    if(count < window)
        return {}; // return empty vec if not enough elements

    std::vector<T> avg;
    avg.reserve(count - window + 1);
   
    /* shift right pointer for any iterator type */
    Iterator right_win_edge = std::next(begin,window);
    
    /* get first window average sum */
    T first_win_sum = 0;
    first_win_sum = std::accumulate(begin,right_win_edge,first_win_sum) / window;
    avg.emplace_back(first_win_sum);

    /* slide and re-calculate average */
    for( ; right_win_edge != end; ++right_win_edge, ++begin)
        avg.emplace_back(avg.back() - *begin / window + *right_win_edge / window);

    return avg;
}


#endif 
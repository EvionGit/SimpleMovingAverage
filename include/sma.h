#ifndef SIMPLE_MOVING_AVERAGE_HEADER_H
#define SIMPLE_MOVING_AVERAGE_HEADER_H

#include <vector>
#include <numeric>
#include <future>
#include <thread>

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


/* parallel func */
template <typename Iterator>
std::vector<typename Iterator::value_type> sma_parallel(Iterator begin, Iterator end,size_t window, size_t num_threads)
{
    if(!num_threads)
        return {};
    else if(num_threads == 1)
        return sma(begin,end,window);

    
    using T = typename Iterator::value_type;
    size_t count = std::distance(begin,end);
    
    if(count < window)
        return {}; // return empty vec if not enough elements

    size_t windows_amount = count - window + 1;
    std::vector<T> reduced;
    reduced.reserve(windows_amount);

    num_threads = num_threads > windows_amount ? windows_amount : num_threads; // dont run unnecessary threads
    size_t iter_per_thread = windows_amount / num_threads; //work windows in each thread

    std::vector<std::future<std::vector<T>>> futures;
    futures.reserve(num_threads);

    
    for(size_t t = 0; t < num_threads-1; ++t)
    {
        auto thread_begin = begin; // beginning first work window
        begin = std::next(begin,iter_per_thread-1); // slide beginnig to the beginning last work window
        auto thread_end = std::next(begin,window); // ending last work window
        begin = std::next(begin,1); // move to the next work window
        futures.emplace_back(std::move(std::async(std::launch::async,[=]{return sma(thread_begin,thread_end,window);})));
    }
    futures.emplace_back(std::move(std::async(std::launch::async,[=]{return sma(begin,end,window);})));

    
    for(auto it = futures.begin(), end = futures.end(); it != end; ++it)
    {
        std::vector<T> returned = it->get();
        reduced.insert(reduced.end(),returned.begin(),returned.end());
    }

    return reduced;    
}

#endif 
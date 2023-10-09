#ifndef VECTOR_RANDOM_GENERATOR_H
#define VECTOR_RANDOM_GENERATOR_H

#include <vector>
#include <random>

/* uniform type complile definer */
template <typename T, bool is_int>
struct uniform{using type = std::uniform_int_distribution<T>;};

template <typename T>
struct uniform<T,false>{using type = std::uniform_real_distribution<T>;};


/* randomize generator */
template <typename T>
std::vector<T> rand_generate(size_t size,int64_t from, int64_t to)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    typename uniform<T,std::is_integral_v<T>>::type dist(from,to);

    std::vector<T> v;
    v.reserve(size);
    for(size_t i = 0; i < size;++i)
        v.emplace_back(dist(gen));

    return v;
}

#endif

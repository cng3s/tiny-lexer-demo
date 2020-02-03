#ifndef HZCC_DSA_VEC_STACK_HPP
#define HZCC_DSA_VEC_STACK_HPP

#include "dsa_vec.hpp"

namespace hzcc {

    template <typename T>
    class dsa_vec_stack : public dsa_vec<T> {
    protected:
            using dsa_vec<T>::_size;
            using dsa_vec<T>::insert;
            using dsa_vec<T>::rm;
            using dsa_vec<T>::_elem;

    public:
            explicit dsa_vec_stack()
                : dsa_vec<T>()
            {}

    public:
            void push(const T &e)
            {
                    insert(_size, e);
            }

            T pop()
            {
                    return rm(_size - 1);
            }

            T& top()
            {
                    return (*this)[_size - 1];
            }

            void print_info()
            {
                    for (int i = 0; i < _size; i++)
                            std::cout << _elem[i] << " ";
                    std::cout << std::endl;
            }
    };
}

#endif //MYCC_DSA_VEC_STACK_HPP

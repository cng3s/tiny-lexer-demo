#ifndef HZCC_DSA_ARRAY_HPP
#define HZCC_DSA_ARRAY_HPP

#include <cassert>
#include <iostream>

namespace hzcc {


    /* 动态分配数组
     * ToDo:
     * 添加循环数组和惰性删除(维护两个size， realsize存储未删除元素个数, size存储总个数)
     * 变得更适合读程序的分配方式，即读程序后再分配空间
     * */
    template<typename Type>
    class dsa_array {
    private:
            Type *data;       // data指向一个类型为Type的数组
            int size;         // data数组使用长度
            int capacity;     // data数组总长度

    public:
            explicit dsa_array(int cap = 1000)
                    : capacity(cap), size(0)
            { data = new Type[cap]; }

            ~dsa_array()
            {
                    delete[] data;
            }

    public:
            int get_size() const
            {
                    return size;
            }

            int get_capacity() const
            {
                    return capacity;
            }

            int find(Type elem)
            {
                    for (int i = 0; i < size; i++) {
                            if (data[i] == elem)
                                    return i;
                    }
                    return -1;
            }

            Type rm(int index)
            {
                    Type ret = data[index];
                    for (int i = index + 1; i < size; i++) {
                            data[i - 1] = data[i];
                    }
                    size--;
                    if (size == (capacity >> 2) && (capacity >> 1) >= 20)
                            resize(capacity >> 1);
                    return ret;
            }

            Type rm_last()
            {
                    return rm(size - 1);
            }

            void rm_elem(Type elem)
            {
                    int index = find(elem);
                    if (index != -1)
                            rm(index);
            }

            void add(int index, Type elem)
            {
                    if (size == capacity)
                            resize(capacity << 1);
                    for (int i = size-1; i >= index; i--) {
                            data[i+1] = data[i];
                    }
                    data[index] = elem;
                    size++;
            }

            void add_last(Type elem)
            {
                    add(size, elem);
            }

            Type get(int index) const
            {
                    if (index < 0 || index >= size)
                            return Type(NULL);
                    return data[index];
            }

            void set(int index, Type elem)
            {
                    if (index < 0 || index > size)
                            return;
                    data[index] = elem;
            }

            void print_info()
            {
                    std::cout << "dsa_array size = " << size << ",capacity = " << capacity;
                    std::cout << "\nData:[";

                    // 读取一： 输出数组详细信息，并用,隔开每个元素
                    /*for (int i = 0; i < size; i++) {
                        std::cout << data[i];
                        if (i != size-1)
                            std::cout << ",";
                    }*/
                    // 读取二： 直接输出数组全部内容

                    for (int i = 0; i < size; i ++)
                            std::cout << data[i] << " ";
                    std::cout << "]" << std::endl;
            }

    private:
            void resize(int newCapacity)
            {
                    Type *newData = new Type[newCapacity];
                    for (int i = 0; i < size; i++)
                            newData[i] = data[i];
                    delete[] data;
                    data = newData;
                    capacity = newCapacity;
            }
    };
}

#endif //MYCC_ARRAY_HPP

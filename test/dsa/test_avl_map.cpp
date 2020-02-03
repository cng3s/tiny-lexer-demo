#include "test_avl_map.hpp"
#include <iostream>
using namespace std;

namespace hzcc {


namespace testcc {

    void test_avl_map::case1() {
        /* 读取傲慢与偏见并测试词频的测试用例 */
        auto *words = new dsa_array<string>();
        string filename = "../test/dsa/pride-and-prejudice.txt";   // 可执行文件在cmake-build-debug下，所以以该目录为相对目录
        ifstream in(filename, ios::in);
        string tmp;
        assert(in.is_open());
        while ((in >> tmp) && tmp != "/0") {
            words->add_last(tmp);
        }
        cout << "Total words: " << words->get_size() << endl;
        auto *map = new dsa_avl_map<string, int>();
        int size = words->get_size();
        string word;
        //words->printInfo();
        for (int i = 0; i < size; i++) {
            word = words->get(i);
            // 这里要好好考虑如何改进效率问题，contains查找一次,set查找一次
            if (map->contains(word))
                map->set(word, map->get(word) + 1);
            else
                map->add(word, 1);
        }
        cout << "Total different words: " << map->size()
             << "\nFrequency of PRIDE: " << map->get("pride")
             << "\nFrequency of PREJUDICE: " << map->get("prejudice")
             << "\nis Balanced : " << map->balanced() << endl;
        delete map;
    }
}

}
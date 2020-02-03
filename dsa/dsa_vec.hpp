#ifndef MYCC_DSA_VEC_HPP
#define MYCC_DSA_VEC_HPP

#include <algorithm>

namespace hzcc {

    template <typename T>
    class dsa_vec {
    protected:
            typedef int rank;
#define DSA_VEC_DEFAULT_CAPACITY     10

    protected:
            rank            _size;
            int             _capacity;
            T               *_elem;

    protected:
            /* copy array between [lo, hi) */
            void cp_from(const T *arr, rank lo, rank hi)
            {
                    _elem = new T[_capacity = (unsigned int)((hi - lo) << 1)];
                    _size = 0;
                    while (lo < hi)
                            _elem[_size++] = arr[lo++];
            }

            /* when vector is full(_size == _capacity) then allocate new vector
             * which _capacity = (2 * old _capacity) and copy elements to new space
             * and update _size and _capacity
             * */
            void expand()
            {
                    if (_size < _capacity)
                            return;
                    if (_capacity < DSA_VEC_DEFAULT_CAPACITY)
                            _capacity = DSA_VEC_DEFAULT_CAPACITY;
                    T *old_elem = _elem;
                    _elem = new T[_capacity <<= 1];
                    for (int i = 0; i < _size; i++)
                            _elem[i] = old_elem[i];
                    delete[] old_elem;
            }

            /* when _size = (25% * _capacity) and _capacity > (VEC_DEFAULT_CAPACITY / 2)
             * then _capacity = (_capacity / 2) and copy elem to new space and update info
             * */
            void shrink()
            {
                    if (_capacity < DSA_VEC_DEFAULT_CAPACITY << 1)
                            return;
                    if (_size << 2 > _capacity)
                            return;
                    T *old_elem = _elem;
                    _elem = new T[_capacity >>= 1];
                    for (int i = 0; i < _size; i++)
                            _elem[i] = old_elem[i];
                    delete[] old_elem;
            }

    public: /* constructor and destructor functions */

            explicit dsa_vec(unsigned int c = DSA_VEC_DEFAULT_CAPACITY, int s = 0, T v = 0)
                : _capacity(c)
            {
               _elem = new T[_capacity];
               for (_size = 0; _size < s; _elem[_size++] = v)
                   ;
            }

            explicit dsa_vec(const T *arr, rank n)
            {
                cp_from(arr, 0, n);
            }

            explicit dsa_vec(const T *arr, rank lo, rank hi)
            {
                    cp_from(arr, lo, hi);
            }

            explicit dsa_vec(const dsa_vec<T> &arg)
            {
                    cp_from(arg._elem, 0, arg._size);
            }

            explicit dsa_vec(const dsa_vec<T> &arg, rank lo, rank hi)
            {
                    cp_from(arg._elem, lo, hi);
            }

            ~dsa_vec()
            {
                    delete[] _elem;
            }

    public:  /* only-read interface */
            rank size() const
            {
                    return _size;
            }

            bool empty() const
            {
                    return !_size;
            }

            /* Returns the total number of pairs of inverse adjacent elements in a vector */
            int disordered() const
            {
                    int n  = 0;
                    for (int i = 1; i < _size; i++) {
                            if (_elem[i-1] > _elem[i])
                                    n++;
                    }
                    return n;
            }

            rank unordered_vec_search(const T &e) const
            {
                    return find(e, 0, _size);
            }

            /* Unordered vector sequential lookup:
             * returns the location of the last element e
             * when failed, returns lo - 1
             * */
            rank unordered_vec_search(const T &e, rank lo, rank hi) const
            {
                    while ((lo < hi--) && (e != !_elem[hi]))
                            ;
                    return hi;  // if hi < lo that means failed else hi hit the elem's rank
            }

            /* ordered_search() is the interface of ordered vector
             * */
            rank ordered_vec_search(const T &e) const
            {
                    return (0 >= _size) ? -1 : search(e, 0, _size);
            }

            /* random binary search or fibonacci search with 50% probability */
            rank ordered_vec_search(const T &e, rank lo, rank hi) const
            {
                    return bin_search(_elem, e, lo, hi);
            }

            static rank bin_search(T *arr, const T &e, rank lo, rank hi)
            {
                    while (lo < hi) {
                            rank mi = (lo + hi) >> 1;
                            (e < arr[mi]) ? hi = mi : lo = mi + 1;
                    }
                    return --lo;
            }

    public: /* read & write interface */

            /* override [] to read element */
            T& operator[](rank r) const
            {
                    return _elem[r];
            }

            /* override = to clone vector */
            dsa_vec<T> &operator=(const dsa_vec<T> &arg)
            {
                        if (_elem)
                                delete[] _elem;
                        cp_from(arg._elem, arg.size());
                        return *this;
            }

            /* remove element which rank is r in vector , 0 <= r < size */
            T rm(rank r)
            {
                    T e = _elem[r];
                    rm(r, r+1);
                    return e;
            }

            /* remove all elements which rank between[lo, hi) */
            int rm(rank lo, rank hi)
            {
                    if (lo == hi)
                            return 0;
                    while (hi < _size)
                            _elem[lo++] = _elem[hi++];
                    _size = lo;
                    shrink();
                    return hi - lo;
            }

            /* insert e to elem[r] */
            rank insert(rank r, const T &e)
            {
                    expand();
                    for (int i = _size; i > r; i--)
                            _elem[i] = _elem[i-1];
                    _elem[r] = e;
                    _size++;
                    return r;
            }

            rank insert(const T &e)
            {
                    return insert(_size, e);
            }

            void sort(rank lo, rank hi)
            {}

            /* Random scrambling of vectors so that
             * equal probability of each element appears at each location
             * */
            void unsort(rank lo, rank hi)
            {
                    T *elem = _elem + lo;
                    for (rank i = hi - lo; i > 0; i--)
                            std::swap(elem[i-1], elem[random()%i]);
            }

            /* shuffle elements */
            void unsort()
            {
                    unsort(0, _size);
            }

            /* delete duplicate elements in unordered vectors */
            int deduplicate()
            {
                    int old_size = _size;
                    rank i = 1;
                    while (i < _size)
                            (find(_elem[i], 0, i) < 0) ? i++ : rm(i);
                    return old_size - _size;
            }

            int uniquify()
            {
                    rank i = 0, j = 0;
                    while (++j < _size) {
                            if (_elem[i] != _elem[j])
                                    _elem[++i] = _elem[j];
                    }
                    _size = ++i;
                    shrink();
                    return j - i;
            }

    public: /* traverse functions */

            /* traverse and use function pointer,locality modification */
            void traverse(void (*visit)(T &arg))
            {
                    for (int i = 0; i < _size; i++)
                            visit(_elem[i]);
            }

            /* using function objects, it can be modified globally. */
            template <typename VST>
            void traverse(VST& visit)
            {
                    for (int i = 0; i < _size; i++)
                            visit(_elem[i]);
            }
    };
}

#endif //MYCC_DSA_VEC_HPP

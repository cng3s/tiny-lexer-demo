#ifndef HZCC_DSA_AVL_MAP_HPP
#define HZCC_DSA_AVL_MAP_HPP

#include "dsa_stack.hpp"
#include <algorithm>

namespace hzcc {

    template <typename K, typename V, typename Compare = std::less<K>>
    class dsa_avl_map {

    public:
            class _node {
            public:
                    K               _key;
                    V               _val;
                    _node            *_l, *_r;
                    unsigned int    _height;

            public:
                    explicit _node(K k = NULL, V v = NULL, _node *l = nullptr, _node *r = nullptr, unsigned int h = 1)
                            : _key(k), _val(v), _l(l), _r(r), _height(h)
                    {}

                    ~_node() = default;
            };

    private:
            _node            *_root;
            unsigned int    _size;

    public:
            explicit dsa_avl_map()
                    : _root(nullptr), _size(0)
            {}

            /* AVLMap析构函数
             * 先序遍历删除所有节点 */
            ~dsa_avl_map()
            {
                    auto stack = new dsa_stack<_node*>();
                    stack->push(_root);
                    for (_node *cur = nullptr; !stack->empty();) {
                            cur = stack->pop();
                            if (cur->_l)
                                    stack->push(cur->_l);
                            if (cur->_r)
                                    stack->push(cur->_r);
                            delete cur;
                    }
            }

    public:
            unsigned int height(_node *_node)
            {
                    return _node == nullptr ? 0 : _node->_height;
            }

            unsigned int size()
            {
                    return _size;
            }

            V get(K _key)
            {
                    _node *_node = get_node(_root, _key);
                    return _node == nullptr ? V(NULL) : _node->_val;
            }

            bool balanced()
            {
                    return balanced(_root);
            }

            bool balanced(_node *cur)
            {
                    return abs(balance_factor(cur)) <= 1;
            }

            bool contains(K _key)
            {
                    return get_node(_root, _key) != nullptr;
            }

            void set(K _key, V _val)
            {
                    _node *_node = get_node(_root, _key);
                    if (_node == nullptr)
                            return;
                    _node->_val = _val;
            }

            /* 将键为Key的结点值设置为新值newValue且从beginSearch_node开始查找 */
            void set(_node *begin, K _key, V _val)
            {
                    _node *_node = get_node(begin, _key);
                    if (_node == nullptr)
                            return;
                    _node->_val = _val;
            }

            V rm(K _key)
            {
                    _node *_node = get_node(_root, _key);
                    if (_node != nullptr) {
                            _root = rm(_root, _key);
                            return _node->_val;
                    }
                    return V(NULL);
            }

            void add(K _key, V _val)
            {
                    _root = add(_root, _key, _val);
            }

    private:
            /* 查找_key相同的节点并返回该节点指针 */
            _node *get_node(_node *_node, K _key)
            {
                    if (_node == nullptr)
                            return nullptr;
                    if (_key == _node->_key)
                            return _node;
                    else if (_key < _node->_key)
                            return get_node(_node->_l, _key);
                    else // (_key > _node._key)
                            return get_node(_node->_r, _key);
            }

            int balance_factor(_node *_node)
            { return _node == nullptr ? 0 : height(_node->_l) - height(_node->_r); }

            /* 从*_node开始寻找树中最小结点 */
            _node *min_node(_node *_node)
            { return _node->_l == nullptr ? _node : min_node(_node->_l); }

            /* AVL左旋转函数
             * 对节点_node进行向左旋转操作，返回旋转后新的根节点x
             *  _node                            x
             *  /  \                          /   \
             * T1   x      向左旋转 (y)      _node   z
             *     / \   - - - - - - - ->   / \   / \
             *   T2  z                     T1 T2 T3 T4
             *      / \
             *     T3 T4
             * */
            _node* l_rotate(_node *cur)
            {
                    _node *x = cur->_r;
                    _node *T2 = x->_l;
                    // 左旋转
                    x->_l = cur;
                    cur->_r = T2;
                    //更新结点_height, 这里必须首先更新_node->_height然后再更新x->_height。
                    cur->_height = std::max(height(cur->_l), height(cur->_r)) + 1;
                    x->_height = std::max(height(x->_l), height(x->_r)) + 1;
                    return x;
            }

            /* AVL右旋转函数
             * 对节点_node进行向右旋转操作，返回旋转后新的根节点x
             *         _node                            x
             *         / \                           /   \
             *        x   T4     向右旋转 (y)        z    _node
             *       / \       - - - - - - - ->    / \   / \
             *      z  T3                       T1  T2 T3 T4
             *     / \
             *   T1  T2
             * */
            _node* r_rotate(_node *cur)
            {
                    _node *x = cur->_l;
                    _node *T3 = x->_r;
                    x->_r = cur;
                    cur->_l = T3;
                    cur->_height = std::max(height(cur->_l), height(cur->_r)) + 1;
                    x->_height = std::max(height(x->_l), height(x->_r)) + 1;
                    return x;
            }

            /* 向以_node为根结点的BST中插入元素(_key,_val),递归算法
             * 返回插入新结点后BST的根结点
             * */
            _node *add(_node *cur, K _key, V _val)
            {
                    if (cur == nullptr) {
                            _size++;
                            return new _node(_key, _val);
                    }
                    if (_key < cur->_key)
                            cur->_l = add(cur->_l, _key, _val);
                    else if (_key > cur->_key)
                            cur->_r = add(cur->_r, _key, _val);
                    else // _key == cur->_key
                            cur->_val = _val;
                    // 更新cur->_height
                    cur->_height = 1 + std::max(height(cur->_l), height(cur->_r));
                    // 计算平衡因子
                    int factor = balance_factor(cur);
                    /* 平衡维护！这里描述的比较重就是深度_height值更大 */
                    // 当cur的左边比较重并且cur->_l的左边比较重的时候，cur进行右旋转并返回
                    if (factor > 1 && balance_factor(cur->_l) >= 0)
                            return r_rotate(cur);
                    // 当cur的右边比较重并且cur->_r的右边比较重的时候，cur进行左旋转并返回
                    if (factor < -1 && balance_factor(cur->_r) <= 0)
                            return l_rotate(cur);
                    // 当cur的左边比较重并且cur->_l的右边比较重的时候，先对cur->_l进行左旋转再对cur进行右旋转
                    //      cur                                cur                            z
                    //     /   \                             /    \                         /   \
                    //    x    T4    cur->_l左旋转        z     T4   cur进行右旋转         x    cur
                    //  /  \        ----------------->    /  \       ---------------->   / \   /  \
                    // T1  z                             x   T3                        T1 T2  T3  T4
                    //    / \                           / \
                    //   T2 T3                         T1 T2
                    if (factor > 1 && balance_factor(cur->_l) < 0) {
                            cur->_l = l_rotate(cur->_l);
                            return r_rotate(cur);
                    }
                    // 当cur的右边比较重并且cur->_r的左边比较重的时候，先对cur->_r进行右旋转再对cur进行左旋转
                    //     cur                            cur                            z
                    //    /    \                        /    \                         /   \
                    //   T1    x    cur->_r右旋转   T1    z     cur进行左旋转         cur   x
                    //        / \  ----------------->       / \  ---------------->   /  \   / \
                    //       z  T4                         T2 x                     T1  T2 T3 T4
                    //      / \                              / \
                    //     T2 T3                            T3 T4
                    if (factor < -1 && balance_factor(cur->_r) > 0) {
                            cur->_r = r_rotate(cur->_r);
                            return l_rotate(cur);
                    }
                    return cur;
            }

            /* 删除掉根结点尾cur的树中最小结点并返回删除后二叉树的根结点 */
            _node *rm_min(_node *cur)
            {
                    if (cur->_l == nullptr) {
                            _node *_r = cur->_r;
                            delete cur;
                            _size--;
                            return _r;
                    }
                    cur->_l = rm_min(cur->_l);
                    return cur;
            }

            /* 删除指定的_node结点，删除之后做旋转操作然后递归向上的把父节点做旋转操作 */
            _node *rm(_node *cur, K _key)
            {
                    if (cur == nullptr)
                            return nullptr;
                    if (cur->_key < _key) {
                            cur->_r = rm(cur->_r, _key);
                            return cur;
                    }
                    else if (cur->_key > _key) {
                            cur->_l = rm(cur->_l, _key);
                            return cur;
                    }
                    else { // cur->_key == _key
                            // 左子树为空情况，删除cur并返回cur->_r
                            if (cur->_l == nullptr) {
                                    _node *_r = cur->_r;
                                    delete cur;
                                    _size--;
                                    return _r;
                            }
                                    // 右子树为空情况
                            else if (cur->_r == nullptr) {
                                    _node *_l = cur->_l;
                                    delete cur;
                                    _size--;
                                    return _l;
                            }
                            /* 左右子树都不为空的情况 cur->_l != nullptr && cur->_r != nullptr
                             * 找到比cur大的最小结点，即cur右子树的最小结点并用这个最小结点顶替cur的位置
                             * */
                            _node *successor = _min_node(cur->_r);
                            successor->_r = rm_min(cur->_r);
                            successor->_l = cur->_l;
                            delete cur;
                            return successor;
                    }
            }
    };

}

#endif //MYCC_AVLMAP_HPP

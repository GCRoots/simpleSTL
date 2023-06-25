#include <iostream>

struct input_iterator_tag{int i=1;};
struct output_iterator_tag{int i=2;};
struct forward_iterator_tag: public input_iterator_tag{int i=3;};
struct bidirectional_iterator_tag: public forward_iterator_tag{int i=4;};
struct random_access_iterator_tag: public bidirectional_iterator_tag{int i=5;};

template<class Category, class T, class Distance=ptrdiff_t,
        class Pointer=T*, class Reference=T&>
struct iterator{
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
};

template<class Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category    iterator_category;
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
};

template<class T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};

template<class T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};

template <class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&){
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

// distance()函数组
// input_iterator_tag版
template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n(0);
    // 逐一累计距离
    for (;  first!=last ; ++first) {
        ++n;
    }
    return n;
}

// random_access_iterator_tag版
template<class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
    // 直接计算差值
    return last-first;
}

// 外露接口
template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last){
    typedef typename iterator_traits<InputIterator>::iterator_category category;
    return __distance(first, last, category());
}


// advance()函数组
// input_iterator_tag版
template<class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n,
                      input_iterator_tag){
    // 单向，逐一前进
    while (n--) i++;
}

// bidirectional_iterator_tag版
template<class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n,
                      bidirectional_iterator_tag){
    // 双向，逐一前进
    if (n >= 0)
        for (; n > 0; --n)
            ++i;
    else
        for (; n < 0; ++n)
            --i;
}

// random_access_iterator_tag版
template<class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n,
                      random_access_iterator_tag){
    // 双向，跳跃前进
    i += n;
}

// 外露接口
template<class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n){
    __advance(i, n, iterator_category(i));
}




int main() {
    std::cout << "Hello, World!" << std::endl;

    iterator<input_iterator_tag, int> iter;
    std::cout << iterator_category(iter).i << std::endl;

    int i[] = {1, 2, 3, 4, 5};
    int *a = i;

    char *str = "abcde";

    for (int j = 0; j < 5; ++j) {
        std::cout << i[j] << ' ';
    }
    std::cout << std::endl;
    int n = distance(i, i+5);

    std::cout << n << std::endl;

    std::cout << typeid(i).name() << std::endl;
    std::cout << typeid(str).name() << std::endl;


    std::cout << *str << std::endl;
    advance(str,2);
    std::cout << *str << std::endl;


    return 0;
}

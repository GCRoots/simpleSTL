/**
 * Created by 史进 on 2023/6/2.
 *
 *  该头文件包含两个函数 construct()，destroy()
 *  construct()：负责对象的构造
 *  destroy()：负责对象的析构
 *
 */
#ifndef SIMPLESTL_STL_CONSTRUCT_H
#define SIMPLESTL_STL_CONSTRUCT_H

#include <new>

#include "../type_traits.h"
#include "../iterator.h"
#include "../utility.h"

namespace simple_stl{
    template <class Tp>
    inline constexpr Tp* address_of(Tp& _p) noexcept{
        return &_p;
    }

    // construct 构造对象
    template<class Tp>
    inline void construct(Tp* _p){
        ::new ((void*)_p) Tp();
    }

    template<class T1, class T2>
    inline void construct(T1* _p, const T2& value){
        ::new ((void*)_p) T1(value);
    }

    template<class Tp, class... Args>
    inline void construct(Tp* _p, Args&&... _args){
        ::new ((void*)_p) Tp(forward<Args>(_args)...);
    }

    template<class ForwardIterator>
    inline void construct(ForwardIterator first, ForwardIterator last){
        using value_type = typename iterator_traits<ForwardIterator>::value_type;
        ForwardIterator idx = first;
        try {
            for( ; idx!=last; ++idx)
                ::new ((void*)address_of(*__idx)) value_type();
        }catch(...) {
            destroy(first, idx);
        }
    }

    // destroy 析构对象
    // 版本1：接受一个指针
    template <class Tp>
    inline void destroy(Tp* _loc){
        if (_loc != nullptr){
            _loc->~Tp();
        }
    }

    template <class ForwardIterator>
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type_s){
        for ( ; first!=last ; ++first)
            destroy(&*first);
    }

    template <class ForwardIterator>
    inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type_s){}

    template<class ForwardIterator, class Tp>
    inline void __destroy(ForwardIterator first, ForwardIterator last, Tp*){
        typedef typename __type_traits_s<Tp>::have_trivial_destructor trivial_destructor;
        __destroy_aux(first, last, trivial_destructor());
    }

    // 版本2：接受两个迭代器
    template <class ForwardIterator>
    inline void destroy(ForwardIterator first, ForwardIterator last){
        __destroy(first, last, value_type(first));
    }

    // 版本2针对char*和wchar_t*的特化版本
    inline void destroy(char*, char*){}
    inline void destroy(wchar_t*, wchar_t*){}

}   // simple_stl

#endif //SIMPLESTL_STL_CONSTRUCT_H

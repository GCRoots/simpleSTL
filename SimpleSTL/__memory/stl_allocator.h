/**
 * Created by 史进 on 2023/6/2.
 *
 * 包含一个模板类allocator，用于管理内存的分配、释放，对象的构造、析构
 *
 * ps：旧allocator，新allocator为alloc
 */
#ifndef SIMPLESTL_STL_ALLOCATOR_H
#define SIMPLESTL_STL_ALLOCATOR_H

#include "stl_construct.h"
#include "s../utility.h"

namespace simple_stl{
    template<class T>
    inline T* allocate(ptrdiff_t size, T*){
        T* tmp = static_cast<T*>(::operator new((size_t)(size*sizeof(T))));
        if (tmp == 0){
            cerr << "out of memory" << endl;
            exit(1);
        }
        return tmp;
    }

    template<class T>
    inline void deallocate(T* buffer){
        if (buffer == nullptr)
            return;
        ::operator delete(buffer);
    }


    // 模板类allocator
    template<class T>
    struct allocator{
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

        pointer allocate(){
            return simple_stl::allocate((difference_type)1, (pointer)0);
        }

        pointer allocate(size_type n){
            return simple_stl::allocate((difference_type)n, (pointer)0);
        }

        void deallocate(pointer p){
            simple_stl::deallocate(p);
        }

        void construct(pointer p){
            simple_stl::construct(p);
        }

        void construct(pointer p, const_reference value){
            simple_stl::construct(p, value);
        }

        void construct(pointer p, T&& value){
            simple_stl::construct(p, simple_stl::move(value));
        }

        template <class... Args>
        void construct(pointer p, Args&& ...args){
            simple_stl::construct(p, simple_stl::forward<Args>(args)...);
        }

        void destroy(pointer p){
            simple_stl::destroy(p);
        }

        void destroy(pointer first, pointer last){
            simple_stl::destroy(first, last);
        }

        pointer address(reference x){
            return static_cast<pointer>(&x);
        }

        const_pointer address(const_reference x){
            return static_cast<const_pointer>(&x);
        }
    };






}   // simple_stl

#endif //SIMPLESTL_STL_ALLOCATOR_H

#ifndef SHAREDD_PTR
#define SHAREDD_PTR

#include "unique_ptr.h"

template <typename T>
class SharedPtr {
private:
    UniquePtr<T> *_p = nullptr;
    int *use_cnt;

public:
    SharedPtr() = default;
    SharedPtr(T value): _p(new UniquePtr(value)), use_cnt(new int{1}) {}
    SharedPtr(T *pointer): _p(new UniquePtr(pointer)), use_cnt(new int{1}) {}
    SharedPtr(SharedPtr &other) {
        _p = other._p;
        *other.use_cnt += 1;
        use_cnt = (other.use_cnt);
    }

    T *get() { return (_p) ? _p->get() : nullptr; }
    void reset() {
        delete _p;
        _p = nullptr;
    }
    void reset(T *other) {
        delete _p;
        use_cnt = 0;
        _p = other;
    }
    T *release() {
        T *tmp = _p;
        _p = nullptr;
        return tmp;
    }
    int use_count() {return *use_cnt;}

    operator bool() const { return _p != nullptr; }
    T &operator*() {
        return **_p;
    }
    T *operator->() {
        return _p;
    }
    T &operator=(T *pointer) {
        _p = pointer;
        return *this;
    }
};

template<typename T>
SharedPtr<T> make_shared(T value) {
    return SharedPtr<T>(value);
}

template<typename T>
SharedPtr<T> make_shared(T *pointer) {
    return SharedPtr<T>(pointer);
}

#endif //SHAREDD_PTR

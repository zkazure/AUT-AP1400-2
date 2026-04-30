#ifndef SHAREDD_PTR
#define SHAREDD_PTR

#include "unique_ptr.h"

template <typename T>
class SharedPtr {
private:
    T *_p = nullptr;
    int *use_cnt;

public:
    SharedPtr() : _p(nullptr), use_cnt(nullptr) {}
    SharedPtr(T value): _p(new T(value)), use_cnt(new int{1}) {}
    SharedPtr(T *pointer): _p(pointer), use_cnt(new int{1}) {}
    SharedPtr(SharedPtr &other) {
        _p = other._p;
        use_cnt = other.use_cnt;
        *use_cnt += 1;
    }
    ~SharedPtr() {
        if (use_cnt) {
            *use_cnt -= 1;
            if (*use_cnt == 0) {
                delete _p;
                delete use_cnt;
                _p = nullptr;
                use_cnt = nullptr;
            }
        }
    }

    T *get() { return _p; }
    void reset() {
        delete _p;
        _p = nullptr;
        if (use_cnt) *use_cnt -= 1;
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
    int use_count() {
        if (use_cnt) {
            return *use_cnt;
        }
        return 0;
    }

    operator bool() const { return _p != nullptr; }
    T &operator*() {
        return *_p;
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

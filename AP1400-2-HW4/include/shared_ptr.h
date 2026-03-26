#ifndef SHAREDD_PTR
#define SHAREDD_PTR

template <typename T>
class SharedPtr {
private:
    T* _p;

public:
    SharedPtr() = default;
    SharedPtr(T value) { _p = new T(value); }
    SharedPtr(T* pointer) { _p = pointer; }

    T* get() { return _p; }
    void reset() {
        delete _p;
        _p = nullptr;
    }
    void reset(T* other) {
        delete _p;
        _p = other;
    }
    T* release() {
        T *tmp = _p;
        _p = nullptr;
        return tmp;
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
SharedPtr<T> make_shared(T* pointer) {
    return SharedPtr<T>(pointer);
}


#endif //SHAREDD_PTR

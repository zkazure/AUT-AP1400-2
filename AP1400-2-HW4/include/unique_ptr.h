#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
private:
    T* _p;

public:
    UniquePtr() = default;
    UniquePtr(T value) { _p = new T(value); }
    UniquePtr(T* pointer) { _p = pointer; }

    T* get() { return _p; }
    void reset() {
        delete _p;
        _p = nullptr;
    }
    void reset(T* other) {
        delete _p;
        _p = other;
    }

    operator bool() const { return _p != nullptr; }
    T &operator*() {
        return *_p;
    }
    T *operator->() {
        return _p;
    }
};

template<typename T>
UniquePtr<T> make_unique(T value) {
    return UniquePtr<T>(value);
}

template<typename T>
UniquePtr<T> make_unique(T* pointer) {
    return UniquePtr<T>(pointer);
}

#endif //UNIQUE_PTR

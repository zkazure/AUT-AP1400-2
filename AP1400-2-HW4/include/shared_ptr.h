#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class UniquePtr {
private:
    T* _p;

public:
    UniquePtr() = default;
    UniquePtr(T value) { _p = new T(value); };
    UniquePtr(T* pointer) { _p = pointer; };

    T* get() { return _p; };
    T &operator*() {
        return *(this->get());
    }
    T *operator->() {
        return this->get();
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


#endif //SHARED_PTR

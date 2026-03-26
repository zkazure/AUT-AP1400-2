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
};


#endif //SHARED_PTR

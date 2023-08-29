#include <utility>

//auto_ptr1
template<class T>
class my_auto_ptr{
    private:
        T* ptr_;
        bool owner_;

    public:
        my_auto_ptr(T* ptr):ptr_(ptr), owner_(true){}
        my_auto_ptr(my_auto_ptr<T>& ap); //拷贝构造函数
        my_auto_ptr<T>& operator=(my_auto_ptr<T>& ap); //重载赋值运算符
        T* operator->();
        T* operator*();
        ~my_auto_ptr();
};

template<class T>
my_auto_ptr<T>::my_auto_ptr(my_auto_ptr<T>& ap):ptr_(ap.ptr) {
    ap.owner_ = false;
}

template<class T>
my_auto_ptr<T>& my_auto_ptr<T>::operator=(my_auto_ptr<T>& ap) {
    if(this != &ap) {
        delete this->ptr_;
        this->ptr_ = ap.ptr_;
        this->owner_ = true;
        ap.owner_ = false;
    }
    return *this;
}

template<class T>
T* my_auto_ptr<T>::operator->() {
    return this->ptr_;
}

template<class T>
T* my_auto_ptr<T>::operator*() {
    return this->ptr_;
}

template<class T>
my_auto_ptr<T>::~my_auto_ptr() {
    if(this->ptr_) {
        this->owner_ = false;
        delete this->ptr_;
    }
}
//此种auto_ptr存在的隐患在于，如果拷贝出来的对象比原来的对象先出作用域或调用析构函数，则原来的对象_owner虽然为false，
//但却在访问一块已经被释放的空间，造成指针悬空的问题

//auto_ptr2
template<class T>
class my_auto_ptr2
{
private:
    /* data */
    T* ptr_;
public:
    my_auto_ptr2(T* ptr) : ptr_(ptr);
    my_auto_ptr2(my_auto_ptr2<T>& ap);
    ~my_auto_ptr2();
    my_auto_ptr2<T>& operator=(my_auto_ptr2<T>& ap);
    T* operator->();
    T* operator*();
};

template<class T>
my_auto_ptr2<T>::my_auto_ptr2(my_auto_ptr2<T>& ap):ptr_(ap.ptr_) {
    ap.ptr = nullptr;
}

template<class T>
my_auto_ptr2<T>& my_auto_ptr2<T>::operator=(my_auto_ptr2<T>& ap) {
    if(this != ap) {
        delete this->ptr_;
        this->ptr_ = ap.ptr_;
        ap.ptr_ = nullptr;
    }
    return *this;
}
//此种auto_ptr实现方式是通过赋值时直接将被拷贝对象指针置为nullptr解决指针悬空问题，但是仍可能存在对空指针解引用或者取地址
//的操作导致程序崩溃

//unique_ptr
template<class T>
class unique_ptr{
    private:
        T* ptr_ = nullptr;
    
    public:
        unique_ptr() : ptr_(nullptr) {}
        
        explicit unique_ptr(T* ptr) : ptr_(std::move(ptr)) {}
        //explicit构造函数是防止隐式转换，即不允许写成unique_ptr<T> tempPtr = T
        //std::move()是将对象的所有权从一个对象转移到另一个对象，只是转移而非内存拷贝从而提高效率

        unique_ptr(const unique_ptr<T>&) noexcept = delete;
        unique_ptr& operator = (const unique_ptr<T>&) noexcept = delete;

        ~unique_ptr() noexcept {
            delete ptr_;
        }
        
        unique_ptr(unique_ptr&& move) noexcept{
            move.swap(*this)
        }

        void swap(unique_ptr<T>& resource_ptr) noexcept{
            std::swap(ptr_, resource_ptr);
        }

        unique_ptr& operator = (unique_ptr<T>&& move) noexcept{
            move.swap(*this);
            return *this;
        }

        T* release() noexcept{
            return std::exchange(ptr_, nullptr);
        }
        
        void reset(T* ptr) {
            if(ptr == nullptr) {
                cout << "invalid" << endl;
            }
            delete ptr_;
            ptr_ = nullptr;
            std::swap(ptr_, ptr);
        }
};
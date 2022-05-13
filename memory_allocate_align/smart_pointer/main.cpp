// #include <memory>

//https://blog.csdn.net/luanfenlian0992/article/details/118771472#:~:text=%E4%BB%8B%E7%BB%8D%E4%B8%8B%20valgrind%20%E3%80%82-,1.9.%20%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88%E6%9C%89%E5%93%AA%E5%87%A0%E7%A7%8D%EF%BC%9F%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88%E7%9A%84%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86%EF%BC%9F,-%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88%E6%98%AF


template <typename T>
class SmartPtr{
private:
    T *_ptr;
    size_t *_count;

public:
    SmartPtr(T *ptr =nullptr) : _ptr(ptr){
        if(_ptr){
            _count = new size_t(1);
        }
        else{
            _count = new size_t(0);
        }
    }

    ~SmartPtr(){
        (*this->_count)--;
        if(*this->_count==0){
            delete this->_ptr;
            delete this->_count;
        }
    }

    SmartPtr(const SmartPtr &ptr){//拷贝构造：计数+1
        if(this!= &ptr){
            this->_ptr = ptr._ptr;
            this->_count = ptr._count;
            (*this->_count)++;
        }
    }

    SmartPtr &operator=(const SmartPtr &ptr){//赋值运算符重载
        if(this->_ptr == ptr._ptr){
            return *this;
        }

        if(this->_ptr){//将当前的ptr指向的原来的空间计数-1
            (*this->_count)--;
            if(*this->_count == 0){
                delete this->_ptr;
                delete this->_count;
            }
        }

        this->_ptr=ptr._ptr;
        this->_count=ptr._count;
        (*this->_count)++;//此时ptr指向了新赋值的空间，该空间的计数+1
        return *this;
    }

    T &operator*(){
        assert(this->_ptr==nullptr);
        return *(this->_ptr);
    }

    T *operator->(){
        assert(this->_ptr==nullptr);
        return this->_ptr;
    }

    size_t use_count(){
        return *this->_count;
    }

};
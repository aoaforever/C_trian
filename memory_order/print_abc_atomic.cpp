#include <iostream>
#include <thread>
#include <atomic>

/*
https://github.com/szza/LearningNote/blob/master/1.%E9%9D%A2%E8%AF%95%E6%80%BB%E7%BB%93/7_%E7%BA%BF%E7%A8%8B.md#:~:text=%E5%8E%9F%E5%AD%90%E6%93%8D%E4%BD%9C%E4%BD%BF%E7%94%A8%E3%80%82-,%E4%B8%89%E4%B8%AA%E7%BA%BF%E7%A8%8B%E6%8C%89%E7%85%A7%E9%A1%BA%E5%BA%8F%E6%89%93%E5%8D%B0abc,-%23include%20%3C

*/
// 无锁的方式实现
class Solution { 
public:
    enum class State {A, B, C};

    Solution() { 
        state_.store(State::A, std::memory_order_release);
        int cnt=10;
        std::thread([this, cnt]()mutable
                    { 
                        while(cnt--) 
                        { 
                            this->printB();
                        }
                    }).detach();

        std::thread([this, cnt]()mutable
                    { 
                        while(cnt--) 
                        { 
                            this->printC();
                        }
                    }).detach();
        while(cnt--) 
        { 
            this->printA();
        }
    }

    ~Solution() 
    { 
        std::cout<<std::endl;
    }

    void printA() { 
        while(state_.load(std::memory_order_acquire) != State::A);
        std::cout<<"a";
        state_.store(State::B, std::memory_order_release);
    }

    void printB() { 
        while(state_.load(std::memory_order_acquire) != State::B);
        std::cout<<"b";
        state_.store(State::C, std::memory_order_release);
    }

    void printC() { 
        while(state_.load(std::memory_order_acquire) != State::C);
        std::cout<<"c";
        state_.store(State::A, std::memory_order_release);
    }
    private:
        std::atomic<State> state_;
    };

    int main(int argc, char const *argv[])
    {
        Solution();
        return 0;
    }
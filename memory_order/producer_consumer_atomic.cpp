#include <iostream>
#include <thread>
#include <atomic>
#include <list>
#include <iostream>
using namespace std;


class Solution {
public:
  Solution()
  : state_{State::READ},
    trd_{[this]{
        this->customer();
            }
        }
    { 
        trd_.detach();
        producer(2);
    }

    void producer(int val)
    {
      while(state_.load(std::memory_order_acquire) == State::READ);

      task_.push_back(val);
      state_.store(State::READ, std::memory_order_release);
    }

    void customer() 
    { 
      while(state_.load(std::memory_order_acquire) == State::WRITE);
      if(!task_.empty()) { 
        int val = task_.front();
        cout<<val<<endl;
        task_.pop_front();
      }

      state_.store(State::WRITE, std::memory_order_release);
    }
private:
  enum class State {READ, WRITE};

  std::atomic<State> state_;
  std::thread        trd_;
  std::list<int>     task_;
};

int main(){
    Solution s;
    s.producer(2);
    s.producer(3);
    s.producer(1);
    return 0;
}
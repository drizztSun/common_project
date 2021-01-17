#include <vector>
#include <thread>
#include <mutex>

using std::unique_lock;
using std::mutex;
using std::thread;
using std::vector;
using std::condition_variable;

class ThreadPool {


    vector<thread> _thread_pool;
    condition_variable conv;
    mutex _queue_mutex;

public:


    void Inifinite_loopp_func(mutex& queue_mu) {

        while (true) {

            {
                unique_lock<mutex> lock(queue_mu);

                conv.wait(lock, [] {return ! Queue.empty() || terminate_pool});
                auto job = Queue.front();
                Queue.pop();
            }

            job();
        }

    }

    void add_job(function<void()> new_job) {

        {
            unique_lock<mutex> lock(_queue_mutex);
            Queue.push(new_job);
        }

        conv.notify_one();

    }

    void start(int threads_amount) {


        int Num_Threads =  thread::hardware_concurrency();

        for (int i = 0; i < Num_Threads; i++) {
            _thread_pool.push_back(thread(Inifinite_loopp_func));
        }




    }


    
}

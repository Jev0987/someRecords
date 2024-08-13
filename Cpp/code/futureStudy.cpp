#include <iostream>
#include <future>

int main() {
    std::future<int> result = std::async([](){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;
    });

    std::cout << "the future result is : " << result.get() << std::endl;
    std::cout << "the future status is : " << result.valid() << std::endl;

    try {
        result.wait();
    }   catch(...) {
        std::cout << "get error" << std::endl;
    }
}
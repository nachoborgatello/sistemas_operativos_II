#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#define buff_max 25
#define mod %

struct item {
  // different member of the produced data 
  // or consumed data    
  // ---------
};

// An array is needed for holding the items. 
// This is the shared place which will be  
// access by both process   
// item shared_buff[buff_max];

// Two variables which will keep track of 
// the indexes of the items produced by producer 
// and consumer The free index points to 
// the next free index. The full index points to 
// the first full index. 
std::atomic<int> free_index(0);
std::atomic<int> full_index(0);
std::mutex mtx;

void producer() {
  item new_item;
  while (true) {
    // Produce the item
    // ...
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // Add the item to the buffer
    while (((free_index + 1) mod buff_max) == full_index) {
      // Buffer is full, wait for consumer
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mtx.lock();
    // Add the item to the buffer
    // shared_buff[free_index] = new_item;
    free_index = (free_index + 1) mod buff_max;
    mtx.unlock();
  }
}

void consumer() {
  item consumed_item;
  while (true) {
    while (free_index == full_index) {
      // Buffer is empty, wait for producer
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mtx.lock();
    // Consume the item from the buffer
    // consumed_item = shared_buff[full_index];
    full_index = (full_index + 1) mod buff_max;
    mtx.unlock();
    // Consume the item
    // ...
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int main() {
  // Create producer and consumer threads
  std::vector<std::thread> threads;
  threads.emplace_back(producer);
  threads.emplace_back(consumer);

  // Wait for threads to finish
  for (auto& thread : threads) {
    thread.join();
  }

  return 0;
}
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <vector>
#include <chrono>

std::map<std::string, int> myMap;
std::vector<std::thread> threadList;

std::thread createThread(const std::string &key)
{
    return std::thread([&]() {
        auto const findIter = myMap.find(key);

        if (findIter != myMap.end())
        {
            int count = myMap[key];
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            myMap[key] = count + 1;
        }
        else
        {
            myMap.emplace(key, 1);
        }
    });
}

int main(int argc, char *argv[])
{
    int maxThreads = 1000;
    int maxThreadsHalf = (maxThreads / 2);

    for (int x = 0; x < maxThreadsHalf; x++)
    {
        threadList.push_back(createThread("potato"));
        threadList.push_back(createThread("apple"));
    }

    for (int x = 0; x < maxThreads; x++)
    {
        threadList[x].join();
    }

    std::cout << "> Result: apple = " << myMap["apple"] << ", potato = " << myMap["potato"] << std::endl;

    return EXIT_SUCCESS;
}

// STD
#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define USE_FILES

#ifdef USE_FILES
#define TASK "../tests/31"
#endif

int main(int argc, char** argv)
{
    std::cout << "Task A" << std::endl;

#ifdef USE_FILES
    std::freopen(TASK, "r", stdin);
    std::freopen(TASK ".my.out", "w", stdout);
#endif

    int N, K;
    std::cin >> N >> K;
//    std::cout << "N, K : ";
//    std::cout << N << " ";
//    std::cout << K << " ";
//    std::cout << std::endl;

    std::vector<int> A(N);
    std::multiset <int> buffer;
//    std::cout << "A : ";
    for (int i=0;i<A.size();i++)
    {
        std::cin >> A[i];
        buffer.insert(A[i]);
//        std::cout << A[i] << " ";
    }
//    std::cout << std::endl;


    // Sort A array: complexity O(N*logN)
    std::sort(A.begin(), A.end());
//    std::cout << "A sorted : ";
//    for (int i=0;i<A.size();i++)
//    {
//        std::cout << A[i] << " ";
//    }
//    std::cout << std::endl;

    // Remove all dublicates : complexity O(N)
    A.resize(std::unique(A.begin(), A.end()) - A.begin());
//    std::cout << "A unique : ";
//    for (int i=0;i<A.size();i++)
//    {
//        std::cout << A[i] << " ";
//    }
//    std::cout << std::endl;

    int M = A.size();

    //
//    std::cout << "Output : ";
    for (int i=0; i<std::min(M,K); i++)
    {
        std::cout << A[i] << " ";
        buffer.erase(buffer.find(A[i]));
    }

    for (int i=0; i<K-M; i++)
    {
        std::cout << *buffer.begin() << " ";
        buffer.erase(buffer.begin());
    }

    return 0;
}

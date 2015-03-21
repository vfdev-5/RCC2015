/*!

Грю решил устроить торжественный парад. Неотъемлемая часть парада — построение его могучей армии миньонов.

Парад будет проходить на Центральной площади, которая имеет форму квадрата. Длина и ширина площади — n метров.
Она разбита на ячейки по одному метру в длину и ширину, таким образом, на ней находится n2 ячеек.
Иначе говоря, Центральная площадь представляет собой матрицу n × n.

Грю раздал каждому миньону из своей армии по цветной маечке, на которой написано простое число. На некоторых маечках могут быть написаны одинаковые числа.
Теперь дело за миньонами — они должны построиться так, как хочет Грю. При построении каждую ячейку площади занимает ровно один миньон.
Также есть дополнительные требования к построению. Первое из них заключается в том, что в параде должны участвовать миньоны с ровно k различными простыми числами на маечках.
Второе требование состоит в том, что произведение чисел на маечках в каждой строке и в каждом столбце должно иметь одинаковое количество делителей.
Также учтите, что в распоряжении Грю имеются только маечки с простыми числами, не превосходящими 10^7.

Помогите провести построение, удовлетворяющее всем требованиям или выясните, что это сделать невозможно.
Формат входных данных

На ввод подается одна строка, содержащая два целых числа k и n (1 ≤ k ≤ 10^9, 1 ≤ n ≤ 1000) — количество требуемых различных простых чисел и размер площади.
Формат выходных данных

Выведите матрицу n × n, состоящую из простых чисел, не превосходящих 10^7, для которой выполняются все требования, либо −1, если построение выполнить невозможно.

 */
// STD
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define USE_FILES
//#define CAN_CHECK

#ifdef USE_FILES
#define TASK "../tests/51"
#endif

#ifdef CAN_CHECK
#define SOL TASK ".a"
#endif


/*!
 * 1) Fundamental theorem of arithmetic
 * - Any number can be decompsed into a product of prime numbers
 * - n = p1 * p2 * ... * pN
 *
 *
 * 2) two numbers (n1, n2) have same numbers of dividors
 *      if decompositions n1 = p11 * p12 * ... * p1N1 and
 *      n2 = p21 * p22 * ... * p2N2 have same number of
 *      identical repeated elements <=>
 *
 *      n1 = (p11)^a1 * (p12)^a2 * ... * (p1N)^aN
 *      n2 = (p21)^b1 * (p22)^b2 * ... * (p2N)^bN
 *
 *      number of unique prime numbers is equal
 *
 * 3) Theorem : Number of prime numbers below a given number
 *
 *  The prime counting function π(n) is defined as the number of primes not greater than n.
 *
 *  π(n) ~= n/ln(n)
 *
 *  π(11) = 5  <-> 2,3,5,7,11
 *
 */

const int K_LIMIT = 620421;
const int PRIME_MAX = 10000000;
const int PRIME_MAX2 = PRIME_MAX * PRIME_MAX;

void generatePrimes(std::vector<int> * storage)
{
    std::vector<bool> sieve(PRIME_MAX2, true);

    for (unsigned int value=2; value<PRIME_MAX; value++)
    {
        if (sieve[value])
        {
            storage->push_back(value);
            for (unsigned int j=value*value; j<PRIME_MAX; j+=value)
            {
                sieve[j] = false;
            }
        }
    }
}


int main(int argc, char** argv)
{

    std::cout << "Task C" << std::endl;

#ifdef USE_FILES
    std::freopen(TASK, "r", stdin);
#ifndef _DEBUG
    std::freopen(TASK ".my.out", "w", stdout);
#endif
#endif

    int K, N;
    std::cin >> K >> N;

    // Condition : max of primes should not be larger than 1e7
    if (K > K_LIMIT)
    {
        std::cout << -1;
        return 0;
    }


    // 1st condition:
    if (K > N*N)
    {
        std::cout << -1;
        return -1;
    }

    std::vector<int> primes;
    generatePrimes(&primes);


    if (K == N*N)
    {
        for (unsigned int i=0;i<N;i++)
        {
            for (unsigned int j=0;j<N;j++)
            {
                std::cout << primes[i*N + j] << " ";
            }
            std::cout << std::endl;
        }
    }
    else
    {
        // K < N*N :
        std::vector< int > line(N,-1);
        for (int i=0;i<N;i++)
        {
            int index = i % K;
            line[i] = primes[index];
        }

        for (unsigned int i=0;i<N;i++)
        {
            for (unsigned int j=0;j<N;j++)
            {
                int index = (j + i) % K;
                std::cout << line[index] << " ";
            }
            std::cout << std::endl;
        }
    }


#ifdef CAN_CHECK

//    int goodResult;
//    std::freopen(SOL, "r", stdin);
//    std::cin >> goodResult;
//    if (goodResult == result)
//    {
//        return 0;
//    }
//    else
//    {
//        std::cerr << std::endl << "!!! Answer is wrong !!!" << std::endl;
//        return 1;
//    }


#endif

    return 0;
}

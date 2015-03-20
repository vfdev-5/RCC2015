/*!

Как всем известно, миньоны очень любят бананы, поэтому Грю постоянно сталкивается с необходимостью их закупать. Так как миньонов очень много, он хочет знать количество бананов, которое он закупит.

Он покупает бананы в интернет-магазинах с доставкой на дом. У данного способа есть один спецэффект: если оплачивать коробку бананов в момент отправки, то ее стоимость будет C1, а если при получении, то C2. Грю взломал сервера всех интернет-магазинов по продаже бананов и узнал данные о продажах в ближайшее время. Теперь он знает про каждую коробку бананов, когда ее смогут отправить и когда она придет к нему. Также у него есть выписка из банка, в которой написано, когда и сколько ему поступит денег на счет.

Грю очень нетерпеливый, поэтому если он может купить коробку бананов в момент отправки (у него есть деньги на счету и их хватает для покупки), то он покупает ее. В противном случае он вызывает курьера, и если в момент доставки Грю может выкупить, то он выкупает посылку, а если нет, то курьер уходит ни с чем.

Так как помимо миньонов Грю растит еще трех девочек, у него не остается времени на расчеты. Он просит вас написать программу, которая по имеющимся у него данным вычислит, какое количество коробок бананов он в итоге купит.
Формат входных данных

В первой строке содержатся два целых числа C1 и C2 (1 ≤ C1 ≤ C2 ≤ 1000) — стоимости коробки бананов в момент отправки и в момент получения. Во второй строке находится одно целое число n (1 ≤ n ≤ 100 000) — количество платежей, поступающих на счет Грю. В следющих n строках записаны пары чисел ai, ti (1 ≤ ai ≤ 1000, 1 ≤ ti ≤ 109) — количество поступающих денег и время, когда они поступят. В следующей строке находится число m (1 ≤ m ≤ 100 000) — количество коробок бананов, которые будут продаваться в ближайшее время. В следующих m строках записаны пары чисел li, ri (1 ≤ li ≤ ri ≤ 109) — время отправки и время получения каждой коробки бананов.

Для любых i ≠ j выполняется li ≠ lj, li ≠ rj, ri ≠ rj.
Формат выходных данных

В единственной строке выходного файла количество коробок бананов, которые Грю сможет купить.

 */
// STD
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

#define USE_FILES
#define CAN_CHECK

#ifdef USE_FILES
#define TASK "../tests/67"
#endif

#ifdef CAN_CHECK
#define SOL TASK ".a"
#endif

struct Transaction
{
    int time;
    int amount;
    bool valid;
    Transaction * pairedTransaction;

    Transaction(int t=-1, int a=0) :
        time(t),
        amount(a),
        valid(true),
        pairedTransaction(0)
    {
    }
};

bool compareLess(const Transaction * a, const Transaction * b)
{
    if (a->time < b->time)
        return true;
    else if (a->time == b->time)
        return a->amount > b->amount;
    else
        return false;
}


int main(int argc, char** argv)
{

    std::cout << "Task B" << std::endl;

#ifdef USE_FILES
    std::freopen(TASK, "r", stdin);
#ifndef _DEBUG
    std::freopen(TASK ".my.out", "w", stdout);
#endif
#endif

    int C1, C2;
    std::cin >> C1 >> C2;

    int nbOfTransactions;
    std::cin >> nbOfTransactions;

    std::vector<Transaction*> transactions(nbOfTransactions, 0);

    // store transactions info:
    for (int i=0; i<nbOfTransactions; i++)
    {
        int amount, time;
        std::cin >> amount >> time;
        transactions[i] = new Transaction(time, amount);
    }

    // store sells info:
    int nbOfSells;
    std::cin >> nbOfSells;
    transactions.resize(nbOfTransactions+2*nbOfSells, 0);

    for (int i=0; i<nbOfSells; i++)
    {
        int sellTime1, sellTime2;
        std::cin >> sellTime1 >> sellTime2;
        transactions[nbOfTransactions + 2*i] = new Transaction(sellTime1, -C1);
        transactions[nbOfTransactions + 2*i+1] = new Transaction(sellTime2, -C2);

        transactions[nbOfTransactions + 2*i]->pairedTransaction = transactions[nbOfTransactions + 2*i+1];
    }

    // sort transactions by time:
    // elements in vector are swaped when sorted
    std::sort(transactions.begin(), transactions.end(), &compareLess);

    // Loop on time:
    int result = 0;
    double account=0.0;

    std::vector<Transaction*>::iterator it = transactions.begin();
    for (;it!=transactions.end();++it)
    {
        Transaction * t = *it;
//        std::cout << "Time : " << t->time << ", Account : " << account << std::endl;
        // check if transaction is not canceled:
        if (!t->valid)
        {
//            std::cout << "Transaction is not valid" << std::endl;
            delete t;
            continue;
        }

        if (t->amount > 0)
        {
            // fill account :
//            std::cout << "Fill account" << std::endl;
            account += t->amount;
        }
        else
        {
            // check if can buy
//            std::cout << "Check if can buy" << std::endl;
            if (account + t->amount >= 0)
            {
//                std::cout << "Buy at price : " << -t->amount << std::endl;
                account += t->amount;
                result++;

                if (t->amount == -C1)
                {
//                    std::cout << "Cancel paired transaction" << std::endl;
                    // cancel paired transaction
                    t->pairedTransaction->valid = false;
                }
            }
        }
        delete t;
    }

    // Output
    std::cout << result;

#ifdef CAN_CHECK

    int goodResult;
    std::freopen(SOL, "r", stdin);
    std::cin >> goodResult;
    if (goodResult == result)
    {
        std::cerr << std::endl << "OK" << std::endl;
        return 0;
    }
    else
    {
        std::cerr << std::endl << "!!! Answer is wrong !!!" << std::endl;
        return 1;
    }


#endif

    return 0;
}

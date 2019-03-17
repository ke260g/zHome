// container adaptor
#include<stack>
#include<queue>
#include<string>
#include<iostream>
#include<deque>
#include<list>

using namespace std;
int container_adaptor(void) {
    std::stack<std::string, std::list<std::string>> stk;
    stk.push("first in");
    stk.push("second in");
    cout << stk.size() << " # " << stk.top() << endl;
    stk.pop();
    cout << stk.size() << " # " << stk.top() << endl;

    std::queue<std::string, std::list<std::string>> que;
    que.push("first soul");
    que.push("second soul");
    que.push("third soul");
    que.push("fourth soul");
    que.front() = "modified first";
    cout << que.front() << " << >> " << que.back() << endl;
    que.pop();
    cout << que.front() << " << >> " << que.back() << endl;

    //std::vector<int> svi = { 10, 20, 40, 60 };
    //priority_queue<int, std::vector<int>> pq(svi.begin(), svi.end());
    std::deque<int> dqI = { 10, 20, 40, 60 };
    priority_queue<int, std::deque<int>> pq(dqI.begin(), dqI.end());
    cout << pq.top() << endl;
    pq.push(45);
    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top() << endl;
    cout << "-------" << endl;
}

int main( int argc, char **argv ) {
    container_adaptor();
    return 0;
}

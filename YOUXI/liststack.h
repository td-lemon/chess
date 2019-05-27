#ifndef LISTSTACK_H
#define LISTSTACK_H
class ListStack;  //提前声明，友元函数需要
class ListNode
{
    friend class ListStack;
public:
    ListNode(int value):data(value), next(0) {}
private:
    int data;
    ListNode *next;
};

class ListStack
{
public:
    ListStack():top(0) {}  //构造函数
    ListStack(const ListStack&);  //拷贝构造函数
    ~ListStack();  //析构函数
    ListStack& operator=(const ListStack&);  //赋值函数
    bool isempty()const;  //判空
    void push(int);  //入栈
    bool pop();  //出栈
    bool get_top(int&)const;  //取栈顶元素
protected:
private:
    ListNode *top;
    void copy(const ListStack&);  //拷贝功能函数
    void clear();  //清空函数，实现析构
};

#endif // LISTSTACK_H

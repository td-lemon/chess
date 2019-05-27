#include "liststack.h"

// -------------------- //
//拷贝功能函数
void ListStack::copy(const ListStack& other)
{
    top = 0;
    ListNode *tmp = other.top;
    ListNode *prenode;
    while (tmp)
    {
        ListNode *newnode = new ListNode(tmp->data);
        if (top == 0)
        {
            top = newnode;
        }
        else
        {
            prenode->next = newnode;
        }
        prenode = newnode;
        tmp = tmp->next;
    }
}

//清空栈函数
void ListStack::clear()
{
    while (top)
    {
        ListNode *delnode = top;
        top = top->next;
        delete delnode;
    }
}

//拷贝构造函数
ListStack::ListStack(const ListStack& other)
{
    copy(other);
}

//析构函数
ListStack::~ListStack()
{
    clear();
}

//赋值函数
ListStack& ListStack::operator=(const ListStack& other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

//判栈空函数
bool ListStack::isempty()const
{
    return top == 0;
}

//入栈函数
void ListStack::push(int value)
{
    ListNode *newnode = new ListNode(value);
    newnode->next = top;
    top = newnode;
}

//出栈函数
bool ListStack::pop()
{
    if (isempty())
    {
        return false;
    }
    ListNode *delnode = top;
    top = top->next;
    delete delnode;
    return true;
}

//取栈顶元素
bool ListStack::get_top(int &value)const
{
    if (isempty())
    {
        return false;
    }
    value = top->data;
    return true;
}


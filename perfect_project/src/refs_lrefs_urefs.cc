#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <memory>
#include <algorithm>

//? non_type_deduction
//the argument it's an *rref* since the type is known (no type deduction)
void fct(int &&arg)
{
    //*outside this function, arg is an rvalue, but here, since it has a name, it becomes an lvalue(name), so the move contructor casts it back to an rvalue
    auto stored_var = std::move(arg); //move=static_cast<rvalue>(lvalue)
    std::cout << "NON-TYPE-DEDUCTION: " << stored_var << "\n";
}

//? TYPE DEDUCTION
//the argument of the expression is a *uref* since it has type deduction
template <typename T>
void fct(T &&arg)
{
    //*outside the function: since the type is T, arg can bind to both lvaues and rvalues (uref)
    //inside, arg is again an lvalue
    auto stored_var = std::forward<T>(arg); //casts it back to an rvalue
    std::cout << "TYPE-DEDUCTION: " << stored_var << "\n";
}

int main()
{
    int x = 2;
    fct(static_cast<int &&> (x));//solve compiler complaint on passing lvalue to a function that only takes rvalue refs.
    fct(2);//solve compiler complaint on passing lvalue to a function that only takes rvalue refs.
    fct<int>(2);//solve compiler complaint on passing lvalue to a function that only takes rvalue refs.
}
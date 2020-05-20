#include "../include/perfectf.hh"

inline void line() { std::cout << '\n'; }

perfect_f::Perfect_F::Perfect_F()
{
    std::cout << "1";
    line();
}

perfect_f::Perfect_F::~Perfect_F()
{
    std::cout << "0";
    line();
}

//perfect forwarding tutorial
// # based on a YT video https://www.youtube.com/watch?v=cRjBj7-VjY4

struct S
{
    S() = default;
    S(int i, bool b, float f) : m_i(i), m_b(b), m_f(f) {}
    S(int i) : m_i(i) {}
    S(int i, bool b, float f, std::vector<int> const &vec)
        : m_i(i), m_b(b), m_f(f), m_v(vec) {}
    S(int i, bool b, float f, std::vector<int> &&vec)
        : m_i(i), m_b(b), m_f(f), m_v(std::move(vec)) {}
    int m_i;
    bool m_b;
    float m_f;
    std::vector<int> m_v;
    //expensive to create
};

struct Perfect
{

    //using a variadic template
    //creating a special add function for implementing perfect forwarding and pass multiple arguments
    template <typename... Args>
    void AddS(Args &&... args) //forwarding reference (universal reference)
    {
        v1.emplace_back(std::forward<Args>(args)...); //perfect forwarding -> //* it keeps the argument type
    }
    // void AddS(S const &s)
    // {
    //     v1.emplace_back(s);
    // }

private:
    std::vector<S> v1;
};

int main()
{
    // // auto x = std::make_unique<perfect_f::Perfect_F>();
    // std::vector<S> v1;
    // {
    //     // std::vector<int> v2 = {1, 2, 3};
    //     // v1 = std::move(v2); //steal resources from v2 since it is a temp

    //     S v2(1, true, 2.0);
    //     v1.emplace_back(v2); //make a copy of S v2
    //     //! a better alternative would be to move
    //     v1.emplace_back(std::move(v2));    //move v2 (less expensive)
    //     v1.emplace_back(S(1, false, 2.0)); // move a tmp object

    //     //perfect forwarding is this:
    //     v1.emplace_back(1, false, 2.0); // move a tmp object //* also correct
    //     //! new creates on the heap

    Perfect v2;

    S v1(1, true, 0.0);

    v2.AddS(2, true, 0.1); // this is going to copy construct (use resources) //! if one uses push_back
    //? if AddS uses emplace_back in the constructors, then no copying takes place

    //the new implementation of AddS uses variadic templates.
    //by changing the argument type, it is possible to avoid the default constructor and the move constructor
    //* only use perfect forwarding in this function
    //takes the types as lvalues and rvalues //* this is an universal value reference -> keeps the reference in the initial type

    std::vector<int> test = {1, 2, 3, 4};
    v2.AddS(1, false, 1.0, test); //this will default to the first constructor because "test" is an l-value
    v2.AddS(1, false, 1.0, std::move(test)); //it defaults in the second constructor
}

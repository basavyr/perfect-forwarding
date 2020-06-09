- This is a document which covers the topic of **Perfect Forwarding in C++**
- This is based on a YT video which can be seen [here](https://www.youtube.com/watch?v=cRjBj7-VjY4)
- The actual implementation for `std::forward` in STL:

```
    template <class _Tp>inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR _Tp&&  forward(typename remove_reference<_Tp>::type& __t) _NOEXCEPT
    {
        return static_cast<_Tp&&>(__t);
        }
template <class _Tp>
inline _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR
_Tp&&
forward(typename remove_reference<_Tp>::type&& __t) _NOEXCEPT
{
    static_assert(!is_lvalue_reference<_Tp>::value,
                  "can not forward an rvalue as an lvalue");
    return static_cast<_Tp&&>(__t);
}
```

- The operation of forwarding is considered a **type trait**.
- The following guidelines are based on this [YT](https://www.youtube.com/watch?v=Fe0lypOO3x4&list=LLD8ArTGhWPeTeiLqVFxcDlg&index=6&t=0s) presentation
    - The presentation focuses on:
        - **lvalue, rvalue, universal references**
        - comparison between **push_back** and **emplace_back**
        - comparison between **std::move** and **std::forward**
    - Important notes from the presentation:
        - `std::move`  - indicates that the object on which this function is used on, can be moved, or its resources can be stolen
            - it basically casts an expression to `xvalue` (an expiring `rvalue`)
        - **Binding rules**:
            - **lvalue references** can can bind 
                - `values`
                - `rvalues` (if declared as `const lvalue&`)
            - **rvalue references** can can bind 
                - `rvalues`
        - **rvalue references**: `type &&` without type deduction
        - **universal reference**: `type &&` + **type deduction**
        - ![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2Fbasavyr%2FNa_18HM2Cy.png?alt=media&token=9257fa1e-9026-4553-a75f-8c7680f3814e)
        - **uref** can bind to **everything: 
            - lvalues
            - rvalues
            - const
            - etc
        - ![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2Fbasavyr%2Fp5tjthoPbg.png?alt=media&token=7a5ae1c5-fcf3-4ef3-826b-ed6ab70bf5c4)
        - ![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2Fbasavyr%2Ftm9AL6oZUy.png?alt=media&token=66b392f0-6cad-4ef4-9c62-41daba5d30f5)
        - `auto && e` is **type deduction**
        - ![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2Fbasavyr%2FFZiFoA6rcm.png?alt=media&token=0496a5d9-4f94-46d8-b37f-b1fee255413c)
            - Regarding this example
                - __auto &&e = f[2]; will certainly be int &e (lvalue reference) because f[n] returns an lvalue reference and since an rvalue reference is bound to an lvalue reference, the reference collapsing rules kick in: so e will become &&& <=> & after collapsing. thus e will be an lvalue reference and not an lvalue.the second line is the whole idea behind rvalue references. bar is binding to a temporary (rvalue). the collapsing rules kick in: bar is && which binds to an rvalue thus leaving bar unchanged.bar is therefore an rvalue reference.__
                - This comment from the video explains why `bar` is a lvalue reference.
        - **PB** vs **EB**
            - ![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2Fbasavyr%2Fa4Cc83W_-v.png?alt=media&token=a2ee9f63-0a68-411d-834b-2aaf8f40cec2)
            - ![](https://firebasestorage.googleapis.com/v0/b/firescript-577a2.appspot.com/o/imgs%2Fapp%2Fbasavyr%2FtJuJ5mjhMk.png?alt=media&token=76f75c81-9115-47a7-b296-cb3af6a45ab9)
            - Whenever one has an **rvalue** reference, the `std::move()` should be called on the expression, to avoid copying.
                - In the first function, the move constructor, casts the lvalue b to an rvalue
            - Whenever one has **uref**, the `std::forward` has to be used.
                - Since the second function has type deduction, one needs to use forward operator.
- Another great written tutorial can be found [here](https://www.srcmake.com/home/move-semantics)
    - **An L-value is stored in memory and will exist on the next line of code.**
    - **An R-Value is temporary and won't exist (in memory) on the next line of code. **
    - **The & sign that means a variable refers to something that already exists in memory**
    - the & sign only works with L-Value references. If you use **the && sign, then you mean you want an R-Value reference**
    - 

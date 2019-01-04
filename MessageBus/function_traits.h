#pragma once
#include <functional>
#include <tuple>
#include <iostream>
using namespace std;

template <typename T>
struct function_traits;

template<typename Ret,typename...Args>
struct function_traits<Ret(Args...)>
{
public:
	enum{arity=sizeof...(Args) };
	typedef Ret function_type(Args...);
	typedef Ret return_type;
	using stl_function_type = function<function_type>;
	typedef Ret(*pointer)(Args...);

	template<size_t I>
	struct args
	{
		static_assert(I < arity, "index is out of range,index must less than sizeof Args");
		using type = typename tuple_element<I, tuple<Args...>>::type;
	};
};


//函数指针
template<typename Ret,typename...Args>
struct function_traits<Ret(*)(Args...)>:function_traits<Ret(Args...)>{};
// std::function
template <typename Ret,typename... Args>
struct function_traits<function<Ret(Args...)>>:function_traits<Ret(Args...)>{};

//member function
#define FUNCTION_TRAITS(...) \
	template<typename ReturnType,typename ClassType,typename...Args>\
	struct function_traits<ReturnType(ClassType::*)(Args...) __VA_ARGS__>:function_traits<RetureType(Args...)>{};\


FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

//函数对象
template<typename Callable>
struct function_traits:FUNCTION_TRAITS<decltype(&Callable::operator())>{};

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(const Function& lambda)
{
	return static_cast<function_traits<Function>::stl_function_type > (lambda);
}

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(Function&& lambda)
{
	return static_cast<function_traits<Function>::stl_function_type>(forward<Function>(lambda));
}

template<typename Function>
typename function_traits<Function>::pointer to_function_pointer(const Function& lambda)
{
	return static_cast<typename function_traits<Function>::pointer>(lambda);
}

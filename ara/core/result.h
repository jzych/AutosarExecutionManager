#ifndef ARA_CORE_RESULT_H_
#define ARA_CORE_RESULT_H_

#include <type_traits>
#include <boost/variant.hpp>
#include "error_code.h"

namespace ara {
namespace core {

template <typename T, typename E = ErrorCode>
class Result final
{
    boost::variant<T, E> _data;

public:
    using value_type = T;
    using error_type = E;

    Result(T const &t): _data(t) {};
    Result(T &&t): _data(std::move(t)) {};
    explicit Result(E const &e): _data(e) {};
    explicit Result(E &&e): _data(std::move(e)) {};
    Result(Result const &other): _data(other._data) {};
    Result(Result &&other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                    std::is_nothrow_move_constructible<E>::value)
        : _data(std::move(other._data)) {};
    ~Result();

    static Result FromValue(T const &t)
    {
        return Result(t);
    }

    static Result FromValue(T &&t)
    {
        return Result(std::move(t));
    }

    template <typename... Args>
    static Result FromValue(Args &&... args)
    {
        return Result(T{std::forward<Args>(args)...});
    }

    static Result FromError(E const &e)
    {
        return Result(e);
    }

    static Result FromError(E &&e)
    {
        return Result(std::move(e));
    }

    template <typename... Args>
    static Result FromError(Args &&... args)
    {
        return Result(E{std::forward<Args>(args)...});
    }

    Result& operator= (Result const &other)
    {
        _data = other._data;
        return *this;
    }

    Result& operator= (Result &&other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                                std::is_nothrow_move_assignable<T>::value &&
                                                std::is_nothrow_move_constructible<E>::value &&
                                                std::is_nothrow_move_assignable<E>::value)
    {
        _data = std::move(other._data);
        return *this;
    }

    template <typename... Args>
    void EmplaceValue(Args &&... args)
    {

        // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
        _data = std::move(T(std::forward<Args>(args)...));
    }

    template <typename... Args>
    void EmplaceError(Args &&... args)
    {
        // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
        _data = std::move(E(std::forward<Args>(args)...));
    }

    void Swap(Result &other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                      std::is_nothrow_move_assignable<T>::value &&
                                      std::is_nothrow_move_constructible<E>::value &&
                                      std::is_nothrow_move_assignable<E>::value)
    {
        std::swap(_data, other._data);
    }

    bool HasValue() const noexcept
    {
        return _data.which() == 0;
    }

    explicit operator bool() const noexcept
    {
        return HasValue();
    }

    T const& operator*() const &
    {
        return Value();
    }

    T&& operator*() &&
    {
        return Value();
    }

    T const* operator->() const
    {
        return std::addressof(Value());
    }

    T const& Value() const &
    {
        T const* ptr = boost::get<T>(&_data);
        if (ptr)
            return *ptr;
        // throw?
        std::terminate();
    }

    T&& Value() &&
    {
        T* ptr = boost::get<T>(&_data);
        if (ptr)
            return std::move(*ptr);
        // throw?
        std::terminate();
    }

    E const& Error() const &
    {
        E const* ptr = boost::get<E>(&_data);
        if (ptr)
            return *ptr;
        // throw?
        std::terminate();
    }

    E&& Error() &&
    {
        E* ptr = boost::get<E>(&_data);
        if (ptr)
            return std::move(*ptr);
        //throw?
        std::terminate();
    }

    template <typename U>
    T ValueOr(U &&defaultValue) const &
    {
        return HasValue() ? Value() : static_cast<T>(std::forward<U>(defaultValue));
    }

    template <typename U>
    T ValueOr(U &&defaultValue) &&
    {
        return HasValue() ? std::move(Value()) : static_cast<T>(std::forward<U>(defaultValue));
    }

    template <typename G>
    E ErrorOr(G &&defaultError) const
    {
        return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
    }

    template <typename G>
    bool CheckError(G &&error) const
    {
        return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(error)));
    }

    T const& ValueOrThrow() const& noexcept(false)
    {
        T const* ptr = boost::get<T>(&_data);
        if (ptr)
            return *ptr;

        E* e = boost::get<E>(&_data);
        e->ThrowAsException();
    }

    T&& ValueOrThrow () &&noexcept(false)
    {
        T* ptr = boost::get<T>(&_data);
        if (ptr)
            return std::move(*ptr);

        E* e = boost::get<E>(&_data);
        e->ThrowAsException();
    }

    template <typename F> // F must be compatibile to this interface: T f(E const&);
    T Resolve (F &&f) const
    {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }

    template <typename F> // F is expected to be compatible to one of these two interfaces: Result<XXX, E> f(Tconst&); or XXX f(T const&);
    auto Bind (F &&f) const; // TODO
};

template <typename E>
class Result< void, E > final
{
    // Cannot use 'void' for variant, so define our own (default-constructible) dummy type instead.
    struct dummy{};
    using T = dummy;
    boost::variant<T, E> _data;

public:
    using value_type = void;
    using error_type = E;

    Result() noexcept: _data(T{}) {};
    explicit Result(E const &e): _data(e) {};
    explicit Result(E &&e): _data(std::move(e)) {};
    Result(Result const &other): _data(other._data) {};
    Result(Result &&other) noexcept(std::is_nothrow_move_constructible<E>::value)
        : _data(std::move(other._data)) {};
    ~Result();

    static Result FromValue()
    {
        return Result();
    }

    static Result FromError(E const &e)
    {
        return Result(e);
    }

    static Result FromError(E &&e)
    {
        return Result(std::move(e));
    }

    template <typename...  Args>
    static Result FromError(Args &&...  args)
    {
        return Result(E{std::forward<Args>(args)...});
    }

    Result& operator= (Result const &other)
    {
        _data = other._data;
        return *this;
    }

    Result& operator= (Result &&other) noexcept(std::is_nothrow_move_constructible<E>::value &&
                                                std::is_nothrow_move_assignable<E>::value)
    {
        _data = std::move(other._data);
        return *this;
    }

    template <typename...  Args>
    void EmplaceValue(Args &&...  args) noexcept
    {
        _data = T(args...);
    }
    template <typename...  Args>
    void EmplaceError(Args &&...  args)
    {
        // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
        _data = std::move(E(std::forward<Args>(args)...));
    }

    void Swap(Result &other) noexcept(std::is_nothrow_move_constructible<E>::value &&
                                      std::is_nothrow_move_assignable<E>::value)
    {
        std::swap(_data, other._data);
    }

    bool HasValue() const noexcept
    {
        return _data.which() == 0;
    }

    explicit operator bool() const noexcept
    {
        return HasValue();
    }

    void operator*() const {} // Do nothing. This function only exists for helping with generic programming.

    void Value() const {} // Do nothing. This function only exists for helping with generic programming.

    E const& Error() const &
    {
        E const* ptr = boost::get<E>(&_data);
        if (ptr)
            return *ptr;
        // throw?
        std::terminate();
    }

    E&& Error () &&
    {
        E* ptr = boost::get<E>(&_data);
        if (ptr)
            return std::move(*ptr);
        // throw?
        std::terminate();
    }

    template <typename U>
    void ValueOr(U &&defaultValue) const {} // Do nothing. This function only exists for helping with generic programming.

    template <typename G>
    E ErrorOr(G &&defaultError) const
    {
        return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
    }

    template <typename G>
    bool CheckError(G&& error) const
    {
        return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(error)));
    }

    void ValueOrThrow() const noexcept(false)
    {
        T const* ptr = boost::get<T>(&_data);
        if (ptr)
            return;

        E* e = boost::get<E>(&_data);
        e->ThrowAsException();
    }

    template <typename F> // F is expected to be compatible to this interface: void f(E const&);
    void Resolve (F &&f) const
    {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }
};

template <typename T, typename E>
bool operator== (Result<T, E> const &lhs, Result<T, E> const&rhs);
template <typename T, typename E>
bool operator!= (Result<T, E> const &lhs, Result<T, E> const&rhs);
template <typename T, typename E>
bool operator== (Result<T, E> const &lhs, T const &rhs);
template <typename T, typename E>
bool operator== (T const &lhs, Result<T, E> const &rhs);
template <typename T, typename E>
bool operator!= (Result<T, E> const &lhs, T const &rhs);
template <typename T, typename E>
bool operator!= (T const &lhs, Result<T, E> const &rhs);
template <typename T, typename E>
bool operator== (Result<T, E> const &lhs, E const &rhs);
template <typename T, typename E>
bool operator== (E const &lhs, Result<T, E> const &rhs);
template <typename T, typename E>
bool operator!= (Result<T, E> const &lhs, E const &rhs);
template <typename T, typename E>
bool operator!= (E const &lhs, Result<T, E> const &rhs);

template <typename T, typename E>
void swap (Result<T, E> &lhs, Result<T, E> &rhs) noexcept(noexcept(lhs.Swap(rhs)))
{
    lhs.Swap(rhs);
}


}  // namespace core
}  // namespace ara

#endif // ARA_CORE_RESULT_H_

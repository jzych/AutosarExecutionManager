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

    Result(value_type const &t): _data(t) {};
    Result(value_type &&t): _data(std::move(t)) {};
    explicit Result(error_type const &e): _data(e) {};
    explicit Result(error_type &&e): _data(std::move(e)) {};
    Result(Result const &other): _data(other._data) {};
    Result(Result &&other) noexcept(std::is_nothrow_move_constructible<value_type>::value &&
                                    std::is_nothrow_move_constructible<error_type>::value)
        : _data(std::move(other._data)) {};
    ~Result();

    static Result FromValue(value_type const &t)
    {
        return Result(t);
    }

    static Result FromValue(value_type &&t)
    {
        return Result(std::move(t));
    }

    template <typename... Args>
    static Result FromValue(Args &&... args)
    {
        return Result(T{std::forward<Args>(args)...});
    }

    static Result FromError(error_type const &e)
    {
        return Result(e);
    }

    static Result FromError(error_type &&e)
    {
        return Result(std::move(e));
    }

    template <typename... Args>
    static Result FromError(Args &&... args)
    {
        return Result(E{std::forward<Args>(args)...});
    }

    Result& operator=(Result const &other)
    {
        _data = other._data;
        return *this;
    }

    Result& operator=(Result &&other) noexcept(std::is_nothrow_move_constructible<value_type>::value &&
                                               std::is_nothrow_move_assignable<value_type>::value &&
                                               std::is_nothrow_move_constructible<error_type>::value &&
                                               std::is_nothrow_move_assignable<error_type>::value)
    {
        _data = std::move(other._data);
        return *this;
    }

    template <typename... Args>
    void EmplaceValue(Args &&... args)
    {

        // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
        _data = std::move(value_type(std::forward<Args>(args)...));
    }

    template <typename... Args>
    void EmplaceError(Args &&... args)
    {
        // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
        _data = std::move(error_type(std::forward<Args>(args)...));
    }

    void Swap(Result &other) noexcept(std::is_nothrow_move_constructible<value_type>::value &&
                                      std::is_nothrow_move_assignable<value_type>::value &&
                                      std::is_nothrow_move_constructible<error_type>::value &&
                                      std::is_nothrow_move_assignable<error_type>::value)
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

    value_type const& operator*() const &
    {
        return Value();
    }

    T&& operator*() &&
    {
        return Value();
    }

    value_type const* operator->() const
    {
        return std::addressof(Value());
    }

    value_type const& Value() const &
    {
        value_type const* ptr = boost::get<value_type>(&_data);
        if (ptr)
            return *ptr;
        // throw?
        std::terminate();
    }

    T&& Value() &&
    {
        value_type* ptr = boost::get<value_type>(&_data);
        if (ptr)
            return std::move(*ptr);
        // throw?
        std::terminate();
    }

    error_type const& Error() const &
    {
        error_type const* ptr = boost::get<error_type>(&_data);
        if (ptr)
            return *ptr;
        // throw?
        std::terminate();
    }

    E&& Error() &&
    {
        error_type* ptr = boost::get<error_type>(&_data);
        if (ptr)
            return std::move(*ptr);
        //throw?
        std::terminate();
    }

    template <typename U>
    value_type ValueOr(U &&defaultValue) const &
    {
        return HasValue() ? Value() : static_cast<value_type>(std::forward<U>(defaultValue));
    }

    template <typename U>
    value_type ValueOr(U &&defaultValue) &&
    {
        return HasValue() ? std::move(Value()) : static_cast<value_type>(std::forward<U>(defaultValue));
    }

    template <typename G>
    error_type ErrorOr(G &&defaultError) const
    {
        return HasValue() ? static_cast<error_type>(std::forward<G>(defaultError)) : Error();
    }

    template <typename G>
    bool CheckError(G &&error) const
    {
        return HasValue() ? false : (Error() == static_cast<error_type>(std::forward<G>(error)));
    }

    value_type const& ValueOrThrow() const& noexcept(false)
    {
        value_type const* ptr = boost::get<value_type>(&_data);
        if (ptr)
            return *ptr;

        error_type* e = boost::get<error_type>(&_data);
        e->ThrowAsException();
    }

    T&& ValueOrThrow() &&noexcept(false)
    {
        value_type* ptr = boost::get<value_type>(&_data);
        if (ptr)
            return std::move(*ptr);

        error_type* e = boost::get<error_type>(&_data);
        e->ThrowAsException();
    }

    template <typename F> // F must be compatibile to this interface: value_type f(error_type const&);
    value_type Resolve(F &&f) const
    {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }

    template <typename F> // F is expected to be compatible to one of these two interfaces: Result<XXX, E> f(Tconst&); or XXX f(value_type const&);
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
    explicit Result(error_type const &e): _data(e) {};
    explicit Result(error_type &&e): _data(std::move(e)) {};
    Result(Result const &other): _data(other._data) {};
    Result(Result &&other) noexcept(std::is_nothrow_move_constructible<error_type>::value)
        : _data(std::move(other._data)) {};
    ~Result();

    static Result FromValue()
    {
        return Result();
    }

    static Result FromError(error_type const &e)
    {
        return Result(e);
    }

    static Result FromError(error_type &&e)
    {
        return Result(std::move(e));
    }

    template <typename...  Args>
    static Result FromError(Args &&...  args)
    {
        return Result(E{std::forward<Args>(args)...});
    }

    Result& operator=(Result const &other)
    {
        _data = other._data;
        return *this;
    }

    Result& operator=(Result &&other) noexcept(std::is_nothrow_move_constructible<error_type>::value &&
                                                std::is_nothrow_move_assignable<error_type>::value)
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
        _data = std::move(error_type(std::forward<Args>(args)...));
    }

    void Swap(Result &other) noexcept(std::is_nothrow_move_constructible<error_type>::value &&
                                      std::is_nothrow_move_assignable<error_type>::value)
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

    error_type const& Error() const &
    {
        error_type const* ptr = boost::get<error_type>(&_data);
        if (ptr)
            return *ptr;
        // throw?
        std::terminate();
    }

    E&& Error() &&
    {
        error_type* ptr = boost::get<error_type>(&_data);
        if (ptr)
            return std::move(*ptr);
        // throw?
        std::terminate();
    }

    template <typename U>
    void ValueOr(U &&defaultValue) const {} // Do nothing. This function only exists for helping with generic programming.

    template <typename G>
    error_type ErrorOr(G &&defaultError) const
    {
        return HasValue() ? static_cast<error_type>(std::forward<G>(defaultError)) : Error();
    }

    template <typename G>
    bool CheckError(G&& error) const
    {
        return HasValue() ? false : (Error() == static_cast<error_type>(std::forward<G>(error)));
    }

    void ValueOrThrow() const noexcept(false)
    {
        value_type const* ptr = boost::get<value_type>(&_data);
        if (ptr)
            return;

        error_type* e = boost::get<error_type>(&_data);
        e->ThrowAsException();
    }

    template <typename F> // F is expected to be compatible to this interface: void f(error_type const&);
    void Resolve(F &&f) const
    {
        return HasValue() ? Value() : std::forward<F>(f)(Error());
    }
};

template <typename T, typename E>
bool operator==(Result<T, E> const &lhs, Result<T, E> const&rhs)
{
    if(lhs.HasValue() == rhs.HasValue())
    {
        if(lhs.HasValue())
        {
            return lhs.Value() == rhs.Value();
        } else {
            return lhs.Error() == rhs.Error();
        }
    }
    return false;
}
template <typename T, typename E>
bool operator!=(Result<T, E> const &lhs, Result<T, E> const&rhs)
{
    if(lhs.HasValue() == rhs.HasValue())
    {
        if(lhs.HasValue())
        {
            return lhs.Value() != rhs.Value();
        } else {
            return lhs.Error() != rhs.Error();
        }
    }
    return true;
}

template <typename T, typename E>
bool operator==(Result<T, E> const &lhs, T const &rhs)
{
    if(lhs.HasValue())
    {
        return lhs.Value() == rhs;
    }
    return false;
}

template <typename T, typename E>
bool operator==(T const &lhs, Result<T, E> const &rhs)
{
    if(rhs.HasValue())
    {
        return lhs == rhs.Value();
    }
    return false;
}

template <typename T, typename E>
bool operator!=(Result<T, E> const &lhs, T const &rhs)
{
    if(lhs.HasValue())
    {
        return lhs.Value() != rhs;
    }
    return true;
}
template <typename T, typename E>
bool operator!=(T const &lhs, Result<T, E> const &rhs)
{
    if(rhs.HasValue())
    {
        return lhs != rhs.Value();
    }
    return true;
}

template <typename T, typename E>
bool operator==(Result<T, E> const &lhs, E const &rhs)
{
    if(!lhs.HasValue())
    {
        return lhs.Error() == rhs;
    }
    return false;
}

template <typename T, typename E>
bool operator==(E const &lhs, Result<T, E> const &rhs)
{
    if(!rhs.HasValue())
    {
        return lhs == rhs.Error();
    }
    return false;
}

template <typename T, typename E>
bool operator!=(Result<T, E> const &lhs, E const &rhs)
{
    if(!rhs.HasValue())
    {
        return lhs.Error() != rhs;
    }
    return true;
}

template <typename T, typename E>
bool operator!=(E const &lhs, Result<T, E> const &rhs)
{
    if(!rhs.HasValue())
    {
        return lhs != rhs.Error();
    }
    return true;
}

template <typename T, typename E>
void swap (Result<T, E> &lhs, Result<T, E> &rhs) noexcept(noexcept(lhs.Swap(rhs)))
{
    lhs.Swap(rhs);
}


}  // namespace core
}  // namespace ara

#endif // ARA_CORE_RESULT_H_

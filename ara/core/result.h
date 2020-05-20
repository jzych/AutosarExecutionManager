#ifndef ARA_CORE_RESULT_H_
#define ARA_CORE_RESULT_H_

#include <type_traits>
#include "error_code.h"

namespace ara {
namespace core {

template <typename T, typename E = ErrorCode>
class Result final
{
public:
    using value_type = T;
    using error_type = E;

    Result(T const &t);
    explicit Result(E const &e);
    explicit Result(E &&e);
    Result(Result const &other);
    Result(Result &&other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                    std::is_nothrow_move_constructible<E>::value);
    ~Result();

    static Result FromValue(T const &t);
    static Result FromValue(T &&t);

    template <typename... Args>
    static Result FromValue(Args &&... args);
    static Result FromError(E &&e);
    template <typename... Args>
    static Result FromError(Args &&... args);

    Result& operator= (Result const &other);
    Result& operator= (Result &&other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                                std::is_nothrow_move_assignable<T>::value &&
                                                std::is_nothrow_move_constructible<E>::value &&
                                                std::is_nothrow_move_assignable<E>::value);

    template <typename... Args>
    void EmplaceValue(Args &&... args);
    template <typename... Args>
    void EmplaceError(Args &&... args);
    void Swap(Result &other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                      std::is_nothrow_move_assignable<T>::value &&
                                      std::is_nothrow_move_constructible<E>::value &&
                                      std::is_nothrow_move_assignable<E>::value);
    bool HasValue() const noexcept;
    explicit operator bool() const noexcept;
    T const& operator*() const &;
    T&& operator*() &&;
    T const* operator->() const;
    T const& Value() const &;
    T&& Value() &&;

    E const& Error () const &;
    E&& Error () &&;

    template <typename U>
    T ValueOr(U &&defaultValue) const &;
    template <typename U>
    T ValueOr(U &&defaultValue) &&;
    template <typename G>
    E ErrorOr(G &&defaultError) const;
    template <typename G>
    bool CheckError(G &&error) const;

    T const& ValueOrThrow() const& noexcept(false);
    T&& ValueOrThrow () &&noexcept(false);

    template <typename F> // F must be compatibile to this interface: T f(E const&);
    T Resolve (F &&f) const;
    template <typename F> // F is expected to be compatible to one of these two interfaces: Result<XXX, E> f(Tconst&); or XXX f(T const&);
    auto Bind (F &&f) const;
};

template <typename E>
class Result< void, E > final
{
public:
    using value_type = void;
    using error_type = E;

    Result() noexcept;
    explicit Result(E const &e);
    explicit Result(E &&e);
    Result(Result const &other);
    Result(Result &&other) noexcept(std::is_nothrow_move_constructible<E>::value);
    ~Result();

    static Result FromValue();
    static Result FromError(E const &e);
    static Result FromError(E &&e);

    template <typename...  Args>
    static Result FromError(Args &&...  args);
    Result& operator= (Result const &other);
    Result& operator= (Result &&other) noexcept(std::is_nothrow_move_constructible<E>::value &&
                                                std::is_nothrow_move_assignable<E>::value);

    template <typename...  Args>
    void EmplaceValue(Args &&...  args) noexcept;
    template <typename...  Args>
    void EmplaceError(Args &&...  args);

    void Swap(Result &other) noexcept(std::is_nothrow_move_constructible<E>::value &&
                                      std::is_nothrow_move_assignable<E>::value);

    bool HasValue() const noexcept;
    explicit operator bool() const noexcept;
    void operator*() const;
    void Value() const;
    E const& Error() const &;
    E&& Error () &&;

    template <typename U>
    void ValueOr(U &&defaultValue) const;
    template <typename G>
    E ErrorOr(G &&defaultError) const;
    void ValueOrThrow() const noexcept(false);

    template <typename F> // F is expected to be compatible to this interface: void f(E const&);
    void Resolve (F &&f) const;
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
void swap (Result<T, E> &lhs, Result<T, E> &rhs) noexcept(noexcept(lhs.Swap(rhs)));


}  // namespace core
}  // namespace ara

#endif // ARA_CORE_RESULT_H_

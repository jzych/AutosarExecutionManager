#ifndef ARA_CORE_ERROR_DOMAIN_H_
#define ARA_CORE_ERROR_DOMAIN_H_

#include <cstdint>

namespace ara {
namespace core {

class ErrorDomain
{
public:
    using IdType = std::uint64_t;
    using CodeType = std::int32_t;
    using SupportDataType = std::uint32_t;  // TODO

    ErrorDomain(const ErrorDomain&) = delete;
    ErrorDomain& operator=(const ErrorDomain&) = delete;
    ErrorDomain(ErrorDomain&&) = delete;
    ErrorDomain& operator=(ErrorDomain&&) = delete;
    explicit constexpr ErrorDomain(IdType id) noexcept;
    ~ErrorDomain() = default;

    constexpr bool operator==(const ErrorDomain& other) const noexcept;
    constexpr bool operator!=(const ErrorDomain& other) const noexcept;

    constexpr IdType id() const noexcept;

    virtual const char* Name() const noexcept = 0;
    virtual const char* Message(CodeType errorCode) const noexcept = 0;
    virtual void ThrowAsException(const ErrorCode& errorCode) const noexcept(false) = 0;
};

}  // namespace core
}  // namespace ara

#endif  // ARA_EXEC_ERR_DOMAIN_H_

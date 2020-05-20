#include "error_code.h"
namespace ara {
namespace core {

constexpr ErrorCode::ErrorCode(
    ErrorDomain::CodeType value,
    const ErrorDomain& domain,
    ErrorDomain::SupportDataType = ErrorDomain::SupportDataType()) noexcept
{
}

constexpr ErrorDomain::CodeType ErrorCode::Value() const noexcept
{
    return 0;
}

constexpr const ErrorDomain& ErrorCode::Domain() const noexcept
{
    return ErrorDomain(0);
}

constexpr ErrorDomain::SupportDataType ErrorCode::SupportData() const noexcept
{
    return 0;
}

StringView ErrorCode::Message() const noexcept
{
    return StringView();
}

void ErrorCode::ThrowAsException() const
{
}

constexpr bool operator==(const ErrorCode& lhs, const ErrorCode& rhs) noexcept
{
    return true;
}

constexpr bool operator!=(const ErrorCode& lhs, const ErrorCode& rhs) noexcept
{
    return true;
}

}  // namespace core
}  // namespace ara

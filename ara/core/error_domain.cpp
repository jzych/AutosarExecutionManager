#include "error_domain.h"

namespace ara {
namespace core {

explicit constexpr ErrorDomain::ErrorDomain(IdType id) noexcept
{
}

constexpr bool ErrorDomain::operator==(const ErrorDomain& other) const noexcept
{
    return true;
}

constexpr bool ErrorDomain::operator!=(const ErrorDomain& other) const noexcept
{
    return true;
}

constexpr IdType ErrorDomain::id() const noexcept
{
    return 0;
}

}  // namespace core
}  // namespace ara

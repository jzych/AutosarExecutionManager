#ifndef ARA_CORE_ERROR_CODE_H_
#define ARA_CORE_ERROR_CODE_H_

namespace ara {
namespace core {

class ErrorCode final
{
public:
    template <typename EnumT>
    constexpr ErrorCode(EnumT e,
                        ErrorDomain::SupportDataType data = ErrorDomain::SupportDataType()) noexcept
    {
    }

    constexpr ErrorCode(ErrorDomain::CodeType value,
                        const ErrorDomain& domain,
                        ErrorDomain::SupportDataType = ErrorDomain::SupportDataType()) noexcept;

    constexpr ErrorDomain::CodeType Value() const noexcept;
    constexpr const ErrorDomain& Domain() const noexcept;
    constexpr ErrorDomain::SupportDataType SupportData() const noexcept;
    StringView Message() const noexcept;
    void ThrowAsException() const;
};

constexpr bool operator==(const ErrorCode& lhs, const ErrorCode& rhs) noexcept;
constexpr bool operator!=(const ErrorCode& lhs, const ErrorCode& rhs) noexcept;

}  // namespace core
}  // namespace ara
#endif  // ARA_CORE_ERROR_CODE_H_

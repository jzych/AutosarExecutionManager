#ifndef ARA_EXEC_ERR_DOMAIN_H_
#define ARA_EXEC_ERR_DOMAIN_H_

#include "error_code.h"

namespace ara {
namespace exec {

enum class ExecErrc : ara::core::ErrorDomain::CodeType {
    kGeneralError = 1,
    kInvalidArguments,
    kCommunicationError,
    kMetaModelError,
    kCancelled,
    kFailed
};

class ExecException : public Exception
{
public:
    explicit ExecException(ara::core::ErrorCode errorCode) noexcept;
};

const ara::core::ErrorDomain& GetExecErrorDomain() noexcept;
ara::core::ErrorCode MakeErrorCode(ara::exec::ExecErrc code,
                                   ara::core::ErrorDomain::SupportDataType data) noexcept;

class ExecErrorDomain final : public ara::core::ErrorDomain
{
public:
    ExecErrorDomain() noexcept;

    const char* Name() const noexcept override;
    const char* Message(CodeType errorCode) const noexcept override;
    void ThrowAsException(const ara::core::ErrorCode& errorCode) noexcept(false) override;
};

}  // namespace exec
}  // namespace ara

#endif  // ARA_EXEC_ERR_DOMAIN_H_

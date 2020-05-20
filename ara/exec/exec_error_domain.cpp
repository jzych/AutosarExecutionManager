#include "exec_error_domain.h"

namespace ara {
namespace exec {

explicit ExecException::ExecException(ara::core::ErrorCode errorCode) noexcept
{
}

const ara::core::ErrorDomain& GetExecErrorDomain() noexcept
{
    return ara::core::ErrorDomain();
}

ara::core::ErrorCode MakeErrorCode(ara::exec::ExecErrc code,
                                   ara::core::ErrorDomain::SupportDataType data) noexcept
{
    return 0;
}

ExecErrorDomain::ExecErrorDomain() noexcept
{
}

const char* ExecErrorDomain::Name() const noexcept override
{
    return nullptr;
}

const char* ExecErrorDomain::Message(CodeType errorCode) const noexcept override
{
    return nullptr;
}

void ExecErrorDomain::ThrowAsException(const ara::core::ErrorCode& errorCode) noexcept(
    false) override
{
}

}  // namespace exec
}  // namespace ara

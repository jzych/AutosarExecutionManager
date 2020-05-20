#include "exception.h"

namespace ara {
namespace core {

explicit Exception::Exception(ErrorCode err) noexcept : error_{err}
{
}

const char* Exception::what() const noexcept override
{
    return "";
}

const ErrorCode& Exception::Error() const noexcept
{
    return error_;
}

}  // namespace core
}  // namespace ara

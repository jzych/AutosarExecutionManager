#ifndef ARA_CORE_EXCEPTION_H_
#define ARA_CORE_EXCEPTION_H_

#include <stdexcept>
#include "error_code.h"

namespace ara {
namespace core {

class Exception : public std::exception
{
public:
    explicit Exception(ErrorCode err) noexcept;
    const char* what() const noexcept override;
    const ErrorCode& Error() const noexcept;

protected:
    ErrorCode error_;
};

}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_EXCEPTION_H_

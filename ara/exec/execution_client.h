#ifndef ARA_EXECUTION_CLIENT_H_
#define ARA_EXECUTION_CLIENT_H_

namespace ara {
namespace exec {

class ExecutionClient
{
public:
    ExecutionClient() noexcept;
    ~ExecutionClient() noexcept;

    ara::core::Result<void> ReportExecutionState(ExecutionState state) const noexcept;
};

}  // namespace exec
}  // namespace ara

#endif  // ARA_EXECUTION_CLIENT_H_

#include "execution_client.h"

namespace ara {
namespace exec {

ExecutionClient::ExecutionClient() noexcept
{
}
ExecutionClient::~ExecutionClient() noexcept
{
}

ara::core::Result<void> ExecutionClient::ReportExecutionState(ExecutionState state) const noexcept
{
    return ara::core::Result<void>();
}

}  // namespace exec
}  // namespace ara

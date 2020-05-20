#include "deterministic_client.h"

namespace ara {
namespace exec {

DeterministicClient::DeterministicClient() const noexcept
{
}

DeterministicClient::~DeterministicClient() const noexcept
{
}

ActivationReturnType DeterministicClient::WaitForNextActivation() const noexcept
{
    return ActivationReturnType::kRegisterServices;
}

// Void DeterministicClient::RunWorkerPool(Worker& runnableObj,
//                                         Container& container) const noexcept
// {
// }

uint64_t GetRandom() const noexcept
{
    return 0;
}

// ActivationTimeStampReturnType DeterministicClient::GetActivationTime(TimeStamp) const
// noexcept
// {
//     return ActivationTimeStampReturnType::kSuccess;
// }

// ActivationTimeStampReturnType DeterministicClient::GetNextActivationTime(
//     TimeStamp) const noexcept
// {
//     return ActivationTimeStampReturnType::kSuccess;
// }

}  // namespace exec
}  // namespace ara

#include "state_client.h"

namespace ara {
namespace exec {

ara::core::Result<CtorToken> FunctionGroup::Preconstruct(
    ara::core::StringView metaModelIdentifier) noexcept
{
    return ara::core::Result<CtorToken>();
}

FunctionGroup::FunctionGroup(CtorToken&& token) noexcept
{
}

FunctionGroup::~FunctionGroup() noexcept
{
}

bool FunctionGroup::operator==(const FunctionGroup& other) const noexcept
{
    return true;
}

bool FunctionGroup::operator!=(const FunctionGroup& other) const noexcept
{
    return true;
}

ara::core::Result<CtorToken> FunctionGroupState::Preconstruct(
    const FunctionGroup& FunctionGroup, ara::core::StringView metaModelIdentifier) noexcept
{
    return ara::core::Result<CtorToken>();
}

FunctionGroupState::FunctionGroupState(CtorToken&& token) noexcept
{
}

FunctionGroupState::~FunctionGroupState() noexcept
{
}

bool FunctionGroupState::operator==(const FunctionGroupState& other) const noexcept
{
    return true;
}

bool FunctionGroupState::operator!=(const FunctionGroupState& other) const noexcept
{
    return true;
}

StateClient::StateClient() noexcept
{
}

StateClient::~StateClient() noexcept
{
}

ara::core::Future<void> StateClient::SetState(const FunctionGroupState& state) const noexcept
{
    return ara::core::Future<void>();
}

ara::core::Future<void> StateClient::GetInitialMachineStateTransitionResult() const noexcept
{
    return ara::core::Future<void>();
}

}  // namespace exec
}  // namespace ara

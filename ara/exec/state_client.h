#ifndef ARA_STATE_CLIENT_H_
#define ARA_STATE_CLIENT_H_

namespace ara {
namespace exec {

class FunctionGroup
{
public:
    struct CtorToken  // TODO
    {
    };

    static ara::core::Result<CtorToken> Preconstruct(
        ara::core::StringView metaModelIdentifier) noexcept;
    FunctionGroup(CtorToken&& token) noexcept;
    ~FunctionGroup() noexcept;

    bool operator==(const FunctionGroup& other) const noexcept;
    bool operator!=(const FunctionGroup& other) const noexcept;
};

class FunctionGroupState
{
public:
    struct CtorToken  // TODO
    {
    };

    static ara::core::Result<CtorToken> Preconstruct(const FunctionGroup& FunctionGroup, ara::core::StringView metaModelIdentifier) noexcept;
    FunctionGroupState(CtorToken&& token) noexcept;
    ~FunctionGroupState() noexcept;

    bool operator==(const FunctionGroupState& other) const noexcept;
    bool operator!=(const FunctionGroupState& other) const noexcept;
};

class StateClient {
public:
  StateClient() noexcept;
  ~StateClient() noexcept;

  ara::core::Future<void> SetState(const FunctionGroupState& state) const noexcept;
  ara::core;:Future<void> GetInitialMachineStateTransitionResult() const noexcept;
};

}  // namespace exec
}  // namespace ara

#endif  // ARA_STATE_CLIENT_H_

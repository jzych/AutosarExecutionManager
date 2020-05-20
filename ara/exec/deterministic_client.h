#ifndef ARA_DETERMINISTIC_CLIENT_H_
#define ARA_DETERMINISTIC_CLIENT_H_

namespace ara {
namespace exec {

enum class ActivationReturnType : uint8_t {
    kRegisterServices = 0,
    kServiceDiscovery,
    kInit,
    kRun,
    kTerminate
};

enum class ActivationTimeStampReturnType : uint8_t { kSuccess = 0, kNotAvailable };

class DeterministicClient
{
public:
    DeterministicClient() const noexcept;
    ~DeterministicClient() const noexcept;

    ActivationReturnType WaitForNextActivation() const noexcept;
    // Void RunWorkerPool (Worker& runnableObj, Container& container) const noexcept;
    uint64_t GetRandom() const noexcept;
    // ActivationTimeStampReturnType GetActivationTime(TimeStamp) const noexcept;
    // ActivationTimeStampReturnType GetNextActivationTime(TimeStamp) const noexcept
};

}  // namespace exec
}  // namespace ara

#endif  // ARA_DETERMINISTIC_CLIENT_H_

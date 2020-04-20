#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_H_

#include <string>
#include <vector>

namespace ara {
namespace exec {
namespace parser {

struct ExecutionManifest
{
    // TODO add proper members

    bool operator==(const ExecutionManifest&) const noexcept
    {
        return true;
    }
    bool operator!=(const ExecutionManifest& other) const noexcept
    {
        return !(*this == other);
    }
};

struct MachineManifest
{
    // TODO add proper members

    bool operator==(const MachineManifest&) const noexcept
    {
        return true;
    }
    bool operator!=(const MachineManifest& other) const noexcept
    {
        return !(*this == other);
    }
};

class Manifest  // Simple union wrapper- no std::variant in c++14
{
public:
    enum class Type { kExecution, kMachine, kUnknown };

public:
    Manifest(){};
    Type get_type() const
    {
        return type_;
    }
    ExecutionManifest get_execution() const
    {
        return exec_man;
    }
    MachineManifest get_machine() const
    {
        return mach_man;
    }

    void set_execution(const ExecutionManifest& man)
    {
        type_ = Type::kExecution;
        exec_man = man;
    }
    void set_machine(const MachineManifest& man)
    {
        type_ = Type::kMachine;
        mach_man = man;
    }

private:
    Type type_{Type::kUnknown};
    union
    {
        ExecutionManifest exec_man;
        MachineManifest mach_man;
    };
};

Manifest parse_manifest(const std::string& /*path*/) noexcept(false);

}  // namespace parser
}  // namespace exec
}  // namespace ara

#endif  // ARA_EXEC_PARSER_MANIFEST_PARSER_H_

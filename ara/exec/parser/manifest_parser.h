#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_H_

#include <memory>
#include <string>
#include <vector>

namespace ara {
namespace exec {
namespace parser {

struct ExecutionManifest
{
    struct Process
    {
        struct StartupConfig
        {
            struct StartupOption
            {
                std::string kind{};
                std::string name{};
                std::string arg{};
                bool operator==(const StartupOption&) const noexcept;
                bool operator!=(const StartupOption&) const noexcept;
            };

            struct MachineInstanceRef
            {
                std::string function_group{};
                std::string mode{};
                bool operator==(const MachineInstanceRef&) const noexcept;
                bool operator!=(const MachineInstanceRef&) const noexcept;
            };

            std::vector<StartupOption> startup_options{};
            std::vector<MachineInstanceRef> machine_instance_refs{};
            bool operator==(const StartupConfig&) const noexcept;
            bool operator!=(const StartupConfig&) const noexcept;
        };

        std::string name{};
        std::vector<StartupConfig> startup_configs{};

        bool operator==(const Process&) const noexcept;
        bool operator!=(const Process&) const noexcept;
    };

    std::string manifest_id{};
    std::vector<Process> processes{};

    bool operator==(const ExecutionManifest&) const noexcept;
    bool operator!=(const ExecutionManifest&) const noexcept;
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

class Manifest
{
public:
    enum class Type { kExecution, kMachine, kUnknown };

public:
    Type get_type() const
    {
        return type_;
    }

    const ExecutionManifest* get_execution() const
    {
        return exec_man.get();
    }

    const MachineManifest& get_machine() const
    {
        return *mach_man;
    }

    void set_execution(std::unique_ptr<ExecutionManifest> man)
    {
        type_ = Type::kExecution;
        exec_man = std::move(man);
    }

    void set_machine(std::unique_ptr<MachineManifest> man)
    {
        type_ = Type::kMachine;
        mach_man = std::move(man);
    }

private:
    Type type_{Type::kUnknown};
    std::unique_ptr<ExecutionManifest> exec_man{};
    std::unique_ptr<MachineManifest> mach_man{};
};

Manifest parse_manifest(const std::string& path) noexcept(false);

}  // namespace parser
}  // namespace exec
}  // namespace ara

#endif  // ARA_EXEC_PARSER_MANIFEST_PARSER_H_

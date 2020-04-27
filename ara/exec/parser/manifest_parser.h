#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_H_

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace ara {
namespace exec {
namespace parser {

using json = nlohmann::json;

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
    struct ModeDeclarationGroup
    {
        struct ModeDeclaration
        {
            std::string mode{};
            bool operator==(const ModeDeclaration&) const noexcept;
            bool operator!=(const ModeDeclaration&) const noexcept;
        };

        std::string function_group_name{};
        std::vector<ModeDeclaration> mode_declarations{};
        bool operator==(const ModeDeclarationGroup&) const noexcept;
        bool operator!=(const ModeDeclarationGroup&) const noexcept;
    };

    std::string manifest_id{};
    std::vector<ModeDeclarationGroup> mode_declaration_groups{};
    bool operator==(const MachineManifest&) const noexcept;
    bool operator!=(const MachineManifest&) const noexcept;
};

class IManifestParser
{
public:
    virtual ~IManifestParser() noexcept = default;
    virtual ExecutionManifest parse_execution_manifest(const std::string& path) noexcept(false) = 0;
    virtual MachineManifest parse_machine_manifest(const std::string& path) noexcept(false) = 0;
};

class ManifestParser : public IManifestParser
{
public:
    virtual ~ManifestParser() noexcept = default;
    virtual ExecutionManifest parse_execution_manifest(const std::string& path) noexcept(
        false) override;

    virtual MachineManifest parse_machine_manifest(const std::string& path) noexcept(
        false) override;

private:
    json read_manifest_file(const std::string& path) noexcept(false);
    void validate_content(const json& json_obj, const std::vector<std::string>& json_keys) const
        noexcept(false);
};

}  // namespace parser
}  // namespace exec
}  // namespace ara

#endif  // ARA_EXEC_PARSER_MANIFEST_PARSER_H_


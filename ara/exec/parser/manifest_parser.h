#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_H_

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

namespace ara {
namespace exec {
namespace parser {

using json = nlohmann::json;

struct ExecutionManifest
{
    // TODO add proper members
};

struct MachineManifest
{
    // TODO add proper members
};

class IManifestParser
{
public:
    virtual ExecutionManifest parse_execution_manifest(const std::string& path) noexcept(false) = 0;
    virtual MachineManifest parse_machine_manifest(const std::string& path) noexcept(false) = 0;
    virtual ~IManifestParser() noexcept = default;
};

class ManifestParser : public IManifestParser
{
public:
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

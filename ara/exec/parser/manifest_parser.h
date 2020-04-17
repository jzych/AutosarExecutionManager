#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_HPP_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_HPP_

#include <string>

namespace ara {
namespace exec {
namespace parser {

struct ExecutionManifest
{
    // TODO add proper members

    bool operator==(const ExecutionManifest&) const
    {
        return true;
    }
};

struct MachineManifest
{
    // TODO add proper members

    bool operator==(const MachineManifest&) const
    {
        return true;
    }
};

ExecutionManifest parse_execution_manifest(const std::string& /*path*/);
MachineManifest parse_machine_manifest(const std::string& /*path*/);

}  // namespace parser
}  // namespace exec
}  // namespace ara

#endif  // ARA_EXEC_PARSER_MANIFEST_PARSER_HPP_

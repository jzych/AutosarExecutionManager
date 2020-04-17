#include "manifest_parser.h"

#include <nlohmann/json.hpp>

namespace ara {
namespace exec {
namespace parser {

ExecutionManifest parse_execution_manifest(const std::string& /*path*/)
{
    // TODO implement this method
    return ExecutionManifest();
}

MachineManifest parse_machine_manifest(const std::string& /*path*/)
{
    // TODO implement this method
    return MachineManifest();
}

}  // namespace parser
}  // namespace exec
}  // namespace ara

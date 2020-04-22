#include "manifest_parser.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace ara {
namespace exec {
namespace parser {

using json = nlohmann::json;

namespace {
namespace EMJsonKeys {
const std::string kApplicationManifest = "Application_manifest";
const std::string kApplicationManifestId = "Application_manifest_id";
// const std::string kProcess = "Process";
// const std::string kProcessName = "Process_name";
// const std::string kModeDependentStartupConfigs = "Mode_dependent_startup_configs";
// const std::string kStartupOptions = "Startup_options";
// const std::string kStartupOptionsOptionKind = "Option_kind";
// const std::string kStartupOptionsOptionName = "Option_name";
// const std::string kStartupOptionsOptionArg = "Option_arg";
// const std::string kModeInMachineInstanceRefs = "Mode_in_machine_instance_refs";
// const std::string kFunctionGroup = "Function_group";
// const std::string kMode = "Mode";
// TODO add rest of the keys

const std::vector<std::string> kAsVector{kApplicationManifest,
                                         kApplicationManifestId /* TODO add rest of the keys */};

}  // namespace EMJsonKeys

namespace MMJsonKeys {
const std::string kMachineManifest = "Machine_manifest";
// TODO add rest of the keys

const std::vector<std::string> kAsVector{kMachineManifest /* TODO add rest of the keys */};
}  // namespace MMJsonKeys

}  // anonymous namespace

template <typename T>
bool try_to_read_value(const json& json_obj, const std::string& key, T& output_value)
{
    T tmp{};
    try {
        tmp = json_obj.at(key);
    } catch (json::out_of_range) {
        std::cerr << "ara::exec::parser::try_to_read_value -> unable to read key: " << key << '\n';
        return false;
    }
    output_value = tmp;
    return true;
}

bool validate_manifest(const json& /* json_obj */, const std::vector<std::string>& /* keys */)
{
    // TODO implement this method
    return true;
}

ExecutionManifest parse_execution_manifest(const json& /* json_obj */)
{
    // TODO implement this method
    return ExecutionManifest();
}

MachineManifest parse_machine_manifest(const json& /* json_obj */)
{
    // TODO implement this method
    return MachineManifest();
}

Manifest parse_manifest(const std::string& path) noexcept(false)
{
    std::ifstream manifest_content(path, std::ifstream::binary);
    if (not manifest_content.is_open()) {
        throw std::runtime_error(
            "ara::com::exec::parser::parse_manifest -> cannot open manifest: " + path + "\n");
    }

    Manifest ret_val;

    try {
        json manifest_json;
        manifest_content >> manifest_json;
        manifest_content.close();

        std::string manifest_type{};
        if (try_to_read_value(manifest_json, EMJsonKeys::kApplicationManifest, manifest_type)) {
            if (validate_manifest(manifest_json.at(EMJsonKeys::kApplicationManifest),
                                  EMJsonKeys::kAsVector)) {
                ret_val.set_execution(
                    parse_execution_manifest(manifest_json.at(EMJsonKeys::kApplicationManifest)));
            }
        }
        else if (try_to_read_value(manifest_json, MMJsonKeys::kMachineManifest, manifest_type)) {
            if (validate_manifest(manifest_json.at(MMJsonKeys::kMachineManifest),
                                  MMJsonKeys::kAsVector)) {
                ret_val.set_machine(
                    parse_machine_manifest(manifest_json.at(MMJsonKeys::kMachineManifest)));
            }
        }
        else {
            throw std::runtime_error(
                "ara::exec::parser::parse_manifest -> unknown manifest type in " + path + '\n');
        }

    } catch (json::exception& e) {
        throw std::runtime_error(
            "ara::exec::parser::parse_manifest -> error during parsing manifest " + path +
            "\tFollowing exception occured: " + e.what() + '\n');
    }

    return ret_val;
}

}  // namespace parser
}  // namespace exec
}  // namespace ara

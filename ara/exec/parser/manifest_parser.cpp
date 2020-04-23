#include "manifest_parser.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace ara {
namespace exec {
namespace parser {

namespace {

namespace EMJsonKeys {
const std::string kApplicationManifest = "Application_manifest";
// TODO add rest of the keys

const std::vector<std::string> kAsVector{kApplicationManifest /* TODO add rest of the keys */};
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

ExecutionManifest ManifestParser::parse_execution_manifest(const std::string& path) noexcept(false)
{
    using namespace EMJsonKeys;
    auto manifest_json{read_manifest_file(path)};

    validate_content(manifest_json, kAsVector);

    // TODO implement rest of the method

    return ExecutionManifest();
}

MachineManifest ManifestParser::parse_machine_manifest(const std::string& path) noexcept(false)
{
    using namespace MMJsonKeys;
    auto manifest_json{read_manifest_file(path)};

    validate_content(manifest_json, kAsVector);

    // TODO implement rest of the method

    return MachineManifest();
}

json ManifestParser::read_manifest_file(const std::string& path) noexcept(false)
{
    std::ifstream manifest_content(path, std::ifstream::binary);
    if (not manifest_content.is_open()) {
        throw std::runtime_error(
            "ara::com::exec::parser::parse_manifest -> cannot open manifest: " + path + "\n");
    }

    json manifest_json;

    try {
        manifest_content >> manifest_json;
    } catch (json::exception& e) {
        manifest_content.close();
        throw std::runtime_error(
            "ManifestParser::read_manifest_file -> cannot read manifest file. " +
            std::string(e.what()));
    }

    manifest_content.close();
    return manifest_json;
}

void ManifestParser::validate_content(const json& /*json_obj*/,
                                      const std::vector<std::string>& /*json_keys*/) const
    noexcept(false)
{
    // If validation will end with failure, this method will throw std::runtime_error
}

}  // namespace parser
}  // namespace exec
}  // namespace ara

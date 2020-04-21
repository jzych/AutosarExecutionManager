#include <fstream>
#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "manifest_parser.h"

using namespace ara::exec::parser;
using json = nlohmann::json;

bool create_manifest(const std::string& path, const std::string& content)
{
    std::ofstream output(path, std::ofstream::binary);
    if (not output.is_open())
        return false;
    try {
        auto j{json::parse(content)};
        std::cout << std::setw(4) << j << std::endl;

    } catch (json::exception& e) {
        return true;
    }
    output << content << std::endl;
    output.close();
    return true;
}

TEST(AraExecParserParseManifest, InvalidExecutionManifestFileExceptionThrown)
{
    const std::string manifest_path{"noexisting_execution_manifest.json"};  // not existing file
    ManifestParser mp{};
    EXPECT_THROW(mp.parse_execution_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, InvalidMachineManifestFileExceptionThrown)
{
    const std::string manifest_path{"noexisting_machine_manifest.json"};  // not existing file
    ManifestParser mp{};
    EXPECT_THROW(mp.parse_machine_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, EmptyExecutionManifestFileExceptionThrown)
{
    const std::string manifest_path{"empty_manifest.json"};  // empty file
    const std::string manifest_content{""};
    ManifestParser mp{};
    ASSERT_TRUE(create_manifest(manifest_path, manifest_content))
        << "Unable to create test manifest";
    EXPECT_THROW(mp.parse_execution_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, EmptyMachineManifestFileExceptionThrown)
{
    const std::string manifest_path{"empty_manifest.json"};  // empty file
    const std::string manifest_content{""};
    ManifestParser mp{};
    ASSERT_TRUE(create_manifest(manifest_path, manifest_content))
        << "Unable to create test manifest";
    EXPECT_THROW(mp.parse_machine_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, ExecutionManifestAllKeysUsedSuccess)
{
    const std::string manifest_path{"execution_manifest.json"};

    const std::string manifest_id{"test_app"};
    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.startup_options.push_back(option);
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    // Prepare manifest content
    const std::string manifest_content{

        "{\"Application_manifest\": {\
        \"Application_manifest_id\": \"" +
        manifest_id +
        "\",\
        \"Process\": [ \
            { \
                \"Mode_dependent_startup_configs\": [ \
                    { \
                        \"Startup_options\": [ \
                            { \
                                \"Option_kind\": \"" +
        option_kind1 +
        "\",\
                                \"Option_name\": \"" +
        option_name1 +
        "\",\
                                \"Option_arg\": \"" +
        option_arg1 +
        "\"\
                            } \
                        ], \
                        \"Mode_in_machine_instance_refs\": [ \
                            { \
                                \"Function_group\": \"" +
        function_group +
        "\",\
                                \"Mode\": \"" +
        mode1 +
        "\"\
                            } \
                        ] \
                    } \
                ], \
                \"Process_name\": \"" +
        process_name +
        "\"\
            } \
        ]\
    }\
  }"};

    if (create_manifest(manifest_path, manifest_content)) {
        auto manifest = parse_manifest(manifest_path);
        const auto* exec_man = manifest.get_execution();
        ASSERT_EQ(expected_manifest, *exec_man);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

TEST(AraExecParserParseManifest, ExecutionManifestManifestIdMissingSuccess)
{
    const std::string manifest_path{"execution_manifest.json"};

    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.startup_options.push_back(option);
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);

    // Prepare manifest content
    const std::string manifest_content{

        "{\"Application_manifest\": {\
        \"Process\": [ \
            { \
                \"Mode_dependent_startup_configs\": [ \
                    { \
                        \"Startup_options\": [ \
                            { \
                                \"Option_kind\": \"" +
        option_kind1 +
        "\",\
                                \"Option_name\": \"" +
        option_name1 +
        "\",\
                                \"Option_arg\": \"" +
        option_arg1 +
        "\"\
                            } \
                        ], \
                        \"Mode_in_machine_instance_refs\": [ \
                            { \
                                \"Function_group\": \"" +
        function_group +
        "\",\
                                \"Mode\": \"" +
        mode1 +
        "\"\
                            } \
                        ] \
                    } \
                ], \
                \"Process_name\": \"" +
        process_name +
        "\"\
            } \
        ]\
    }\
  }"};

    if (create_manifest(manifest_path, manifest_content)) {
        auto manifest = parse_manifest(manifest_path);
        const auto* exec_man = manifest.get_execution();
        ASSERT_EQ(expected_manifest, *exec_man);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

TEST(AraExecParserParseManifest, ExecutionManifestStartupConfigsSectionMissingSuccess)
{
    const std::string manifest_path{"execution_manifest.json"};

    const std::string manifest_id{"test_app"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    // Prepare manifest content
    const std::string manifest_content{

        "{\"Application_manifest\": {\
        \"Application_manifest_id\": \"" +
        manifest_id +
        "\",\
        \"Process\": [ \
            { \
                \"Process_name\": \"" +
        process_name +
        "\"\
            } \
        ]\
    }\
  }"};

    if (create_manifest(manifest_path, manifest_content)) {
        auto manifest = parse_manifest(manifest_path);
        const auto* exec_man = manifest.get_execution();
        ASSERT_EQ(expected_manifest, *exec_man);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

TEST(AraExecParserParseManifest, ExecutionManifestStartupOptionsSectionMissingSuccess)
{
    const std::string manifest_path{"execution_manifest.json"};

    const std::string manifest_id{"test_app"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    // Prepare manifest content
    const std::string manifest_content{

        "{\"Application_manifest\": {\
        \"Application_manifest_id\": \"" +
        manifest_id +
        "\",\
        \"Process\": [ \
            { \
                \"Mode_dependent_startup_configs\": [ \
                    { \
                        \"Mode_in_machine_instance_refs\": [ \
                            { \
                                \"Function_group\": \"" +
        function_group +
        "\",\
                                \"Mode\": \"" +
        mode1 +
        "\"\
                            } \
                        ] \
                    } \
                ], \
                \"Process_name\": \"" +
        process_name +
        "\"\
            } \
        ]\
    }\
  }"};

    if (create_manifest(manifest_path, manifest_content)) {
        auto manifest = parse_manifest(manifest_path);
        const auto* exec_man = manifest.get_execution();
        ASSERT_EQ(expected_manifest, *exec_man);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

TEST(AraExecParserParseManifest, ExecutionManifestMachineInstanceRefsSuccess)
{
    const std::string manifest_path{"execution_manifest.json"};

    const std::string manifest_id{"test_app"};
    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string process_name{"Proc_1"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    config.startup_options.push_back(option);
    process.startup_configs.push_back(config);
    process.name = process_name;
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    // Prepare manifest content
    const std::string manifest_content{

        "{\"Application_manifest\": {\
        \"Application_manifest_id\": \"" +
        manifest_id +
        "\",\
        \"Process\": [ \
            { \
                \"Mode_dependent_startup_configs\": [ \
                    { \
                        \"Startup_options\": [ \
                            { \
                                \"Option_kind\": \"" +
        option_kind1 +
        "\",\
                                \"Option_name\": \"" +
        option_name1 +
        "\",\
                                \"Option_arg\": \"" +
        option_arg1 +
        "\"\
                            } \
                        ] \
                    } \
                ], \
                \"Process_name\": \"" +
        process_name +
        "\"\
            } \
        ]\
    }\
  }"};

    if (create_manifest(manifest_path, manifest_content)) {
        auto manifest = parse_manifest(manifest_path);
        const auto* exec_man = manifest.get_execution();
        ASSERT_EQ(expected_manifest, *exec_man);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

TEST(AraExecParserParseManifest, ExecutionManifestProcessNameMissingSuccess)
{
    const std::string manifest_path{"execution_manifest.json"};

    const std::string manifest_id{"test_app"};
    const std::string option_kind1{"commandLineShortForm"};
    const std::string option_name1{"name"};
    const std::string option_arg1{"as"};
    const std::string function_group{"MachineState"};
    const std::string mode1{"Running"};

    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    ExecutionManifest::Process process{};
    ExecutionManifest::Process::StartupConfig config{};
    ExecutionManifest::Process::StartupConfig::StartupOption option{option_kind1, option_name1,
                                                                    option_arg1};
    ExecutionManifest::Process::StartupConfig::MachineInstanceRef mach_inst_ref{function_group,
                                                                                mode1};
    config.startup_options.push_back(option);
    config.machine_instance_refs.push_back(mach_inst_ref);
    process.startup_configs.push_back(config);
    expected_manifest.processes.push_back(process);
    expected_manifest.manifest_id = manifest_id;

    // Prepare manifest content
    const std::string manifest_content{

        "{\"Application_manifest\": {\
        \"Application_manifest_id\": \"" +
        manifest_id +
        "\",\
        \"Process\": [ \
            { \
                \"Mode_dependent_startup_configs\": [ \
                    { \
                        \"Startup_options\": [ \
                            { \
                                \"Option_kind\": \"" +
        option_kind1 +
        "\",\
                                \"Option_name\": \"" +
        option_name1 +
        "\",\
                                \"Option_arg\": \"" +
        option_arg1 +
        "\"\
                            } \
                        ], \
                        \"Mode_in_machine_instance_refs\": [ \
                            { \
                                \"Function_group\": \"" +
        function_group +
        "\",\
                                \"Mode\": \"" +
        mode1 +
        "\"\
                            } \
                        ] \
                    } \
                ] \
            } \
        ]\
    }\
  }"};

    if (create_manifest(manifest_path, manifest_content)) {
        auto manifest = parse_manifest(manifest_path);
        const auto* exec_man = manifest.get_execution();
        ASSERT_EQ(expected_manifest, *exec_man);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

TEST(AraExecParserParseManifest, ExecutionManifestProcessSectionMissingSuccess)
{
    const std::string manifest_path{"execution_manifest.json"};

    const std::string manifest_id{"test_app"};
    // Prepare expected manifest object
    ExecutionManifest expected_manifest{};
    expected_manifest.manifest_id = manifest_id;

    // Prepare manifest content
    const std::string manifest_content{
        "{\"Application_manifest\": { \"Application_manifest_id\": \"" + manifest_id + "\"}}"};

    if (create_manifest(manifest_path, manifest_content)) {
        auto manifest = parse_manifest(manifest_path);
        const auto* exec_man = manifest.get_execution();
        ASSERT_EQ(expected_manifest, *exec_man);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

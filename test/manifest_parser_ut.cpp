#include <fstream>
#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "manifest_parser.h"

using namespace ara::exec::parser;

bool create_manifest(const std::string& path, const std::string& content)
{
    std::ofstream output(path, std::ofstream::binary);
    if (not output.is_open())
        return false;
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

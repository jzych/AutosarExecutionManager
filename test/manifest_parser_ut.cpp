#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
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

TEST(AraExecParserParseManifest, InvalidManifestFileExceptionThrown)
{
    const std::string manifest_path{"invalid_file.json"};  // not existing file
    EXPECT_THROW(parse_manifest(manifest_path), std::runtime_error);
}

TEST(AraExecParserParseManifest, EmptyManifestFileExceptionThrown)
{
    const std::string manifest_path{"empty_manifest.json"};  // empty file
    const std::string manifest_content{""};
    if (create_manifest(manifest_path, manifest_content)) {
        EXPECT_THROW(parse_manifest(manifest_path), std::runtime_error);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

TEST(AraExecParserParseManifest, UnknownManifestTypeExceptionThrown)
{
    const std::string manifest_path{"manifest_parser_unknown_type.json"};
    const std::string manifest_content{"{\"Unknown_manifest\":{}}"};
    if (create_manifest(manifest_path, manifest_content)) {
        EXPECT_THROW(parse_manifest(manifest_path), std::runtime_error);
    }
    else {
        ASSERT_TRUE(false) << "Unable to create test manifest";
    }
}

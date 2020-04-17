#include "gtest/gtest.h"
#include "manifest_parser.h"

using namespace ara::exec::parser;

TEST(ManifestParser, ExecutionManifestParserSuccess)
{
    ASSERT_EQ(ExecutionManifest(), parse_execution_manifest(""));
}

TEST(ManifestParser, MachineManifestParserSuccess)
{
    ASSERT_EQ(MachineManifest(), parse_machine_manifest(""));
}

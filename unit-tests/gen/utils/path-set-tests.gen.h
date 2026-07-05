#pragma once
#include "utils/path-set-tests.h"

TestState RunPathSetTests() 
 {
	auto className = "PathSetTests";
	auto testClass = std::make_shared<Soup::UnitTests::PathSetTests>();
	TestState state = { 0, 0 };
	state += Soup::Test::RunTest(className, "Serialize_Empty", [&testClass]() { testClass->Serialize_Empty(); });
	state += Soup::Test::RunTest(className, "Serialize_Single_Directory", [&testClass]() { testClass->Serialize_Single_Directory(); });
	state += Soup::Test::RunTest(className, "Serialize_Single_Directory_Long", [&testClass]() { testClass->Serialize_Single_Directory_Long(); });
	state += Soup::Test::RunTest(className, "Serialize_Single_File", [&testClass]() { testClass->Serialize_Single_File(); });
	state += Soup::Test::RunTest(className, "Serialize_Siblings", [&testClass]() { testClass->Serialize_Siblings(); });
	state += Soup::Test::RunTest(className, "Serialize_ParentChild", [&testClass]() { testClass->Serialize_ParentChild(); });
	state += Soup::Test::RunTest(className, "Deserialize_Empty", [&testClass]() { testClass->Deserialize_Empty(); });
	state += Soup::Test::RunTest(className, "Deserialize_Single_Directory", [&testClass]() { testClass->Deserialize_Single_Directory(); });
	state += Soup::Test::RunTest(className, "Deserialize_Single_Directory_Long", [&testClass]() { testClass->Deserialize_Single_Directory_Long(); });
	state += Soup::Test::RunTest(className, "Deserialize_Single_File", [&testClass]() { testClass->Deserialize_Single_File(); });
	state += Soup::Test::RunTest(className, "Deserialize_Siblings", [&testClass]() { testClass->Deserialize_Siblings(); });
	state += Soup::Test::RunTest(className, "Deserialize_ParentChild", [&testClass]() { testClass->Deserialize_ParentChild(); });
	
	return state;
}
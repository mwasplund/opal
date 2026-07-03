#pragma once
#include "utils/path-set-tests.h"

TestState RunPathSetTests() 
 {
	auto className = "PathSetTests";
	auto testClass = std::make_shared<Soup::UnitTests::PathSetTests>();
	TestState state = { 0, 0 };
	state += Soup::Test::RunTest(className, "Serialize_Empty", [&testClass]() { testClass->Serialize_Empty(); });
	state += Soup::Test::RunTest(className, "Serialize_Single", [&testClass]() { testClass->Serialize_Single(); });
	state += Soup::Test::RunTest(className, "Serialize_Siblings", [&testClass]() { testClass->Serialize_Siblings(); });
	state += Soup::Test::RunTest(className, "Serialize_ParentChild", [&testClass]() { testClass->Serialize_ParentChild(); });
	state += Soup::Test::RunTest(className, "Deserialize_Empty", [&testClass]() { testClass->Deserialize_Empty(); });
	state += Soup::Test::RunTest(className, "Deserialize_Single", [&testClass]() { testClass->Deserialize_Single(); });
	state += Soup::Test::RunTest(className, "Deserialize_Siblings", [&testClass]() { testClass->Deserialize_Siblings(); });
	state += Soup::Test::RunTest(className, "Deserialize_ParentChild", [&testClass]() { testClass->Deserialize_ParentChild(); });
	
	return state;
}
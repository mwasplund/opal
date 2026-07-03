#pragma once
#include "utils/path-set-tests.h"

TestState RunPathSetTests() 
 {
	auto className = "PathSetTests";
	auto testClass = std::make_shared<Soup::UnitTests::PathSetTests>();
	TestState state = { 0, 0 };
	state += Soup::Test::RunTest(className, "Serialize_Empty", [&testClass]() { testClass->Serialize_Empty(); });
	
	return state;
}
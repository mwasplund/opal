#pragma once
#include "utils/path-tests.h"

TestState RunPathTests() 
 {
	auto className = "PathTests";
	auto testClass = std::make_shared<Soup::UnitTests::PathTests>();
	TestState state = { 0, 0 };
	state += Soup::Test::RunTest(className, "Initialize_Default", [&testClass]() { testClass->Initialize_Default(); });
	// state += Soup::Test::RunTest(className, "Initialize_Empty", [&testClass]() { testClass->Initialize_Empty(); });
	state += Soup::Test::RunTest(className, "Initialize_RelativePath_Simple", [&testClass]() { testClass->Initialize_RelativePath_Simple(); });
	state += Soup::Test::RunTest(className, "Initialize_RelativePath_Parent", [&testClass]() { testClass->Initialize_RelativePath_Parent(); });
	state += Soup::Test::RunTest(className, "Initialize_RelativePath_Complex", [&testClass]() { testClass->Initialize_RelativePath_Complex(); });
	state += Soup::Test::RunTest(className, "Initialize_WindowsRoot", [&testClass]() { testClass->Initialize_WindowsRoot(); });
	state += Soup::Test::RunTest(className, "Initialize_LinuxRoot", [&testClass]() { testClass->Initialize_LinuxRoot(); });
	state += Soup::Test::RunTest(className, "Initialize_SimpleAbsolutePath", [&testClass]() { testClass->Initialize_SimpleAbsolutePath(); });
	state += Soup::Test::RunTest(className, "Parse_AlternativeDirectoriesPath", [&testClass]() { testClass->Parse_AlternativeDirectoriesPath(); });
	state += Soup::Test::RunTest(className, "Parse(\"C:/myfolder//file.txt\", \"C:/myfolder/file.txt\", true, true)", [&testClass]() { testClass->Parse("C:/myfolder//file.txt", "C:/myfolder/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "Parse(\"C:/myfolder/../file.txt\", \"C:/file.txt\", true, true)", [&testClass]() { testClass->Parse("C:/myfolder/../file.txt", "C:/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "Parse(\"C:/myfolder/myfolder2/../../file.txt\", \"C:/file.txt\", true, true)", [&testClass]() { testClass->Parse("C:/myfolder/myfolder2/../../file.txt", "C:/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "Parse(\"C:/myfolder/myfolder2/\", \"C:/myfolder/myfolder2/\", true, false)", [&testClass]() { testClass->Parse("C:/myfolder/myfolder2/", "C:/myfolder/myfolder2/", true, false); });
	state += Soup::Test::RunTest(className, "Parse(\"../file.txt\", \"../file.txt\", false, true)", [&testClass]() { testClass->Parse("../file.txt", "../file.txt", false, true); });
	state += Soup::Test::RunTest(className, "Parse(\"./file.txt\", \"./file.txt\", false, true)", [&testClass]() { testClass->Parse("./file.txt", "./file.txt", false, true); });
	state += Soup::Test::RunTest(className, "Parse(\"./\", \".\", false, false)", [&testClass]() { testClass->Parse("./", ".", false, false); });
	state += Soup::Test::RunTest(className, "Parse(\".\", \".\", false, false)", [&testClass]() { testClass->Parse(".", ".", false, false); });
	state += Soup::Test::RunTest(className, "Parse(\"../\", \"..\", false, false)", [&testClass]() { testClass->Parse("../", "..", false, false); });
	state += Soup::Test::RunTest(className, "Parse(\"..\", \"..\", false, false)", [&testClass]() { testClass->Parse("..", "..", false, false); });
	state += Soup::Test::RunTest(className, "Parse(\"../../\", \"../..\", false, false)", [&testClass]() { testClass->Parse("../../", "../..", false, false); });
	state += Soup::Test::RunTest(className, "Parse(\"../..\", \"../..\", false, false)", [&testClass]() { testClass->Parse("../..", "../..", false, false); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"C:/myfolder//file.txt\", \"C:/myfolder/file.txt\", true, true)", [&testClass]() { testClass->ParseRelaxed("C:/myfolder//file.txt", "C:/myfolder/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"C:/myfolder/../file.txt\", \"C:/file.txt\", true, true)", [&testClass]() { testClass->ParseRelaxed("C:/myfolder/../file.txt", "C:/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"C:/myfolder/myfolder2/../../file.txt\", \"C:/file.txt\", true, true)", [&testClass]() { testClass->ParseRelaxed("C:/myfolder/myfolder2/../../file.txt", "C:/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"C:/myfolder/myfolder2/\", \"C:/myfolder/myfolder2/\", true, false)", [&testClass]() { testClass->ParseRelaxed("C:/myfolder/myfolder2/", "C:/myfolder/myfolder2/", true, false); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"../file.txt\", \"../file.txt\", false, true)", [&testClass]() { testClass->ParseRelaxed("../file.txt", "../file.txt", false, true); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"./file.txt\", \"./file.txt\", false, true)", [&testClass]() { testClass->ParseRelaxed("./file.txt", "./file.txt", false, true); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\".\\../file.txt\", \"../file.txt\", false, true)", [&testClass]() { testClass->ParseRelaxed(".\\../file.txt", "../file.txt", false, true); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"./\", \".\", false, false)", [&testClass]() { testClass->ParseRelaxed("./", ".", false, false); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\".\", \".\", false, false)", [&testClass]() { testClass->ParseRelaxed(".", ".", false, false); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"../\", \"..\", false, false)", [&testClass]() { testClass->ParseRelaxed("../", "..", false, false); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"..\", \"..\", false, false)", [&testClass]() { testClass->ParseRelaxed("..", "..", false, false); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"../..\\\", \"../..\", false, false)", [&testClass]() { testClass->ParseRelaxed("../..\\", "../..", false, false); });
	state += Soup::Test::RunTest(className, "ParseRelaxed(\"../..\", \"../..\", false, false)", [&testClass]() { testClass->ParseRelaxed("../..", "../..", false, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"C:\\myfolder\\\\file.txt\", \"C:/myfolder\\file.txt\", true, true)", [&testClass]() { testClass->ParseWindows("C:\\myfolder\\\\file.txt", "C:/myfolder/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"C:\\myfolder\\..\\file.txt\", \"C:/file.txt\", true, true)", [&testClass]() { testClass->ParseWindows("C:\\myfolder\\..\\file.txt", "C:/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"C:\\myfolder\\myfolder2\\..\\..\\file.txt\", \"C:/file.txt\", true, true)", [&testClass]() { testClass->ParseWindows("C:\\myfolder\\myfolder2\\..\\..\\file.txt", "C:/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"C:\\myfolder\\myfolder2\\\", \"C:/myfolder/myfolder2/\", true, false)", [&testClass]() { testClass->ParseWindows("C:\\myfolder\\myfolder2\\", "C:/myfolder/myfolder2/", true, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"..\\file.txt\", \"../file.txt\", false, true)", [&testClass]() { testClass->ParseWindows("..\\file.txt", "../file.txt", false, true); });
	state += Soup::Test::RunTest(className, "ParseWindows(\".\\file.txt\", \"./file.txt\", false, true)", [&testClass]() { testClass->ParseWindows(".\\file.txt", "./file.txt", false, true); });
	state += Soup::Test::RunTest(className, "ParseWindows(\".\\\", \".\", false, false)", [&testClass]() { testClass->ParseWindows(".\\", ".", false, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\".\", \".\", false, false)", [&testClass]() { testClass->ParseWindows(".", ".", false, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"..\\\", \"..\", false, false)", [&testClass]() { testClass->ParseWindows("..\\", "..", false, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"..\", \"..\", false, false)", [&testClass]() { testClass->ParseWindows("..", "..", false, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"..\\..\\\", \"../..\", false, false)", [&testClass]() { testClass->ParseWindows("..\\..\\", "../..", false, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"..\\..\", \"../..\", false, false)", [&testClass]() { testClass->ParseWindows("..\\..", "../..", false, false); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"\\\\?\\C:\\myfolder\\\\file.txt\", \"C:\\myfolder\\file.txt\", true, true)", [&testClass]() { testClass->ParseWindows("\\\\?\\C:\\myfolder\\\\file.txt", "C:/myfolder/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "ParseWindows(\"\\\\.\\C:\\myfolder\\\\file.txt\", \"C:\\myfolder\\file.txt\", true, true)", [&testClass]() { testClass->ParseWindows("\\\\.\\C:\\myfolder\\\\file.txt", "C:/myfolder/file.txt", true, true); });
	state += Soup::Test::RunTest(className, "Concatenate(\"C:/MyRootFolder/\", \"./MyFolder/MyFile.txt\", \"C:/MyRootFolder/MyFolder/MyFile.txt\")", [&testClass]() { testClass->Concatenate("C:/MyRootFolder/", "./MyFolder/MyFile.txt", "C:/MyRootFolder/MyFolder/MyFile.txt"); });
	state += Soup::Test::RunTest(className, "Concatenate(\"C:/MyRootFolder/\", \"./MyFolder/\", \"C:/MyRootFolder/MyFolder/\")", [&testClass]() { testClass->Concatenate("C:/MyRootFolder/", "./MyFolder/", "C:/MyRootFolder/MyFolder/"); });
	state += Soup::Test::RunTest(className, "Concatenate(\"C:/MyRootFolder/\", \".\", \"C:/MyRootFolder/\")", [&testClass]() { testClass->Concatenate("C:/MyRootFolder/", ".", "C:/MyRootFolder/"); });
	state += Soup::Test::RunTest(className, "Concatenate(\"C:/\", \"./MyFile.txt\", \"C:/MyFile.txt\")", [&testClass]() { testClass->Concatenate("C:/", "./MyFile.txt", "C:/MyFile.txt"); });
	state += Soup::Test::RunTest(className, "Concatenate(\"C:/\", \"./MyFolder/\", \"C:/MyFolder/\")", [&testClass]() { testClass->Concatenate("C:/", "./MyFolder/", "C:/MyFolder/"); });
	state += Soup::Test::RunTest(className, "Concatenate(\"C:/MyRootFolder/\", \"../NewRoot/MyFile.txt\", \"C:/NewRoot/MyFile.txt\")", [&testClass]() { testClass->Concatenate("C:/MyRootFolder/", "../NewRoot/MyFile.txt", "C:/NewRoot/MyFile.txt"); });
	state += Soup::Test::RunTest(className, "Concatenate(\"./Folder1/\", \"./Other/MyFile.txt\", \"./Folder1/Other/MyFile.txt\")", [&testClass]() { testClass->Concatenate("./Folder1/", "./Other/MyFile.txt", "./Folder1/Other/MyFile.txt"); });
	state += Soup::Test::RunTest(className, "Concatenate(\"../MyRootFolder/\", \"../NewRoot/MyFile.txt\", \"../NewRoot/MyFile.txt\")", [&testClass]() { testClass->Concatenate("../MyRootFolder/", "../NewRoot/MyFile.txt", "../NewRoot/MyFile.txt"); });
	state += Soup::Test::RunTest(className, "SetFileExtension(\"../MyFile.txt\", \"awe\", \"../MyFile.awe\")", [&testClass]() { testClass->SetFileExtension("../MyFile.txt", "awe", "../MyFile.awe"); });
	state += Soup::Test::RunTest(className, "SetFileExtension(\"C:/MyFolder/MyFile.txt\", \"awe\", \"C:/MyFolder/MyFile.awe\")", [&testClass]() { testClass->SetFileExtension("C:/MyFolder/MyFile.txt", "awe", "C:/MyFolder/MyFile.awe"); });
	state += Soup::Test::RunTest(className, "SetFileExtension(\"../MyFile\", \"awe\", \"../MyFile.awe\")", [&testClass]() { testClass->SetFileExtension("../MyFile", "awe", "../MyFile.awe"); });
	state += Soup::Test::RunTest(className, "GetRelativeTo(\"./File.txt\", \".\", \"./File.txt\")", [&testClass]() { testClass->GetRelativeTo("./File.txt", ".", "./File.txt"); });
	state += Soup::Test::RunTest(className, "GetRelativeTo(\"./Folder/File.txt\", \"./Folder/\", \"./File.txt\")", [&testClass]() { testClass->GetRelativeTo("./Folder/File.txt", "./Folder/", "./File.txt"); });
	state += Soup::Test::RunTest(className, "GetRelativeTo(\"../Folder/Target\", \"../Folder/\", \"./Target\")", [&testClass]() { testClass->GetRelativeTo("../Folder/Target", "../Folder/", "./Target"); });
	state += Soup::Test::RunTest(className, "GetRelativeTo(\"./Folder1/File.txt\", \"./Folder2/\", \"../Folder1/File.txt\")", [&testClass]() { testClass->GetRelativeTo("./Folder1/File.txt", "./Folder2/", "../Folder1/File.txt"); });
	state += Soup::Test::RunTest(className, "GetRelativeTo(\"C:/Folder1/File.txt\", \"D:/Folder1/\", \"C:/Folder1/File.txt\")", [&testClass]() { testClass->GetRelativeTo("C:/Folder1/File.txt", "D:/Folder1/", "C:/Folder1/File.txt"); });
	state += Soup::Test::RunTest(className, "GetRelativeTo(\"C:/Folder1/File.txt\", \"C:/Folder1/\", \"./File.txt\")", [&testClass]() { testClass->GetRelativeTo("C:/Folder1/File.txt", "C:/Folder1/", "./File.txt"); });

	return state;
}
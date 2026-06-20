// <copyright file="path-tests.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once

namespace Soup::UnitTests
{
	class PathTests
	{
	public:
		// [[Fact]]
		void Initialize_Default()
		{
			auto uut = Path();
			Assert::IsFalse(uut.HasRoot(), "Verify is no root.");
			Assert::IsFalse(uut.HasFileName(), "Verify has no filename.");
			Assert::IsFalse(uut.HasFileStem(), "Verify has no file stem.");
			Assert::IsFalse(uut.HasFileExtension(), "Verify has no file extension.");
			Assert::AreEqual(".", uut.ToString(), "Verify string value matches.");
			Assert::AreEqual(".", uut.ToAlternateString(), "Verify alternate string value matches.");
		}

		// [[Fact]]
		void Initialize_Empty()
		{
			auto exception = Assert::Throws<std::runtime_error>([&]()
			{
				auto uut = Path("");
			});
			Assert::AreEqual("A path must have a directory separator", exception.what(), "Verify exception value matches.");
		}

		// [[Fact]]
		void Initialize_RelativePath_Simple()
		{
			auto uut = Path(".");
			Assert::IsFalse(uut.HasRoot(), "Verify is no root.");
			Assert::IsFalse(uut.HasFileName(), "Verify has filename.");
			Assert::IsFalse(uut.HasFileStem(), "Verify has file stem.");
			Assert::IsFalse(uut.HasFileExtension(), "Verify has file extension.");
			Assert::AreEqual(".", uut.ToString(), "Verify string value matches.");
			Assert::AreEqual(".", uut.ToAlternateString(), "Verify alternate string value matches.");
		}

		// [[Fact]]
		void Initialize_RelativePath_Parent()
		{
			auto uut = Path("..");
			Assert::IsFalse(uut.HasRoot(), "Verify is no root.");
			Assert::IsFalse(uut.HasFileName(), "Verify has filename.");
			Assert::IsFalse(uut.HasFileStem(), "Verify has file stem.");
			Assert::IsFalse(uut.HasFileExtension(), "Verify has file extension.");
			Assert::AreEqual("..", uut.ToString(), "Verify string value matches.");
			Assert::AreEqual("..", uut.ToAlternateString(), "Verify alternate string value matches.");
		}

		// [[Fact]]
		void Initialize_RelativePath_Complex()
		{
			auto uut = Path("./myfolder/anotherfolder/file.txt");
			Assert::IsFalse(uut.HasRoot(), "Verify is no root.");
			Assert::IsTrue(uut.HasFileName(), "Verify has filename.");
			Assert::AreEqual("file.txt", uut.GetFileName(), "Verify file name matches.");
			Assert::IsTrue(uut.HasFileStem(), "Verify has file stem.");
			Assert::AreEqual("file", uut.GetFileStem(), "Verify file stem matches.");
			Assert::IsTrue(uut.HasFileExtension(), "Verify has file extension.");
			Assert::AreEqual(".txt", uut.GetFileExtension(), "Verify file extension matches.");
			Assert::AreEqual("./myfolder/anotherfolder/file.txt", uut.ToString(), "Verify string value matches.");
			Assert::AreEqual(".\\myfolder\\anotherfolder\\file.txt", uut.ToAlternateString(), "Verify alternate string value matches.");
		}

		// [[Fact]]
		void Initialize_WindowsRoot()
		{
			auto uut = Path("C:/");
			Assert::IsTrue(uut.HasRoot(), "Verify has root.");
			Assert::AreEqual("C:", uut.GetRoot(), "Verify root matches.");
			Assert::IsFalse(uut.HasFileName(), "Verify has no filename.");
			Assert::IsFalse(uut.HasFileStem(), "Verify has no file stem.");
			Assert::IsFalse(uut.HasFileExtension(), "Verify has no file extension.");
			Assert::AreEqual("C:/", uut.ToString(), "Verify string value matches.");
			Assert::AreEqual("C:\\", uut.ToAlternateString(), "Verify alternate string value matches.");
		}

		// [[Fact]]
		void Initialize_LinuxRoot()
		{
			auto uut = Path("/");
			Assert::IsTrue(uut.HasRoot(), "Verify has root.");
			Assert::AreEqual("", uut.GetRoot(), "Verify root matches.");
			Assert::IsFalse(uut.HasFileName(), "Verify has no filename.");
			Assert::IsFalse(uut.HasFileStem(), "Verify has no file stem.");
			Assert::IsFalse(uut.HasFileExtension(), "Verify has no file extension.");
			Assert::AreEqual("/", uut.ToString(), "Verify string value matches.");
			Assert::AreEqual("\\", uut.ToAlternateString(), "Verify alternate string value matches.");
		}

		// [[Fact]]
		void Initialize_SimpleAbsolutePath()
		{
			auto uut = Path("C:/myfolder/anotherfolder/file.txt");
			Assert::IsTrue(uut.HasRoot(), "Verify is root.");
			Assert::AreEqual("C:", uut.GetRoot(), "Verify root matches.");
			Assert::IsTrue(uut.HasFileName(), "Verify has filename.");
			Assert::AreEqual("file.txt", uut.GetFileName(), "Verify file name matches.");
			Assert::IsTrue(uut.HasFileStem(), "Verify has file stem.");
			Assert::AreEqual("file", uut.GetFileStem(), "Verify file stem matches.");
			Assert::IsTrue(uut.HasFileExtension(), "Verify has file extension.");
			Assert::AreEqual(".txt", uut.GetFileExtension(), "Verify file extension matches.");
			Assert::AreEqual("C:/myfolder/anotherfolder/file.txt", uut.ToString(), "Verify string value matches.");
		}

		// [[Fact]]
		void Parse_AlternativeDirectoriesPath()
		{
			auto uut = Path::ParseRelaxed("C:\\myfolder/anotherfolder\\file.txt");
			Assert::IsTrue(uut.HasRoot(), "Verify is root.");
			Assert::AreEqual("C:", uut.GetRoot(), "Verify root matches.");
			Assert::IsTrue(uut.HasFileName(), "Verify has filename.");
			Assert::AreEqual("file.txt", uut.GetFileName(), "Verify file name matches.");
			Assert::IsTrue(uut.HasFileStem(), "Verify has file stem.");
			Assert::AreEqual("file", uut.GetFileStem(), "Verify file stem matches.");
			Assert::IsTrue(uut.HasFileExtension(), "Verify has file extension.");
			Assert::AreEqual(".txt", uut.GetFileExtension(), "Verify file extension matches.");
			Assert::AreEqual("C:/myfolder/anotherfolder/file.txt", uut.ToString(), "Verify string value matches.");
		}

		// [[Theory]]
		// [[InlineData("C:/myfolder//file.txt", "C:/myfolder/file.txt", true, true)]]
		// [[InlineData("C:/myfolder/../file.txt", "C:/file.txt", true, true)]]
		// [[InlineData("C:/myfolder/myfolder2/../../file.txt", "C:/file.txt", true, true)]]
		// [[InlineData("C:/myfolder/myfolder2/", "C:/myfolder/myfolder2/", true, false)]]
		// [[InlineData("../file.txt", "../file.txt", false, true)]]
		// [[InlineData("./file.txt", "./file.txt", false, true)]]
		// [[InlineData("./", ".", false, false)]]
		// [[InlineData(".", ".", false, false)]]
		// [[InlineData("../", "..", false, false)]]
		// [[InlineData("..", "..", false, false)]]
		// [[InlineData("../../", "../..", false, false)]]
		// [[InlineData("../..", "../..", false, false)]]
		void Parse(std::string_view input, std::string_view expected, bool hasRoot, bool hasFileName)
		{
			auto uut = Path::Parse(input);
			Assert::AreEqual(expected, uut.ToString(), "Verify string value matches.");
			Assert::AreEqual(uut.HasRoot(), hasRoot, "Verify is root.");
			Assert::AreEqual(uut.HasFileName(), hasFileName, "Verify has filename.");
		}

		// [[Theory]]
		// [[InlineData("C:/myfolder//file.txt", "C:/myfolder/file.txt", true, true)]]
		// [[InlineData("C:/myfolder/../file.txt", "C:/file.txt", true, true)]]
		// [[InlineData("C:/myfolder/myfolder2/../../file.txt", "C:/file.txt", true, true)]]
		// [[InlineData("C:/myfolder/myfolder2/", "C:/myfolder/myfolder2/", true, false)]]
		// [[InlineData("../file.txt", "../file.txt", false, true)]]
		// [[InlineData("./file.txt", "./file.txt", false, true)]]
		// [[InlineData(".\\../file.txt", "../file.txt", false, true)]]
		// [[InlineData("./", ".", false, false)]]
		// [[InlineData(".", ".", false, false)]]
		// [[InlineData("../", "..", false, false)]]
		// [[InlineData("..", "..", false, false)]]
		// [[InlineData("../..\\", "../..", false, false)]]
		// [[InlineData("../..", "../..", false, false)]]
		void ParseRelaxed(std::string_view input, std::string_view expected, bool hasRoot, bool hasFileName)
		{
			auto uut = Path::ParseRelaxed(input);
			Assert::AreEqual(expected, uut.ToString(), "Verify string value matches.");
			Assert::AreEqual(uut.HasRoot(), hasRoot, "Verify is root.");
			Assert::AreEqual(uut.HasFileName(), hasFileName, "Verify has filename.");
		}

		// [[Theory]]
		// [[InlineData("C:\\myfolder\\file.txt", "C:/myfolder/file.txt", true, true)]]
		// [[InlineData("C:\\myfolder\\..\\file.txt", "C:/file.txt", true, true)]]
		// [[InlineData("C:\\myfolder\\myfolder2\\..\\..\\file.txt", "C:/file.txt", true, true)]]
		// [[InlineData("C:\\myfolder\\myfolder2\\", "C:/myfolder/myfolder2/", true, false)]]
		// [[InlineData("..\\file.txt", "../file.txt", false, true)]]
		// [[InlineData(".\\file.txt", "./file.txt", false, true)]]
		// [[InlineData(".\\..\\file.txt", "../file.txt", false, true)]]
		// [[InlineData(".\\", ".", false, false)]]
		// [[InlineData(".", ".", false, false)]]
		// [[InlineData("..\\", "..", false, false)]]
		// [[InlineData("..", "..", false, false)]]
		// [[InlineData("..\\..\\", "../..", false, false)]]
		// [[InlineData("..\\..", "../..", false, false)]]
		// [[InlineData("\\\\?\\C:\\myfolder\\file.txt", "C:/myfolder/file.txt", true, true)]]
		// [[InlineData("\\\\.\\C:\\myfolder\\file.txt", "C:/myfolder/file.txt", true, true)]]
		void ParseWindows(std::string_view input, std::string_view expected, bool hasRoot, bool hasFileName)
		{
			auto uut = Path::ParseWindows(input);
			Assert::AreEqual(expected, uut.ToString(), "Verify string value matches.");
			Assert::AreEqual(uut.HasRoot(), hasRoot, "Verify is root.");
			Assert::AreEqual(uut.HasFileName(), hasFileName, "Verify has filename.");
		}

		// [[Theory]]
		// [[InlineData("C:/MyRootFolder/", "./MyFolder/MyFile.txt", "C:/MyRootFolder/MyFolder/MyFile.txt")]]
		// [[InlineData("C:/MyRootFolder/", "./MyFolder/", "C:/MyRootFolder/MyFolder/")]]
		// [[InlineData("C:/MyRootFolder/", ".", "C:/MyRootFolder/")]]
		// [[InlineData("C:/", "./MyFile.txt", "C:/MyFile.txt")]]
		// [[InlineData("C:/", "./MyFolder/", "C:/MyFolder/")]]
		// [[InlineData("C:/MyRootFolder/", "../NewRoot/MyFile.txt", "C:/NewRoot/MyFile.txt")]]
		// [[InlineData("./Folder1/", "./Other/MyFile.txt", "./Folder1/Other/MyFile.txt")]]
		// [[InlineData("../MyRootFolder/", "../NewRoot/MyFile.txt", "../NewRoot/MyFile.txt")]]
		void Concatenate(std::string_view lhs, std::string_view rhs, std::string_view expected)
		{
			auto path1 = Path(lhs);
			auto path2 = Path(rhs);
			auto uut = path1 + path2;

			Assert::AreEqual(expected, uut.ToString(), "Verify value matches.");
		}

		// [[Theory]]
		// [[InlineData("../MyFile.txt", "awe", "../MyFile.awe")]]
		// [[InlineData("C:/MyFolder/MyFile.txt", "awe", "C:/MyFolder/MyFile.awe")]]
		// [[InlineData("../MyFile", "awe", "../MyFile.awe")]]
		void SetFileExtension(std::string_view file, std::string_view extension, std::string_view expected)
		{
			auto uut = Path(file);
			uut.SetFileExtension(extension);

			Assert::AreEqual(expected, uut.ToString(), "Verify value matches.");
		}

		// [[Theory]]
		// [[InlineData("./File.txt", ".", "./File.txt")]]
		// [[InlineData("./Folder/File.txt", "./Folder/", "./File.txt")]]
		// [[InlineData("../Folder/Target", "../Folder/", "./Target")]]
		// [[InlineData("./Folder1/File.txt", "./Folder2/", "../Folder1/File.txt")]]
		// [[InlineData("C:/Folder1/File.txt", "D:/Folder1/", "C:/Folder1/File.txt")]]
		// [[InlineData("C:/Folder1/File.txt", "C:/Folder1/", "./File.txt")]]
		void GetRelativeTo(std::string_view path, std::string_view base, std::string_view expected)
		{
			auto uut = Path(path);
			auto basePath = Path(base);

			auto result = uut.GetRelativeTo(basePath);

			Assert::AreEqual(expected, result.ToString(), "Verify result matches.");
		}
	};
}

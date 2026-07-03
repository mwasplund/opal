// <copyright file="path-tests.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace Soup::UnitTests
{
	class PathSetTests
	{
	public:
		// [[Fact]]
		void Serialize_Empty()
		{
			auto set = std::vector<Path>();
			auto uut = PathSet::Build(set);
			
			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x00, 0x00, 0x00, 0x00,
			});
			Assert::AreEqual(
				std::string((char *)expected.data(), expected.size()),
				actual.str(),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Serialize_Single()
		{
			auto set = std::vector<Path>({
				Path("C:/test/"),
			});
			auto uut = PathSet::Build(set);
			
			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x01, 0x00, 0x00, 0x00,
				0x02, 0x00, 0x00, 0x00, 'C', ':',
				0x01, 0x00, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x00, 't', 'e', 's', 't',
				0x00, 0x00, 0x00, 0x00,
			});
			Assert::AreEqual(
				std::string((char *)expected.data(), expected.size()),
				actual.str(),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Serialize_Siblings()
		{
			auto set = std::vector<Path>({
				Path("C:/test/folder1/"),
				Path("C:/test/folder2/"),
			});
			auto uut = PathSet::Build(set);
			
			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x01, 0x00, 0x00, 0x00,
				0x02, 0x00, 0x00, 0x00, 'C', ':',
				0x01, 0x00, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x00, 't', 'e', 's', 't',
				0x02, 0x00, 0x00, 0x00,
				0x07, 0x00, 0x00, 0x00, 'f', 'o', 'l', 'd', 'e', 'r', '2',
				0x00, 0x00, 0x00, 0x00,
				0x07, 0x00, 0x00, 0x00, 'f', 'o', 'l', 'd', 'e', 'r', '1',
				0x00, 0x00, 0x00, 0x00,

			});
			Assert::AreEqual(
				std::string((char *)expected.data(), expected.size()),
				actual.str(),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Deserialize_Empty()
		{
			auto input = std::vector<uint8_t>({
				0x00, 0x00, 0x00, 0x00,
			});

			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>();

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Deserialize_Single()
		{
			auto input = std::vector<uint8_t>({
				0x01, 0x00, 0x00, 0x00,
				0x02, 0x00, 0x00, 0x00, 'C', ':',
				0x01, 0x00, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x00, 't', 'e', 's', 't',
				0x00, 0x00, 0x00, 0x00,
			});
	
			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>({
				Path("C:/test/"),
			});

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Deserialize_Siblings()
		{
			auto input = std::vector<uint8_t>({
				0x01, 0x00, 0x00, 0x00,
				0x02, 0x00, 0x00, 0x00, 'C', ':',
				0x01, 0x00, 0x00, 0x00,
				0x04, 0x00, 0x00, 0x00, 't', 'e', 's', 't',
				0x02, 0x00, 0x00, 0x00,
				0x07, 0x00, 0x00, 0x00, 'f', 'o', 'l', 'd', 'e', 'r', '2',
				0x00, 0x00, 0x00, 0x00,
				0x07, 0x00, 0x00, 0x00, 'f', 'o', 'l', 'd', 'e', 'r', '1',
				0x00, 0x00, 0x00, 0x00,
			});

			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>({
				Path("C:/test/folder1/"),
				Path("C:/test/folder2/"),
			});

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify file content match expected.");
		}
	};
}

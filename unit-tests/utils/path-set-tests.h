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
			auto set = std::vector<Path>({});
			auto uut = PathSet::Build(set);

			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x00,
			});
			Assert::AreEqual(
				ToHex(std::string((char *)expected.data(), expected.size())),
				ToHex(actual.str()),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Serialize_Single_Directory()
		{
			auto set = std::vector<Path>({
				Path("C:/test/"),
			});
			auto uut = PathSet::Build(set);
			
			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x03,
				0x04, 't', 'e', 's', 't',
				0x00,
			});
			Assert::AreEqual(
				ToHex(std::string((char *)expected.data(), expected.size())),
				ToHex(actual.str()),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Serialize_Single_Directory_Long()
		{
			auto set = std::vector<Path>({
				Path("C:/this_is_a_very_long_directory_to_test_var_int_expansion_this_is_a_very_long_directory_to_test_var_int_expansion_this_is_a_very_long_directory_to_test_var_int_expansion/"),
			});
			auto uut = PathSet::Build(set);
			
			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x03,
				0xA7, 0x01,
				't', 'h', 'i', 's', '_', 'i', 's', '_', 'a', '_', 'v', 'e', 'r', 'y', '_', 'l', 'o', 'n', 'g', '_', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '_', 't', 'o', '_', 't', 'e', 's', 't', '_', 'v', 'a', 'r', '_', 'i', 'n', 't', '_', 'e', 'x', 'p', 'a', 'n', 's', 'i', 'o', 'n', '_',
				't', 'h', 'i', 's', '_', 'i', 's', '_', 'a', '_', 'v', 'e', 'r', 'y', '_', 'l', 'o', 'n', 'g', '_', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '_', 't', 'o', '_', 't', 'e', 's', 't', '_', 'v', 'a', 'r', '_', 'i', 'n', 't', '_', 'e', 'x', 'p', 'a', 'n', 's', 'i', 'o', 'n', '_',
				't', 'h', 'i', 's', '_', 'i', 's', '_', 'a', '_', 'v', 'e', 'r', 'y', '_', 'l', 'o', 'n', 'g', '_', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '_', 't', 'o', '_', 't', 'e', 's', 't', '_', 'v', 'a', 'r', '_', 'i', 'n', 't', '_', 'e', 'x', 'p', 'a', 'n', 's', 'i', 'o', 'n',
				0x00,
			});
			Assert::AreEqual(
				ToHex(std::string((char *)expected.data(), expected.size())),
				ToHex(actual.str()),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Serialize_Single_File()
		{
			auto set = std::vector<Path>({
				Path("C:/test/file.txt"),
			});
			auto uut = PathSet::Build(set);
			
			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x01,
				0x04, 't', 'e', 's', 't',
				0x01,
				0x02,
				0x08, 'f', 'i', 'l', 'e', '.', 't', 'x', 't',
			});
			Assert::AreEqual(
				ToHex(std::string((char *)expected.data(), expected.size())),
				ToHex(actual.str()),
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
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x01,
				0x04, 't', 'e', 's', 't',
				0x02,
				0x03,
				0x07, 'f', 'o', 'l', 'd', 'e', 'r', '2',
				0x00,
				0x03,
				0x07, 'f', 'o', 'l', 'd', 'e', 'r', '1',
				0x00,
			});
			Assert::AreEqual(
				ToHex(std::string((char *)expected.data(), expected.size())),
				ToHex(actual.str()),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Serialize_ParentChild()
		{
			auto set = std::vector<Path>({
				Path("C:/parent/"),
				Path("C:/parent/child/"),
			});
			auto uut = PathSet::Build(set);
			
			auto actual = std::stringstream();
			uut.Serialize(actual);

			auto expected = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x03,
				0x06, 'p', 'a', 'r', 'e', 'n', 't',
				0x01,
				0x03,
				0x05, 'c', 'h', 'i', 'l', 'd',
				0x00,
			});
			Assert::AreEqual(
				ToHex(std::string((char *)expected.data(), expected.size())),
				ToHex(actual.str()),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Deserialize_Empty()
		{
			auto input = std::vector<uint8_t>({
				0x00,
			});

			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>();

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify file content match expected.");
		}

		// [[Fact]]
		void Deserialize_Single_Directory()
		{
			auto input = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x03,
				0x04, 't', 'e', 's', 't',
				0x00,
			});
	
			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>({
				Path("C:/test/"),
			});

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify result matches expected.");
		}

		// [[Fact]]
		void Deserialize_Single_Directory_Long()
		{
			auto input = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x03,
				0xA7, 0x01,
				't', 'h', 'i', 's', '_', 'i', 's', '_', 'a', '_', 'v', 'e', 'r', 'y', '_', 'l', 'o', 'n', 'g', '_', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '_', 't', 'o', '_', 't', 'e', 's', 't', '_', 'v', 'a', 'r', '_', 'i', 'n', 't', '_', 'e', 'x', 'p', 'a', 'n', 's', 'i', 'o', 'n', '_',
				't', 'h', 'i', 's', '_', 'i', 's', '_', 'a', '_', 'v', 'e', 'r', 'y', '_', 'l', 'o', 'n', 'g', '_', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '_', 't', 'o', '_', 't', 'e', 's', 't', '_', 'v', 'a', 'r', '_', 'i', 'n', 't', '_', 'e', 'x', 'p', 'a', 'n', 's', 'i', 'o', 'n', '_',
				't', 'h', 'i', 's', '_', 'i', 's', '_', 'a', '_', 'v', 'e', 'r', 'y', '_', 'l', 'o', 'n', 'g', '_', 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', '_', 't', 'o', '_', 't', 'e', 's', 't', '_', 'v', 'a', 'r', '_', 'i', 'n', 't', '_', 'e', 'x', 'p', 'a', 'n', 's', 'i', 'o', 'n',
				0x00,
			});
	
			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>({
				Path("C:/this_is_a_very_long_directory_to_test_var_int_expansion_this_is_a_very_long_directory_to_test_var_int_expansion_this_is_a_very_long_directory_to_test_var_int_expansion/"),
			});

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify result matches expected.");
		}

		// [[Fact]]
		void Deserialize_Single_File()
		{
			auto input = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x01,
				0x04, 't', 'e', 's', 't',
				0x01,
				0x02,
				0x08, 'f', 'i', 'l', 'e', '.', 't', 'x', 't',
			});
	
			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>({
				Path("C:/test/file.txt"),
			});

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify result matches expected.");
		}

		// [[Fact]]
		void Deserialize_Siblings()
		{
			auto input = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x01,
				0x04, 't', 'e', 's', 't',
				0x02,
				0x03,
				0x07, 'f', 'o', 'l', 'd', 'e', 'r', '2',
				0x00,
				0x03,
				0x07, 'f', 'o', 'l', 'd', 'e', 'r', '1',
				0x00,
			});

			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>({
				Path("C:/test/folder2/"),
				Path("C:/test/folder1/"),
			});

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify result matches expected.");
		}
		
		// [[Fact]]
		void Deserialize_ParentChild()
		{
			auto input = std::vector<uint8_t>({
				0x01,
				0x01,
				0x02, 'C', ':',
				0x01,
				0x03,
				0x06, 'p', 'a', 'r', 'e', 'n', 't',
				0x01,
				0x03,
				0x05, 'c', 'h', 'i', 'l', 'd',
				0x00,
			});

			auto uut = PathSet::Deserialize(reinterpret_cast<char *>(input.data()), input.size());
			
			auto expected = std::vector<Path>({
				Path("C:/parent/child/"),
				Path("C:/parent/"),
			});

			Assert::AreEqual(
				expected,
				uut.GetPaths(),
				"Verify result matches expected.");
		}
		
	private:
		std::string ToHex(const std::string& s, bool upper_case = true) {
			std::ostringstream ret;
			for (std::string::size_type i = 0; i < s.length(); ++i) {
				int z = static_cast<unsigned char>(s[i]) & 0xff;
				ret << std::hex << std::setfill('0') << std::setw(2) 
					<< (upper_case ? std::uppercase : std::nouppercase) << z;
			}
			return ret.str();
		}
	};
}

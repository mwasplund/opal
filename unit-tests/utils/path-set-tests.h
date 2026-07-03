// <copyright file="path-tests.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once

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
	};
}

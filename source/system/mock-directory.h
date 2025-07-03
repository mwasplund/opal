// <copyright file="mock-directory.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once
#include "i-file-system.h"

namespace Opal::System
{
	export class MockDirectory
	{
	public:
		MockDirectory(std::vector<Path> children, std::filesystem::file_time_type lastWriteTime) :
			Children(std::move(children)),
			LastWriteTime(lastWriteTime)
		{
		}

		MockDirectory(std::vector<Path> children) :
			Children(std::move(children)),
			LastWriteTime()
		{
		}

		MockDirectory(std::filesystem::file_time_type lastWriteTime) :
			Children(),
			LastWriteTime(lastWriteTime)
		{
		}

		MockDirectory() :
			Children(),
			LastWriteTime()
		{
		}

		std::vector<Path> Children;
		std::filesystem::file_time_type LastWriteTime;
	};
}

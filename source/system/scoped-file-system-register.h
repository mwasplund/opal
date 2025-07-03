// <copyright file="scoped-file-system-register.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once
#include "i-file-system.h"

namespace Opal::System
{
	/// <summary>
	/// A scoped file system registration helper
	/// </summary>
	export class ScopedFileSystemRegister
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='ScopedFileSystemRegister'/> class.
		/// </summary>
		ScopedFileSystemRegister(std::shared_ptr<IFileSystem> listener)
		{
			IFileSystem::Register(std::move(listener));
		}

		/// <summary>
		/// Finalizes an instance of the <see cref='ScopedFileSystemRegister'/> class.
		/// </summary>
		~ScopedFileSystemRegister()
		{
			IFileSystem::Register(nullptr);
		}
	};
}

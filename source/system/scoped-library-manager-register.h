// <copyright file="scoped-library-manager-register.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once
#include "i-library-manager.h"

namespace Opal::System
{
	/// <summary>
	/// A scoped library manager registration helper
	/// </summary>
	export class ScopedLibraryManagerRegister
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='ScopedLibraryManagerRegister'/> class.
		/// </summary>
		ScopedLibraryManagerRegister(std::shared_ptr<ILibraryManager> listener)
		{
			ILibraryManager::Register(std::move(listener));
		}

		/// <summary>
		/// Finalizes an instance of the <see cref='ScopedLibraryManagerRegister'/> class.
		/// </summary>
		~ScopedLibraryManagerRegister()
		{
			ILibraryManager::Register(nullptr);
		}
	};
}

// <copyright file="scoped-library-manager-register.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <memory>
export module Opal:ScopedLibraryManagerRegister;
import :ILibraryManager;

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

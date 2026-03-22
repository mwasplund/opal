// <copyright file="i-input-file.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

export module Opal:IInputFile;
import :IFile;

namespace Opal::System
{
	/// <summary>
	/// The input file interface
	/// Interface mainly used to allow for unit testing client code
	/// </summary>
	export class IInputFile : virtual public IFile
	{
	public:
		/// <summary>
		/// Gets the input stream
		/// </summary>
		virtual std::istream& GetInStream() = 0;
	};
}

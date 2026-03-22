// <copyright file="i-output-file.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

export module Opal:IOutputFile;
import :IFile

namespace Opal::System
{
	/// <summary>
	/// The output file interface
	/// Interface mainly used to allow for unit testing client code
	/// </summary>
	export class IOutputFile : virtual public IFile
	{
	public:
		/// <summary>
		/// Gets the output stream
		/// </summary>
		virtual std::ostream& GetOutStream() = 0;
	};
}

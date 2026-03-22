// <copyright file="stl-input-file.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <fstream>
export module Opal:STLInputFile;
import :IInputFile;

namespace Opal::System
{
	/// <summary>
	/// The standard library input file implementation
	/// </summary>
	export class STLInputFile : public IInputFile
	{
	public:
		STLInputFile(std::ifstream stream) :
			_stream(std::move(stream))
		{
		}

		/// <summary>
		/// Gets the file stream
		/// </summary>
		std::istream& GetInStream() override final
		{
			return _stream;
		}

		/// <summary>
		/// Close the file stream
		/// </summary>
		void Close() override final
		{
			_stream.close();
		}

	private:
		std::ifstream _stream;
	};
}

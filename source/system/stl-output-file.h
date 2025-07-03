// <copyright file="stl-output-file.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

#pragma once
#include "i-output-file.h"

namespace Opal::System
{

	/// <summary>
	/// The standard library output file implementation
	/// </summary>
	class STLOutputFile : public IOutputFile
	{
	public:
		STLOutputFile(std::ofstream stream) :
			_stream(std::move(stream))
		{
		}

		/// <summary>
		/// Get the file stream
		/// </summary>
		std::ostream& GetOutStream() override final
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
		std::ofstream _stream;
	};
}

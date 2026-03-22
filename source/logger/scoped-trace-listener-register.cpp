// <copyright file="scoped-trace-listener-register.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <memory>
export module Opal:ScopedTraceListenerRegister;
import :Log;
import :TraceListener;

namespace Opal
{
	/// <summary>
	/// A scoped trace listener registration helper
	/// </summary>
	export class ScopedTraceListenerRegister
	{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref='ScopedTraceListenerRegister'/> class.
		/// </summary>
		ScopedTraceListenerRegister(std::shared_ptr<TraceListener> listener)
		{
			Log::RegisterListener(std::move(listener));
		}

		/// <summary>
		/// Finalizes an instance of the <see cref='ScopedTraceListenerRegister'/> class.
		/// </summary>
		~ScopedTraceListenerRegister()
		{
			Log::RegisterListener(nullptr);
		}
	};
}

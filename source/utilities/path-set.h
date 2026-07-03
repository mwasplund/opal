// <copyright file="path-set.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>
#pragma once

namespace Opal
{
	/// <summary>
	/// A set of paths
	/// </summary>
	export class PathSet
	{
	private:
		struct DirectoryEntry
		{
			std::string Value;
			std::vector<DirectoryEntry> Children;
		};

	public:
		static PathSet Build(const std::vector<Path>& set)
		{
			auto root = std::vector<DirectoryEntry>();
			return PathSet(std::move(root));
		}

	private:
		std::vector<DirectoryEntry> _root;

		/// <summary>
		/// Initializes a new instance of the <see cref="PathSet"/> class.
		/// </summary>
		PathSet(std::vector<DirectoryEntry>&& root) :
			_root(std::move(root))
		{
		}

	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="PathSet"/> class.
		/// </summary>
		PathSet() :
			_root()
		{
		}

		/// <summary>
		/// Gets a value indicating whether the path is empty
		/// </summary>
		void Serialize(std::ostream& stream) const
		{
			WriteValue(stream, (uint32_t)_root.size());
		}

	private:
		static void WriteValue(std::ostream &stream, uint32_t value) {
			stream.write(reinterpret_cast<char *>(&value), sizeof(uint32_t));
		}

		static void WriteValue(std::ostream &stream, int64_t value) {
			stream.write(reinterpret_cast<char *>(&value), sizeof(int64_t));
		}

		static void WriteValue(std::ostream &stream, double value) {
			stream.write(reinterpret_cast<char *>(&value), sizeof(double));
		}

		static void WriteValue(std::ostream &stream, bool value) {
			uint32_t integerValue = value ? 1u : 0u;
			stream.write(reinterpret_cast<char *>(&integerValue), sizeof(uint32_t));
		}

		static void WriteValue(std::ostream &stream, std::string_view value) {
			WriteValue(stream, static_cast<uint32_t>(value.size()));
			stream.write(value.data(), value.size());
		}
	};
}

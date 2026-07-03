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
			DirectoryEntry(std::string_view entry) :
				InSet(false),
				Entry(entry),
				Children()
			{
			}

			DirectoryEntry(bool inSet, std::string&& entry, std::list<DirectoryEntry>&& children) :
				InSet(inSet),
				Entry(std::move(entry)),
				Children(std::move(children))
			{
			}

			// A value that lets us know if the entry was in the original set
			bool InSet;
			std::string Entry;
			std::list<DirectoryEntry> Children;
		};

		static DirectoryEntry* EnsureEntry(std::list<DirectoryEntry>& children, std::string_view entry)
		{
			auto findEntry = std::find_if(
				children.begin(),
				children.end(),
				[entry](const DirectoryEntry& value) { return value.Entry == entry; });
			if (findEntry != children.end())
			{
				// Found you
				return &*findEntry;
			}
			else
			{
				// First time seeing this entry
				children.push_front(DirectoryEntry(entry));
				return &children.front();
			}
		}

	public:
		static PathSet Build(const std::vector<Path>& set)
		{
			auto root = std::list<DirectoryEntry>();

			for (auto& path : set)
			{
				if (!path.HasRoot())
				{
					throw std::runtime_error("Path set must be absolute paths");
				}

				// Ensure the root actually exists
				auto currentDirectory = EnsureEntry(root, path.GetRoot());

				// walk down the path
				auto directories = path.DecomposeDirectories();
				for (auto& directory : directories)
				{
					currentDirectory = EnsureEntry(currentDirectory->Children, directory);
				}

				// File names
				if (path.HasFileName())
				{
					throw std::runtime_error("TODO");
				}

				// Mark the current directory as a leaf node
				currentDirectory->InSet = true;
			}

			return PathSet(std::move(root));
		}

		static PathSet Deserialize(char *data, size_t size)
		{
			size_t offset = 0;
			auto root = ReadChildren(data, size, offset);
			return PathSet(std::move(root));
		}

	private:
		std::list<DirectoryEntry> _root;

		/// <summary>
		/// Initializes a new instance of the <see cref="PathSet"/> class.
		/// </summary>
		PathSet(std::list<DirectoryEntry>&& root) :
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
			WriteChildren(stream, _root);
		}

		std::vector<Path> GetPaths() const {
			auto result = std::vector<Path>();
			for (auto& entry : _root) {
				auto fullPath = Path(entry.Entry + "/");
				BuildPaths(result, fullPath, entry.Children);
				if (entry.InSet) {
					result.push_back(std::move(fullPath));
				}
			}

			return result;
		}

	private:
		static void BuildPaths(
			std::vector<Path>& result,
			const Path& parent,
			const std::list<DirectoryEntry>& entries) {
			for (auto& entry : entries) {
				auto fullPath = parent + Path("./" + entry.Entry + "/");
				BuildPaths(result, fullPath, entry.Children);
				if (entry.InSet) {
					result.push_back(std::move(fullPath));
				}
			}
		}

		static std::list<DirectoryEntry> ReadChildren(char *data, size_t size, size_t &offset) {
			// Read the list size
			auto listSize = ReadUInt32(data, size, offset);

			auto result = std::list<DirectoryEntry>();
			for (auto i = 0u; i < listSize; i++) {
				auto inSet = ReadBoolean(data, size, offset);
				auto entry = ReadString(data, size, offset);
				auto children = ReadChildren(data, size, offset);

				result.push_back(
					DirectoryEntry(inSet, std::move(entry), std::move(children)));
			}

			return result;
		}

		static uint32_t ReadUInt32(char *data, size_t size, size_t &offset) {
			uint32_t result = 0;
			Read(data, size, offset, reinterpret_cast<char *>(&result), sizeof(uint32_t));

			return result;
		}

		static bool ReadBoolean(char *data, size_t size, size_t &offset) {
			uint32_t result = 0;
			Read(data, size, offset, reinterpret_cast<char *>(&result), sizeof(uint32_t));

			return result != 0;
		}

		static std::string ReadString(char *data, size_t size, size_t &offset) {
			auto stringLength = ReadUInt32(data, size, offset);
			auto result = std::string(stringLength, '\0');
			Read(data, size, offset, result.data(), stringLength);

			return result;
		}

		static void Read(char *data, size_t size, size_t &offset, char *buffer, size_t count) {
			if (offset + count > size)
				throw std::runtime_error("Tried to read past end of data");
			memcpy(buffer, data + offset, count);
			offset += count;
		}

		static void WriteChildren(std::ostream &stream, const std::list<DirectoryEntry>& children) {
			WriteValue(stream, (uint32_t)children.size());
			for (auto& entry : children)
			{
				WriteValue(stream, entry.InSet);
				WriteValue(stream, entry.Entry);
				WriteChildren(stream, entry.Children);
			}
		}

		static void WriteValue(std::ostream &stream, uint32_t value) {
			stream.write(reinterpret_cast<char *>(&value), sizeof(uint32_t));
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

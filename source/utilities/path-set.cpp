// <copyright file="path-set.cpp" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>

module;
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>
export module Opal:PathSet;
import :Path;

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
			DirectoryEntry(std::string_view entry, bool isDirectory) :
				Entry(entry),
				IsDirectory(isDirectory),
				Children(),
				InSet(false)
			{
			}

			DirectoryEntry(std::string&& entry, bool isDirectory, std::list<DirectoryEntry>&& children, bool inSet) :
				Entry(std::move(entry)),
				IsDirectory(isDirectory),
				Children(std::move(children)),
				InSet(inSet)
			{
			}

			std::string Entry;
			bool IsDirectory;
			std::list<DirectoryEntry> Children;
			
			// A value that lets us know if the entry was in the original set
			bool InSet;
		};

		static DirectoryEntry* EnsureEntry(std::list<DirectoryEntry>& children, std::string_view entry, bool isDirectory)
		{
			auto findEntry = std::find_if(
				children.begin(),
				children.end(),
				[entry](const DirectoryEntry& value) { return value.Entry == entry; });
			if (findEntry != children.end())
			{
				if (findEntry->IsDirectory != isDirectory) {
					throw std::runtime_error("Cannot have directory and file with same name.");
				}

				// Found you
				return &*findEntry;
			}
			else
			{
				// First time seeing this entry
				children.push_front(DirectoryEntry(entry, isDirectory));
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
				auto currentDirectory = EnsureEntry(root, path.GetRoot(), true);

				// walk down the path
				auto directories = path.DecomposeDirectories();
				for (auto& directory : directories)
				{
					currentDirectory = EnsureEntry(currentDirectory->Children, directory, true);
				}

				// File names
				if (path.HasFileName())
				{
					currentDirectory = EnsureEntry(currentDirectory->Children, path.GetFileName(), false);
				}

				// Mark the current directory as a leaf node
				currentDirectory->InSet = true;
			}

			return PathSet(std::move(root));
		}

		static PathSet Deserialize(const char *data, size_t size)
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
				auto entryPath = entry.IsDirectory ? Path("./" + entry.Entry + "/") : Path("./" + entry.Entry);
				auto fullPath = parent + entryPath;
				BuildPaths(result, fullPath, entry.Children);
				if (entry.InSet) {
					result.push_back(std::move(fullPath));
				}
			}
		}

		static std::list<DirectoryEntry> ReadChildren(const char *data, size_t size, size_t &offset) {
			// Read the list size
			auto listSize = ReadVarInt(data, size, offset);

			auto result = std::list<DirectoryEntry>();
			for (auto i = 0u; i < listSize; i++) {
				auto [isDirectory, inSet] = ReadFlags(data, size, offset);
				auto entry = ReadString(data, size, offset);
				auto children = std::list<DirectoryEntry>();
				if (isDirectory) {
					children = ReadChildren(data, size, offset);
				}

				result.push_back(
					DirectoryEntry(std::move(entry), isDirectory, std::move(children), inSet));
			}

			return result;
		}

		static size_t ReadVarInt(const char *data, size_t size, size_t &offset) {
			size_t result = 0;
			for (auto i = 0; true; i++) {
				uint8_t currentValue = 0;
				Read(data, size, offset, reinterpret_cast<char *>(&currentValue), sizeof(uint8_t));

				result = result | (currentValue & 0x7F) << (7 * i);
				if ((currentValue & 0x80) == 0) {
					break;
				}
			}
			return result;
		}

		static std::pair<bool, bool> ReadFlags(const char *data, size_t size, size_t &offset) {
			uint8_t result = 0;
			Read(data, size, offset, reinterpret_cast<char *>(&result), sizeof(uint8_t));

			auto result1 = (result & 0x01) != 0;
			auto result2 = (result & 0x02) != 0;

			return std::make_pair(result1, result2);
		}

		static std::string ReadString(const char *data, size_t size, size_t &offset) {
			auto stringLength = ReadVarInt(data, size, offset);
			auto result = std::string(stringLength, '\0');
			Read(data, size, offset, result.data(), stringLength);

			return result;
		}

		static void Read(const char *data, size_t size, size_t &offset, char *buffer, size_t count) {
			if (offset + count > size)
				throw std::runtime_error("Tried to read past end of data");
			std::memcpy(buffer, data + offset, count);
			offset += count;
		}

		static void WriteChildren(std::ostream &stream, const std::list<DirectoryEntry>& children) {
			WriteVarInt(stream, children.size());
			for (auto& entry : children)
			{
				WriteFlags(stream, entry.IsDirectory, entry.InSet);
				WriteString(stream, entry.Entry);
				if (entry.IsDirectory) {
					WriteChildren(stream, entry.Children);
				}
			}
		}

		static void WriteVarInt(std::ostream &stream, size_t value) {
			auto isFirst = true;
			while (isFirst || value != 0) {
				auto currentValue = static_cast<uint8_t>(value & 0x7F);
				value = value >> 7;
				if (value != 0) {
					currentValue |= 0x80;
				}

				stream.write(reinterpret_cast<char *>(&currentValue), sizeof(uint8_t));
				isFirst = false;
			}
		}

		static void WriteFlags(std::ostream &stream, bool value1, bool value2) {
			uint8_t integerValue = value1 ? 0x01 : 0x00;
			integerValue |= value2 ? 0x02 : 0x00;
			stream.write(reinterpret_cast<char *>(&integerValue), sizeof(uint8_t));
		}

		static void WriteString(std::ostream &stream, std::string_view value) {
			WriteVarInt(stream, value.size());
			stream.write(value.data(), value.size());
		}
	};
}

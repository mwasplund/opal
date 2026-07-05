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
				auto entryPath = entry.IsDirectory ? Path("./" + entry.Entry + "/") : Path("./" + entry.Entry);
				auto fullPath = parent + entryPath;
				BuildPaths(result, fullPath, entry.Children);
				if (entry.InSet) {
					result.push_back(std::move(fullPath));
				}
			}
		}

		static std::list<DirectoryEntry> ReadChildren(char *data, size_t size, size_t &offset) {
			// Read the list size
			auto listSize = ReadUInt16(data, size, offset);

			auto result = std::list<DirectoryEntry>();
			for (auto i = 0u; i < listSize; i++) {
				auto [isDirectory, inSet] = ReadTwoBoolean(data, size, offset);
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

		static uint16_t ReadUInt16(char *data, size_t size, size_t &offset) {
			uint16_t result = 0;
			Read(data, size, offset, reinterpret_cast<char *>(&result), sizeof(uint16_t));

			return result;
		}

		static std::pair<bool, bool> ReadTwoBoolean(char *data, size_t size, size_t &offset) {
			uint8_t result = 0;
			Read(data, size, offset, reinterpret_cast<char *>(&result), sizeof(uint8_t));

			auto result1 = (result & 0x01) != 0;
			auto result2 = (result & 0x02) != 0;

			return std::make_pair(result1, result2);
		}

		static std::string ReadString(char *data, size_t size, size_t &offset) {
			auto stringLength = ReadUInt16(data, size, offset);
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
			WriteValue(stream, CheckCast(children.size()));
			for (auto& entry : children)
			{
				WriteValue(stream, entry.IsDirectory, entry.InSet);
				WriteValue(stream, entry.Entry);
				if (entry.IsDirectory) {
					WriteChildren(stream, entry.Children);
				}
			}
		}

		static void WriteValue(std::ostream &stream, uint16_t value) {
			stream.write(reinterpret_cast<char *>(&value), sizeof(uint16_t));
		}

		static void WriteValue(std::ostream &stream, bool value1, bool value2) {
			uint16_t integerValue = value1 ? 0x01 : 0x00;
			integerValue |= value2 ? 0x02 : 0x00;
			stream.write(reinterpret_cast<char *>(&integerValue), sizeof(uint8_t));
		}

		static void WriteValue(std::ostream &stream, std::string_view value) {
			WriteValue(stream, CheckCast(value.size()));
			stream.write(value.data(), value.size());
		}

		static uint16_t CheckCast(size_t value) {
			if (value > 0xFFFF) {
				throw std::overflow_error("Cannot store value in 16 bit value");
			}
			return static_cast<uint16_t>(value);
		}
	};
}

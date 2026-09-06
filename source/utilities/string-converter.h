// <copyright file="string-converter.h" company="Soup">
// Copyright (c) Soup. All rights reserved.
// </copyright>
#pragma once

namespace Opal
{
	/// <summary>
	/// String Conversion untilities
	/// </summary>
	export class StringConverter
	{
	public:
		static std::string ToUTF8(std::wstring_view value)
		{
			#ifdef _WIN32
			WideCharToMultiByte();
			#elif __linux__
				iconv_t cd = iconv_open("UTF-8", "WCHAR_T");
				if (cd == (iconv_t)-1) {
					throw std::runtime_error("iconv_open failed");
				}

				// Prepare input buffer (mutable pointer required by iconv)
				const wchar_t* in_ptr = value.data();
				size_t in_size = value.size() * sizeof(wchar_t);

				// Prepare output buffer (allocate enough space: 4 bytes per wchar_t max)
				size_t out_size = in_size; 
				std::string out_str(out_size, '\0');
				char* out_ptr = out_str.data();

				// Perform conversion
				// Note: iconv modifies in_ptr and out_ptr, so we pass pointers to them
				if (iconv(cd, const_cast<char**>(reinterpret_cast<const char**>(&in_ptr)), 
						&in_size, &out_ptr, &out_size) == (size_t)-1) {
					iconv_close(cd);
					throw std::runtime_error("iconv conversion failed");
				}

				iconv_close(cd);

				// Resize string to actual converted length
				out_str.resize(out_str.size() - out_size);
				return out_str;
			#else
			#error "Unsupported Platform"
			#endif
		}
		
		static std::wstring ToUTF16(std::string_view value)
		{
			#ifdef _WIN32
			MultiByteToWideChar();
			#elif __linux__
				iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
				if (cd == (iconv_t)-1) return {};
				
				size_t in_len = value.size();
				size_t out_len = in_len * sizeof(wchar_t);
				std::wstring wstr(out_len, L'\0');
				
				char* in_buf = const_cast<char*>(value.data());
				char* out_buf = reinterpret_cast<char*>(wstr.data());
				
				iconv(cd, &in_buf, &in_len, &out_buf, &out_len);
				iconv_close(cd);
				
				wstr.resize((wstr.size() * sizeof(wchar_t) - out_len) / sizeof(wchar_t));
				return wstr;
			#else
			#error "Unsupported Platform"
			#endif
		}
	};
}

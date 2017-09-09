#pragma once

#include <ostream>
#include <string>

#include "yinterpreter_exception.h"

#define DLL_INTERPRETER_API
#ifdef DEVELOPER_YINTERPRETER_
#else
#ifdef BUILD_YINTERPRETER_DLL
//#define DLL_INTERPRETER_API __declspec(dllexport)
#else
//#define DLL_INTERPRETER_API __declspec(dllimport)

#ifdef _DEBUG
#pragma comment(lib, "yinterpreter_debug")
#else
#pragma comment(lib, "yinterpreter")
#endif
#endif
#endif


namespace yu
{
namespace interpret
{

typedef class Ycode
{
public:
	/**
	 * Move-Constructor.
	 *
	 * @param	p_object	Defines the object that should be move to this.
	*/
	inline Ycode(Ycode && p_object)
	{
		m_bCopied = p_object.m_bCopied;

		m_data = p_object.m_data;
		m_type = p_object.m_type;
		p_object.m_data.pCD = nullptr;

		m_iTruncatedSize = p_object.m_iTruncatedSize;
		m_iSize = p_object.m_iSize;
		m_iOffset = p_object.m_iOffset;
		p_object.m_iTruncatedSize = 0;
		p_object.m_iSize = 0;
		p_object.m_iOffset = 0;
	}
	/**
	 * Copy constructor.
	 *
	 * @param	p_object	Defines the object that should be copied.
	 * @param	p_bCopy	Defines if the data should be copied or not. If true, the data will be copied otherwise the config of the object will apply.
	*/
	inline Ycode(const Ycode & p_object, bool p_bCopy = false) : Ycode(p_object.m_type, p_object.m_iSize, p_bCopy ? true : p_object.m_bCopied)
	{
		m_iOffset = m_iOffset = p_object.m_iOffset;
		m_iTruncatedSize = p_object.m_iTruncatedSize;

		if (m_bCopied)
		{
			if (m_iSize)
			{
				switch (m_type)
				{
				case TYPE::CHAR:
					m_data.pCD = new char[m_iSize];
					memcpy(m_data.pCD, p_object.m_data.pRD, m_iSize);

					break;
				case TYPE::CHAR_16:
					m_data.pCD_16 = new char16_t[m_iSize];
					memcpy(m_data.pCD_16, p_object.m_data.pRD_16, m_iSize * sizeof(char16_t));

					break;
				case TYPE::CHAR_32:
					m_data.pCD_32 = new char32_t[m_iSize];
					memcpy(m_data.pCD_32, p_object.m_data.pRD_32, m_iSize * sizeof(char32_t));

					break;
				default:
					break;
				}
			}
		}
		else
			m_data = p_object.m_data;
	}
	inline Ycode(const char * p_pcString, size_t p_iSize) : Ycode(TYPE::CHAR, p_pcString ? p_iSize : 0, true)
	{
		if (p_iSize && p_pcString)
		{
			m_data.pCD = new char[p_iSize];
			memcpy(m_data.pCD, p_pcString, p_iSize);
		}
	}
	inline Ycode(const char16_t * p_pcString, size_t p_iSize) : Ycode(TYPE::CHAR_16, p_pcString ? p_iSize : 0, true)
	{
		if (p_iSize && p_pcString)
		{
			m_data.pCD_16 = new char16_t[p_iSize];
			memcpy(m_data.pCD_16, p_pcString, p_iSize * sizeof(char16_t));
		}
	}
	inline Ycode(const char32_t * p_pcString, size_t p_iSize)
		: Ycode(TYPE::CHAR_32, p_pcString ? p_iSize : 0, true)
	{
		if (p_iSize && p_pcString)
		{
			m_data.pCD_32 = new char32_t[p_iSize];
			memcpy(m_data.pCD_32, p_pcString, p_iSize * sizeof(char32_t));
		}
	}
	inline Ycode(const char * p_pszString) : Ycode(p_pszString, p_pszString ? std::char_traits<char>::length(p_pszString) : 0) {}
	inline Ycode(const char16_t * p_pszString) : Ycode(p_pszString, p_pszString ? std::char_traits<char16_t>::length(p_pszString) : 0) {}
	inline Ycode(const char32_t * p_pszString) : Ycode(p_pszString, p_pszString ? std::char_traits<char32_t>::length(p_pszString) : 0) {}
	inline ~Ycode()
	{
		if (m_bCopied)
		{
			switch (m_type)
			{
			case TYPE::CHAR:
				delete m_data.pCD;

				break;
			case TYPE::CHAR_16:
				delete m_data.pCD_16;

				break;
			case TYPE::CHAR_32:
				delete m_data.pCD_32;

				break;
			default:
				break;
			}
		}
	}

	/**
	 * Truncates the size down.
	 *
	 * @param	p_iNewSize	Defines the new size. Must be smaller than the original size.
	 *
	 * @throw	EOutOfBounds	The new size is greater than the original size.
	*/
	inline void Truncate(size_t p_iNewSize)
	{
		if (p_iNewSize <= m_iSize)
			m_iTruncatedSize = p_iNewSize;
		else if (m_iOffset < m_iSize)
			m_iTruncatedSize = m_iSize - m_iOffset;
		else if (m_iSize < p_iNewSize)
			throw OutOfBounds("New size is too large.");
	}
	inline void Swap(Ycode & p_right)
	{
		{
			auto tmp = p_right.m_bCopied;
			p_right.m_bCopied = m_bCopied;
			m_bCopied = tmp;
		}

		{
			auto tmp = p_right.m_data;
			p_right.m_data = m_data;
			m_data = tmp;
		}

		{
			auto tmp = p_right.m_type;
			p_right.m_type = m_type;
			m_type = tmp;
		}

		{
			auto tmp = p_right.m_iSize;
			p_right.m_iSize = m_iSize;
			m_iSize = tmp;

			tmp = p_right.m_iOffset;
			p_right.m_iOffset = m_iOffset;
			m_iOffset = tmp;

			tmp = p_right.m_iTruncatedSize;
			p_right.m_iTruncatedSize = m_iTruncatedSize;
			m_iTruncatedSize = tmp;
		}
	}
	inline void PointTo(const char * p_pcString, size_t p_iSize)
	{
		this->~Ycode();
		new(this) Ycode(TYPE::CHAR, p_iSize, false);
		
		m_data.pRD = p_pcString;
	}
	inline void PointTo(const char16_t * p_pcString, size_t p_iSize)
	{
		this->~Ycode();
		new(this) Ycode(TYPE::CHAR_16, p_iSize, false);

		m_data.pRD_16 = p_pcString;
	}
	inline void PointTo(const char32_t * p_pcString, size_t p_iSize)
	{
		this->~Ycode();
		new(this) Ycode(TYPE::CHAR_32, p_iSize, false);

		m_data.pRD_32 = p_pcString;
	}
	inline void PointTo(const Ycode & p_code, size_t p_iSize)
	{
		this->~Ycode();
		new(this) Ycode(p_code.m_type, p_iSize, false);

		m_iOffset = p_code.m_iOffset;
		m_data = p_code.m_data;
	}
	template<typename T>
	inline const T * GetBuffer() const
	{
		static_assert(std::is_same<T, char>::value || std::is_same<T, char16_t>::value || std::is_same<T, char32_t>::value, "Buffer type has to be a character type.");

		return GetSize() ? (static_cast<const T*>(m_data.pVoid) + m_iOffset) : nullptr;
	}
	inline const void * GetBuffer() const
	{
		if (GetSize())
		{
			switch (m_type)
			{
			case TYPE::CHAR:
				return m_data.pRD + m_iOffset;
			case TYPE::CHAR_16:
				return m_data.pRD_16 + m_iOffset;
			case TYPE::CHAR_32:
				return m_data.pRD_32 + m_iOffset;
			default:
				break;
			}
		}

		return nullptr;
	}
	/**
	 * Returns true if this begins with the right object.
	 *
	 * @param	p_right	Defines the right object.
	 *
	 * @throw	EWrongEncoding	The encoding does not match.
	 * @throw	EOutOfBounds	The index is invalid.
	 *
	 * @return	true if this begins with the right obejct, otherwise false.
	*/
	inline bool BeginsWith(size_t p_iIndex, const Ycode & p_right) const
	{
		if (m_type == p_right.m_type)
		{
			auto iSize = GetSize();

			if (p_iIndex >= iSize && iSize)
				throw OutOfBounds("Index is invalid.");

			auto iRightSize = p_right.GetSize();

			if (iSize >= iRightSize)
				return !memcmp(GetBuffer(), p_right.GetBuffer(), iRightSize * GetElementSize());
		}
		else
			throw WrongEncoding("Different encoding.");

		return false;
	}
	/**
	 * Compares one element of this object with another element of the right object.
	 *
	 * @param	p_iLeftId	Defines the index of this element.
	 * @param	p_right	Defines the right object.
	 * @param	p_iRightId	Defines the index of the right object.
	 *
	 * @throw	EWrongEncoding	The encoding does not match.
	 * @throw	EOutOfBounds	One of the index is invalid.
	 *
	 * @return	true if the specified elements match, otherwise false.
	*/
	inline bool CompareElement(size_t p_iLeftId, const Ycode & p_right, size_t p_iRightId) const
	{
		if (m_type != p_right.m_type)
			throw WrongEncoding("Different encoding.");

		if (p_iLeftId < GetSize() && p_iRightId < p_right.GetSize())
		{
			switch (m_type)
			{
			case TYPE::CHAR:
				return GetBuffer<char>()[p_iLeftId] == p_right.GetBuffer<char>()[p_iRightId];
			case TYPE::CHAR_16:
				return GetBuffer<char16_t>()[p_iLeftId] == p_right.GetBuffer<char16_t>()[p_iRightId];
			case TYPE::CHAR_32:
				return GetBuffer<char32_t>()[p_iLeftId] == p_right.GetBuffer<char32_t>()[p_iRightId];
			default:
				break;
			}
		}

		throw OutOfBounds("Index is too large.");
	}
	/**
	 * Checks if the element of this object is in range.
	 *
	 * @param	p_iLeftId	Defines the index of this element.
	 * @param	p_start	Defines the start element. Must have a lower value (or equal) than @b p_end.
	 * @param	p_end	Defines the end element.
	 *
	 * @throw	EWrongEncoding	The encoding does not match.
	 * @throw	EOutOfBounds	The index or one of the elements are invalid.
	 *
	 * @return	true if the specified element is in range (element >= start && element <= end), otherwise false.
	*/
	inline bool IsElementInRange(size_t p_iLeftId, const Ycode & p_start, const Ycode & p_end) const
	{
		if (m_type != p_start.m_type || m_type != p_end.m_type)
			throw WrongEncoding("Different encoding.");

		if (p_iLeftId < GetSize() && p_start.GetSize() && p_end.GetSize())
		{
			switch (m_type)
			{
			case TYPE::CHAR:
				return GetBuffer<char>()[p_iLeftId] >= p_start.GetBuffer<char>()[0] &&
					GetBuffer<char>()[p_iLeftId] <= p_end.GetBuffer<char>()[0];
			case TYPE::CHAR_16:
				return GetBuffer<char16_t>()[p_iLeftId] >= p_start.GetBuffer<char16_t>()[0] &&
					GetBuffer<char16_t>()[p_iLeftId] <= p_end.GetBuffer<char16_t>()[0];
			case TYPE::CHAR_32:
				return GetBuffer<char32_t>()[p_iLeftId] >= p_start.GetBuffer<char32_t>()[0] &&
					GetBuffer<char32_t>()[p_iLeftId] <= p_end.GetBuffer<char32_t>()[0];
			default:
				break;
			}
		}

		throw OutOfBounds("Index is too large.");
	}
	/**
	 * Compares this object with the right one.
	 *
	 * @param	p_right	Defines the right object.
	 *
	 * @throw	EWrongEncoding	The encoding does not match.
	 *
	 * @return	>0 if this string is greater than the right one; <0 if this string is less than the right one; 0 if both strings are equal.
	*/
	inline int Compare(const Ycode & p_right) const
	{
		if (m_type == p_right.m_type)
		{
			auto iSize = GetSize();
			auto iRightSize = p_right.GetSize();

			if (iSize > iRightSize)
				return 1;
			else if (iSize < iRightSize)
				return -1;
			else
				return memcmp(GetBuffer(), p_right.GetBuffer(), iSize * GetElementSize());
		}

		throw WrongEncoding("Different encoding.");
	}
	inline int Compare(const char * p_pszString) const
	{
		if (m_type == TYPE::CHAR)
		{
			auto iSize = GetSize();
			auto iRightSize = std::char_traits<char>::length(p_pszString);

			if (iSize > iRightSize)
				return 1;
			else if (iSize < iRightSize)
				return -1;
			else
				return memcmp(GetBuffer(), p_pszString, iSize);
		}

		throw WrongEncoding("Different encoding.");
	}
	inline int Compare(const char16_t * p_pszString) const
	{
		if (m_type == TYPE::CHAR_16)
		{
			auto iSize = GetSize();
			auto iRightSize = std::char_traits<char16_t>::length(p_pszString);

			if (iSize > iRightSize)
				return 1;
			else if (iSize < iRightSize)
				return -1;
			else
				return memcmp(GetBuffer(), p_pszString, iSize * sizeof(char16_t));
		}

		throw WrongEncoding("Different encoding.");
	}
	inline int Compare(const char32_t * p_pszString) const
	{
		{
			if (m_type == TYPE::CHAR_32)
			{
				auto iSize = GetSize();
				auto iRightSize = std::char_traits<char32_t>::length(p_pszString);

				if (iSize > iRightSize)
					return 1;
				else if (iSize < iRightSize)
					return -1;
				else
					return memcmp(GetBuffer(), p_pszString, iSize * sizeof(char32_t));
			}

			throw WrongEncoding("Different encoding.");
		}
	}
	inline size_t GetSize() const
	{
		return m_iTruncatedSize;
	}
	inline size_t GetOffset() const
	{
		return m_iOffset;
	}
	inline size_t GetElementSize() const
	{
		switch (m_type)
		{
		case TYPE::CHAR:
			return sizeof(char);
		case TYPE::CHAR_16:
			return sizeof(char16_t);
		case TYPE::CHAR_32:
			return sizeof(char32_t);
		default:
			return 0;
		}
	}
	inline size_t GetOriginalSize() const
	{
		return m_iSize;
	}

	inline Ycode & operator()(const Ycode & p_right, size_t p_iOffset, size_t p_iSize)
	{
		if (p_iOffset + p_iSize <= p_right.GetSize() && p_iSize)
		{
			this->~Ycode();
			new(this) Ycode(p_right.m_type, p_iSize, true);

			switch (m_type)
			{
			case TYPE::CHAR:
				m_data.pCD = new char[p_iSize];
				memcpy(m_data.pCD, p_right.GetBuffer<char>() + p_iOffset, p_iSize);

				break;
			case TYPE::CHAR_16:
				m_data.pCD_16 = new char16_t[p_iSize];
				memcpy(m_data.pCD_16, p_right.GetBuffer<char16_t>() + p_iOffset, p_iSize * sizeof(char16_t));

				break;
			case TYPE::CHAR_32:
				m_data.pCD_32 = new char32_t[p_iSize];
				memcpy(m_data.pCD_32, p_right.GetBuffer<char32_t>() + p_iOffset, p_iSize * sizeof(char32_t));

				break;
			}
		}
		else
			throw OutOfBounds("Invalid parameter.");

		return *this;
	}
	inline Ycode & operator+=(size_t p_iOffset)
	{
		if (p_iOffset <= m_iTruncatedSize)
		{
			m_iTruncatedSize -= p_iOffset;
			m_iOffset += p_iOffset;
		}
		else
			throw OutOfBounds("Offset is too large.");

		return *this;
	}
	inline Ycode & operator=(size_t p_iOffset)
	{
		if (p_iOffset <= m_iSize)
		{
			m_iTruncatedSize = m_iSize - p_iOffset;
			m_iOffset = p_iOffset;
		}
		else
			throw OutOfBounds("Offset is too large.");

		return *this;
	}
	inline Ycode & operator=(const Ycode & p_right)
	{
		this->~Ycode();
		new(this) Ycode(p_right.m_type, p_right.GetSize(), p_right.m_bCopied);
		m_iTruncatedSize = p_right.m_iTruncatedSize;

		if (m_bCopied)
		{
			if (GetSize())
				this->operator()(p_right, 0, p_right.GetSize());
		}
		else
			m_data = p_right.m_data;

		return *this;
	}
	inline bool operator==(const Ycode & p_right) const
	{
		return Compare(p_right) == 0;
	}
	inline bool operator==(const char * p_pszString) const
	{
		return Compare(p_pszString) == 0;
	}
	inline bool operator==(const char16_t * p_pszString) const
	{
		return Compare(p_pszString) == 0;
	}
	inline bool operator==(const char32_t * p_pszString) const
	{
		return Compare(p_pszString) == 0;
	}
	inline friend std::ostream & operator<<(std::ostream & p_stream, const Ycode & p_code)
	{
		if (p_code.m_type == TYPE::CHAR)
			p_stream.write(p_code.GetBuffer<char>(), p_code.GetSize());

		return p_stream;
	}

private:
	union Data
	{
		const void * pVoid;
		char * pCD;
		char16_t * pCD_16;
		char32_t * pCD_32;
		const char * pRD;
		const char16_t * pRD_16;
		const char32_t * pRD_32;
	};

	enum class TYPE
	{
		CHAR,
		CHAR_16,
		CHAR_32
	};

	bool m_bCopied;

	Data m_data;
	TYPE m_type;

	size_t m_iSize;
	size_t m_iOffset;
	size_t m_iTruncatedSize;


	inline Ycode(TYPE p_type, size_t p_iSize, bool p_bCopy) : m_data{}
	{
		m_iSize = p_iSize;
		m_iOffset = 0;
		m_iTruncatedSize = p_iSize;
		m_bCopied = p_bCopy;
		m_type = p_type;
	}
} ycode;

}
}

using yu::interpret::ycode;
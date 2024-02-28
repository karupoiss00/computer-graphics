#pragma once
#include <cassert>
#include <memory>

#include "WriteProxy.h"

template <typename T>
class CoW
{
	template <typename U>
	struct CopyConstr
	{
		static std::unique_ptr<U> Copy(U const& other)
		{
			return std::make_unique<T>(other);
		}
	};

	template <typename U>
	struct CloneConstr
	{
		static std::unique_ptr<U> Copy(U const& other)
		{
			return other.Clone();
		}
	};
	using CopyClass = typename std::conditional<
		!std::is_abstract<T>::value && std::is_copy_constructible<T>::value,
		CopyConstr<T>,
		CloneConstr<T>>::type;
public:
	template <typename... Args, typename = std::enable_if<!std::is_abstract<T>::value>::type>
	CoW(Args&&... args)
		: m_shared(std::make_shared<T>(std::forward<Args>(args)...))
	{
	}

	// avoid duplicate object
	CoW(CoW<T>&& rhs)
		: m_shared(std::move(rhs.m_shared))
	{
	}

	CoW(std::unique_ptr<T> pUniqueObj)
		: m_shared(std::move(pUniqueObj))
	{
	}

	CoW& operator=(CoW<T>&& rhs)
	{
		m_shared = std::move(rhs.m_shared);
		return *this;
	}

	template <typename U>
	CoW(CoW<U>& rhs)
		: m_shared(rhs.m_shared)
	{
	}

	template <typename U>
	CoW& operator=(CoW<U>& rhs)
	{
		m_shared = rhs.m_shared;
		return *this;
	}

	// vc generate copy, but c++11 don't allow this, implement for gcc

	CoW(CoW const& rhs)
		: m_shared(rhs.m_shared)
	{
	}

	CoW& operator=(CoW const& rhs)
	{
		m_shared = rhs.m_shared;
		return *this;
	}

	T const& operator*() const&& noexcept = delete;
	T const& operator*() const& noexcept
	{
		assert(m_shared);
		return *m_shared;
	}

	T const* operator->() const&& noexcept = delete;
	T const* operator->() const& noexcept
	{
		assert(m_shared);
		return m_shared.get();
	}

	[[nodiscard]] WriteProxy<T> operator--(int) &
	{
		assert(m_shared);
		EnsureUnique();
		return WriteProxy(m_shared.get());
	}

	WriteProxy<T> Write() &
	{
		assert(m_shared);
		EnsureUnique();
		return WriteProxy(m_shared.get());
	}

private:
	void EnsureUnique()
	{
		if (m_shared.use_count() != 1)
		{
			m_shared = CopyClass::Copy(*m_shared);
		}
	}

private:
	std::shared_ptr<T> m_shared;
};
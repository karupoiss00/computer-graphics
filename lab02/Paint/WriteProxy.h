#pragma once
template <typename T>
class WriteProxy
{
public:
	WriteProxy(T* p)
		: m_p(p)
	{
	}

	T& operator*() const& = delete;
	[[nodiscard]] T& operator*() const&& noexcept
	{
		return *m_p;
	}

	// Operator -> must be invoked only once on temporary object
	// Do not store reference to CWriteProxy
	T* operator->() const& = delete;
	T* operator->() const&&
	{
		return m_p;
	}

private:
	T* m_p;
};
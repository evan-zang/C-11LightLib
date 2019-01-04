#pragma once

class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	// 禁用复制构造
	NonCopyable(const NonCopyable&) = delete;
	// 禁用赋值构造
	NonCopyable& operator = (const NonCopyable&) = delete;
};
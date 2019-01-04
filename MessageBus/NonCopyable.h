#pragma once

class NonCopyable
{
protected:
	NonCopyable() = default;
	~NonCopyable() = default;
	// ���ø��ƹ���
	NonCopyable(const NonCopyable&) = delete;
	// ���ø�ֵ����
	NonCopyable& operator = (const NonCopyable&) = delete;
};
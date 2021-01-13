#pragma once
template <size_t _SizeInByte>
struct BitBool
{
public:
	size_t Size() {
		return _SizeInByte * 8;
	}
	bool operator[](size_t posn) {
		return ((data[posn / 8] & (1 << (posn % 8))) != 0);
	}
	void Set(size_t posn, bool status) {
		status = status ? 1 : 0;//lets say status was previously somthing entirely different
		size_t block = posn / 8;
		if (block >= _SizeInByte)
			return;
		data[block] ^= (-status ^ data[block]) & (1UL << (posn % 8));
	}
	void SetAllValues(bool _val) {
		unsigned char _setter = _val ? ALL_TRUE : ALL_FALSE;
		for (size_t i = 0;i < _SizeInByte;i++)
			data[i] = _setter;
	}
	BitBool() {
		for (size_t i = 0; i < _SizeInByte; i++)
			data[i] = 0;
	}
private:
	static unsigned char const ALL_FALSE = 0, ALL_TRUE = 255;
	unsigned char data[_SizeInByte];
};
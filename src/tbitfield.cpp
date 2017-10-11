// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{ 
	if (len < 0)
		throw ("Error");
		BitLen = len;
		MemLen = len/BITS_IN_ONE_MEM;
		if ((len%BITS_IN_ONE_MEM) != 0)
			MemLen += 1;
		pMem = new TELEM[MemLen];
		for (int i = 0;i < MemLen;i++)
			pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM [bf.MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{ 
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n<0)|(n > BitLen))
		throw "Error index.";
	int pElem;
	pElem = n/BITS_IN_ONE_MEM;
  return pElem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{ 
	if ((n<0) | (n > BitLen))
		throw "Error index.";
	TELEM BitMask = 0;
	BitMask = 1 << (n%BITS_IN_ONE_MEM);
  return BitMask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0)|(n>BitLen))
		throw ("Error");
			TELEM mask = GetMemMask(n);
			int index = GetMemIndex(n);
			pMem[index] |= mask;
		
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) | (n>BitLen))
		throw ("Error");
	TELEM mask = GetMemMask(n);
	int index = GetMemIndex(n);
	pMem[index] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) | (n>BitLen))
		throw ("Error");
	TELEM mask = GetMemMask(n);
	int index = GetMemIndex(n);
	int k = pMem[index] & mask;
	if (k > 0)
		return 1;
	else
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[bf.MemLen];
		for (int i = 0;i < MemLen;i++)
			pMem[i] = bf.pMem[i];
	}
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen != bf.MemLen)
		return 0;
	else 
		if (BitLen != bf.BitLen)
			return 0;
	else
	{
		for (int i = 0;i < BitLen;i++)
		{
			int a = GetBit(i);
			int b = bf.GetBit(i);
			if (a != b)
				return 0;
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = (*this == bf);
	return !res;
		
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int max = (BitLen < bf.BitLen) ? bf.BitLen : BitLen;
	int min = (BitLen > bf.BitLen) ? bf.BitLen : BitLen;
	TBitField res(max);
	if (max == bf.BitLen)
		res = bf;
	else
		res = *this;
	for (int i = 0; i < min; i++)
	{
		int a = GetBit(i);
		int b = bf.GetBit(i);
		if ((a + b) != 0)
			res.SetBit(i);
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int min = (BitLen > bf.BitLen) ? bf.BitLen : BitLen;
	TBitField res(min);
	for (int i = 0; i < (res.MemLen - 1); i++)
		res.pMem[i] = pMem[i] & bf.pMem[i];
	for (int j=(res.MemLen-1)*BITS_IN_ONE_MEM;j<res.BitLen;j++)
	{
		int a = GetBit(j);
		int b = bf.GetBit(j);
		if ((a + b) == 2)
			res.SetBit(j);
	}
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < (res.MemLen - 1); i++)
		res.pMem[i] = ~pMem[i];
	for (int j = (res.MemLen - 1)*BITS_IN_ONE_MEM; j < res.BitLen; j++)
	{
		int a = GetBit(j);
		if (a == 0)
			res.SetBit(j);
		else
			res.ClrBit(j);
	}
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int n, k;
	cin >> n; // размер
	for (int i=0; i<n; i++)
	{
		cin >> k; 
		while (k>(-1))
		{
			bf.SetBit(k);
			cin >> k;
		}
	}
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	cout << "{";
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i) == 1)
			cout << i << " ";
	}
    cout << "}\n";
  return ostr;
}

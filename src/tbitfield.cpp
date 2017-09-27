// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{ BitLen = len;
  int ost = len%(BITS_IN_ONE_MEM);
  if (ost==0)
	  MemLen = len/(BITS_IN_ONE_MEM);
  else 
	  MemLen = len/(BITS_IN_ONE_MEM) + 1;
  pMem = new TELEM [MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	delete[]pMem;
	pMem = new TELEM [bf.MemLen];
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
}

TBitField::~TBitField()
{ 
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int pElem;
	if (n%(BITS_IN_ONE_MEM)==0)
		pElem = n/(BITS_IN_ONE_MEM);
	else
		pElem = n/(BITS_IN_ONE_MEM) + 1;
  return pElem;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{ 
	TELEM BitMask = 2^n;
  return BitMask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  return TBitField(0);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
  return TBitField(0);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  cout << "{" << "}\n";
  return ostr;
}

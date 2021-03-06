// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{ 
	MaxPower = mp;
	
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
	
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
	
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return false;
	else
	{
		if (BitField != s.BitField)
			return false;
		else
			return true;
	}
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return true;
	else
	{
		if (BitField != s.BitField)
			return true;
		else
			return false;
	}
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet res(BitField | s.BitField);
	return res;

}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(*this);
	res.BitField.SetBit(Elem);
  return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(*this);
	res.BitField.ClrBit(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet res(BitField & s.BitField);
	return res;
	
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(*this);
	res.BitField = ~res.BitField;
	return res;

}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int maxp, k;
	cin >> maxp; // размер
	for (int i = 0; i<maxp; i++)
	{
		cin >> k;
		while (k>(-1))
		{
			s.BitField.SetBit(k);
			cin >> k;
		}
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	cout << "{";
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{
		if (s.BitField.GetBit(i) == 1)
			cout << i << " ";
	}
	cout << "}\n";
	return ostr;
  return ostr;
}

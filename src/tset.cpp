// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp=10) : BitField(mp)
{
	MaxPower = mp;
	//BitField = TBitField(mp);
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
	//BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
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
	if ((Elem < 0) || (Elem > MaxPower)) return -1;
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem < 0) || (Elem > MaxPower)) throw Elem;
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem < 0) || (Elem > MaxPower)) throw Elem;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (MaxPower != s.MaxPower) MaxPower = s.MaxPower;
	BitField = s.BitField;
	
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower) return 0;
	if (BitField != s.BitField) return 0;

    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower) return 1;
	if (BitField != s.BitField) return 1;

	return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp;
	if (MaxPower > s.MaxPower) tmp = *this;
	else tmp = s;

	tmp.BitField = BitField | s.BitField;
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp(*this);
	if ((Elem < 0) || (Elem > BitField.GetLength())) throw -1;
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp = *this;
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp;
	
	if (MaxPower > s.MaxPower) tmp = *this;
	else tmp = s;
	tmp.BitField = BitField & s.BitField;
	
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(this->MaxPower);
	tmp.BitField = ~(this->BitField);
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}

/* ********************************************************************************
 * Prof. Dr. Andre F. de Angelis
 * School of Technology
 * University of Campinas (Unicamp)
 * 1st Semester - 2024
 * ********************************************************************************
 * This file is part of a C++ teaching project directed to undergraduate students
 * of Information System; and System Analyzes and Development courses of the School
 * of Technology of Unicamp.
 * The project is a simplified cash flow control intended to demonstrate C++
 * resources and capabilities. There are non-optimized parts and some unrealistic
 * pieces of code in it, as well as advanced function pointers and unconventional
 * use of data structures, according to the project objectives.
 * The cash flow program is not a real application. Use its code to learn C++.
 * ********************************************************************************
 * g++ (GCC) 13.3.1 20240522 (Red Hat 13.3.1-1)
 * Eclipse Version: 2023-12 (4.30.0) Build id: 20231201-2043
 * Fedora Linux 39 + KDE
 * ********************************************************************************
 * Copyright (C) 2024 Andre F. de Angelis
 * ********************************************************************************
 * Date.cpp
 * ********************************************************************************
 */

#include <iomanip>
#include <ctime>

#include "Date.h"

using namespace std;

Date::Date()
	{
	time_t now = time(NULL);
	tm *currentTime = localtime(&now);
	day = currentTime->tm_mday;
	month = currentTime->tm_mon;
	year = currentTime->tm_year;
	}

Date::Date(string isoFormat)
	{
	day = stoi(isoFormat.substr(8, 10));
	month = stoi(isoFormat.substr(5, 7));
	year = stoi(isoFormat.substr(0, 4));
	}

Date::Date(int day, int month, int year) :
		day(day), month(month), year(year)
	{
	}

Date::~Date()
	{
	}

int Date::getYear()
	{
	return year;
	}

int Date::getMonth()
	{
	return month;
	}

int Date::getDay()
	{
	return day;
	}

string Date::getIsoFormat()
	{
	return (to_string(year) + "-" + to_string(month) + "-" + to_string(day));
	}

bool Date::operator==(const Date &other) const
	{
	return year == other.year && month == other.month && day == other.day;
	}

bool Date::operator!=(const Date &other) const
	{
	return !(*this == other);
	}

bool Date::operator>(const Date &other) const
	{
	if (year != other.year)
		return year > other.year;
	if (month != other.month)
		return month > other.month;
	return day > other.day;
	}

bool Date::operator>=(const Date &other) const
	{
	return (*this == other) || (*this > other);
	}

bool Date::operator<(const Date &other) const
	{
	return !(*this >= other);
	}

bool Date::operator<=(const Date &other) const
	{
	return !(*this > other);
	}

ostream& operator<<(ostream &os, const Date &date)
	{
	os << setfill('0') << setw(4) << date.year << ".";
	os << setfill('0') << setw(2) << date.month << ".";
	os << setfill('0') << setw(2) << date.day;
	return os;
	}

istream& operator>>(std::istream &is, Date &date)
	{
	char separator;
	is >> date.day >> separator >> date.month >> separator >> date.year;
	return is;
	}

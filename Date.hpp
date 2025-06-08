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
 * Date.h
 * ********************************************************************************
 */

#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <ctime>

class Date
	{
	private:
		int day;
		int month;
		int year;

	public:
		Date();
		Date(int day, int month, int year);
		Date(std::string isoFormat);
		virtual ~Date();

		int getYear();
		int getMonth();
		int getDay();
		std::string getIsoFormat();

		bool operator==(const Date &other) const;
		bool operator!=(const Date &other) const;
		bool operator>(const Date &other) const;
		bool operator>=(const Date &other) const;
		bool operator<(const Date &other) const;
		bool operator<=(const Date &other) const;

		friend std::ostream& operator<<(std::ostream &os, const Date &date);
		friend std::istream& operator>>(std::istream &is, Date &date);
	};

#endif /* DATE_H_ */

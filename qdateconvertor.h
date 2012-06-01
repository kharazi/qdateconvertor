#ifndef QDATECONVERTOR_H
#define QDATECONVERTOR_H
/****************************************************
*QDateConvertor library for Qt developers 
*this library can convert Jalali dates to Miladi and Miladi(AD) to Jalali(shamsi/khorshidi)
*
*    Copyright (C) 2012  vahid kharazi <vahid@kharazi.net>
*
*    This program is free software: you can redistribute it and/or modify
*
*   it under the terms of the GNU General Public License as published by
*
*    the Free Software Foundation, either version 3 of the License, or
*
*    (at your option) any later version.
*    This program is distributed in the hope that it will be useful,
*
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*
*    GNU General Public License for more details.
*
*
*
*    You should have received a copy of the GNU General Public License
*
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************
*how to use:
*---------------QDateConvertor----------------
*- add qdateconvertor class to your project
*- include qdataconvertor where you want to use qdataconvertor
*- use from QDateConvertor::ToJalali(year,month,day)[return QStringList] function to convert Miladi date to Jalali and 
*  use from QDateConvertor::ToMiladi(year,month,day)[return QStringList] function to convert Jalali date to Miladi
*for Example:
*    include <QDebug>
*    include <QDateTime>
*    include "qdateconvertor.h"
*
*
*    QDateConvertor Jalali;
*    QDateTime date =QDateTime::currentDateTime();
*    QStringList shamsi=  Jalali.ToJalali( date.toString("yyyy"), date.toString("MM"),date.toString("dd"));
*    QString JalailDate =shamsi.at(0)+"/"+shamsi.at(1)+"/"+shamsi.at(2);
*    qDebug()<<"JALALI DATE: "<<JalailDate;
or:
*    QDateConvertor Miladi;
*    QStringList m= Miladi.ToMiladi("1372","3","6");
*    QString miladiDate= m.at(0)+"/"+ m.at(1)+"/"+m.at(2);
*    qDebug()<<"VAHID BIRTHDAY: "<<miladiDate;
*
*------------------------------------------------
*QDateConvertor Class 
*Copyright 2012 Vahid Kharazi <vahid@kharazi.net>
*Licensed for distribution under the GPL version 3
*------------------------------------------------
******************************************************/


#include <QStringList>
#include <QDate>
#include <QList>
class QDateConvertor
{
public:
    QDateConvertor();
    int div(int,int);
    bool is_leap(int year);
    QStringList ToJalali(QString year, QString month,QString day);
    QStringList ToMiladi(QString year, QString month,QString day);
    int dayCount;

};

#endif // QDATECONVERTOR_H

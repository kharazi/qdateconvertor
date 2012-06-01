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
#include "qdateconvertor.h"
#include <QDebug>
QDateConvertor::QDateConvertor()
{

}



int QDateConvertor::div(int a,int b)
{
    return  (a / b);
}

bool QDateConvertor::is_leap(int year){


}


QStringList QDateConvertor::ToJalali(QString year, QString month,QString day ){
   int g_y = year.toInt();
   int g_m = month.toInt();
   int g_d = day.toInt();
   QList<int> g_days_in_month,j_days_in_month  ;
   g_days_in_month << 31 << 28 << 31 << 30 << 31 << 30 << 31 <<31 << 30 << 31<< 30 << 31;
   j_days_in_month <<31 <<31 <<31 << 31 << 31 << 31 << 30 << 30 << 30 << 30 << 30 << 29;
   int   gy = g_y-1600;
   int   gm = g_m-1;
   int  gd = g_d-1;
   int    g_day_no = 365*gy+div(gy+3,4)-div(gy+99,100)+div(gy+399,400);
   for (int i=0; i < gm; ++i){
       g_day_no += g_days_in_month[i];
   }

   if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
          /* leap and after Feb */
          g_day_no++;
          g_day_no += gd;
    int j_day_no = g_day_no-79;
    int  j_np = div(j_day_no, 12053); /* 12053 = 365*33 + 32/4 */
    j_day_no = j_day_no % 12053;
    int jy = 979+33*j_np+4*div(j_day_no,1461); /* 1461 = 365*4 + 4/4 */
    j_day_no %= 1461;

     if (j_day_no >= 366) {
          jy += div(j_day_no-1, 365);
          j_day_no = (j_day_no-1)%365;
     }
     int ii;
     for (int i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i){
          j_day_no -= j_days_in_month[i];
          ii=i;
     }
     int  jm = ii+2;
     int  jd = j_day_no+1;
     QStringList jalali;
     jalali << QString::number(jy) << QString::number(jm)<< QString::number(jd) ;
     return jalali;
    }



QStringList QDateConvertor::ToMiladi(QString year, QString month,QString day ){
    //set Date
    int Year;
    int Month;
    int Day;

    Year=year.toInt();//Jalali Year
    Month=month.toInt();//Jalali Month
    Day=day.toInt();//Jalali Day

    QList <int> miladiDate;
    QList <int> farvardin1st;
    //set default value
    miladiDate<<1<<1<<1;
    farvardin1st<<1<<1<<1;

    int miladiYear;
    int marchDayDiff;

    QList<int> miladiMonth;
    miladiMonth<<30<<31<<30<<31<<31<<30<<31<<30<<31<<31<<28<<31;

    miladiYear = Year + 621;

    //Detemining the Farvardin the First
    if (QDate::isLeapYear(miladiYear)){
        //this is a Miladi leap year so Shamsi is leap too so the 1st of Farvardin is March 20 (3/20)
        farvardin1st[1] =3; // change default values
        farvardin1st[2]= 20;
        marchDayDiff = 12;


    }else{
        //this is not a Miladi leap year so Shamsi is not leap too so the 1st of Farvardin is March 21 (3/21)
        farvardin1st[1] = 3;
        farvardin1st[2] =21;
        marchDayDiff = 11;
    }

    if (QDate::isLeapYear(miladiYear+1)){

        miladiMonth[10] = miladiMonth[10] + 1; //Adding one day to Feb

    }
    //Calculate the day count for input shamsi date from 1st Farvadin

    if (Month >=1 && Month<=6){

        dayCount = ((Month-1) * 31) + Day;

    }else{

        dayCount =(6 * 31) + ((Month - 7) * 30) + Day;
    }

    //Finding the correspond miladi month and day
    int remainDay;
    if (dayCount <=marchDayDiff){
        //So we are in 20(for leap year) or 21for none leap year) to 31 march
        miladiDate[2] = dayCount + (31 - marchDayDiff);
        miladiDate[1] = 3;
        miladiDate[0] = miladiYear;

    }else{
         remainDay = dayCount - marchDayDiff;

    }

    int i;
    i=0;//starting from April

    while (remainDay>miladiMonth[i]){
        remainDay = remainDay - miladiMonth[i];
        i = i+1;
    }
    miladiDate[2] = remainDay;
    if (i>8){
        // We are in the next Miladi Year
        miladiDate[1] = i - 8;
        miladiDate[0] =  miladiYear + 1;
    }else{
        miladiDate[1] = i + 4;
        miladiDate[0] =  miladiYear;

    }

    QStringList mymiladiDate;
    mymiladiDate <<QString::number(miladiDate[0])<<QString::number(miladiDate[1])<<QString::number(miladiDate[2]);
    return mymiladiDate;


}

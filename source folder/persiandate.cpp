#include "persiandate.h"
#include <QDebug>
int PersianDate::sourceLeapYear=2016;
int PersianDate::daysMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int PersianDate::daysPersianMonth[12]={31,31,31,31,31,31,30,30,30,30,30,29};
PersianDate::PersianDate()
{
    year=0;
    month=0;
    day=0;
}

PersianDate PersianDate::getPersianDate(QDate md)
{
    int year=md.year();
    int month=md.month();
    int day=md.day();

    int count_leapYear=(year-1)/4;

    int days=(year-1)*365;
    for(int i=0;i<month-1;i++)
        days+=daysMonth[i];
    days+=day;
    days+=count_leapYear;

    if((year-sourceLeapYear)%4==0 && month>2)//if it's leap year
        days++;

    days-=226899;

    int y=days/365;
    days=days-(y-1)/4;
    days=days%365;
    int m=1;
    while(true){
        if(m==12){

            if((y-1387)%4==0){
                if(days<=30)
                    break;
                days-=30;
            }
            else{
                if(days<=29)
                    break;
                days-=29;
            }
        }
        else{
            if(days<=daysPersianMonth[m-1])
                break;
            days-=daysPersianMonth[m-1];
        }

        m++;

    }
    qDebug()<<"date "<<y<<"\\"<<m<<"\\"<<days;

    PersianDate res;
    res.setYear(y);
    res.setMonth(m);
    res.setDay(days);

    return res;
}

QString PersianDate::getDate()
{
    if(year!=0 && month!=0 && day!=0)
        return QString::number(year)+"/"+QString::number(month)+"/"+QString::number(day);
}

int PersianDate::getYear()
{
    return year;
}

int PersianDate::getMonth()
{
    return month;
}

int PersianDate::getDay()
{
    return day;
}

void PersianDate::setYear(int y)
{
    year=y;
}

void PersianDate::setMonth(int m)
{
    month=m;
}

void PersianDate::setDay(int d)
{
    day=d;
}


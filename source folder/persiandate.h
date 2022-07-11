#ifndef PERSIANDATE_H
#define PERSIANDATE_H

#include <QDate>
class PersianDate
{
public:
    PersianDate();

    static PersianDate getPersianDate(QDate md);

    QString getDate();
    int getYear();
    int getMonth();
    int getDay();

    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
private:
    int year,month,day;

    static int sourceLeapYear;

    enum MONTH{JANUARY,FEBUARY,MARCH,APRIL,MAY,JUNE
               ,JULY,AUGUST,SEPTEMBER,OCTOBER,NEVEMBER,DECEMBER};
    static int daysMonth[12];
    static int daysPersianMonth[12];



};

#endif // PERSIANDATE_H

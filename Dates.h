#pragma warning (disable: 4996)
#pragma once
#include <iostream>
using namespace std;
class Date
{
private:
    short day = 1;
    short month=1;
    short year=1900;
  
public:
    Date()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        day = now->tm_mday;
       month = now->tm_mon + 1;
        year = now->tm_year + 1900;
    }
    Date(short _day, short _month, short _year):day(_day),month(_month),year(_year) {}
    Date(int getDays, short _year) {
        Date date1 = convertnbrDaysToDate(getDays, _year);
        day = date1.day;
        month = date1.month;
        year = date1.year;
        
    }
    void setDay(short _day) {
        day = _day;
    }
    short getDay() {
        return day;
    }
    __declspec(property(get = getDay, put = setDay))short day;
    void setMonth(short _month) {
        month= _month;
    }
    short getMonth() {
        return month;           
    }
    __declspec(property(get = getMOnth, put = setMonth))short month;

    void setYear(short _year) {
        year=_year;
    }
    short getYear() {
        return year;
    }
    __declspec(property(get = getYear, put = setYear))short year;

    static Date getSystemDate() {
        time_t t = time(0);
        tm* now = localtime(&t);
        short day, month, year;
        day = now->tm_mday;
        month = now->tm_mon + 1;
        year = now->tm_year + 1900;
        return Date(day, month, year);
    }
   static bool isLeapYear(short year)
    {
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    }
   bool isLeapYear() {
       return isLeapYear(this->year);
   }
   static int numberOfDaysInYear(short year) {

        return (isLeapYear(year)) ? 366 : 356;
    }
   int numberOfDaysInYear() {
       return numberOfHoursInYear(this->year);
   }
   static int numberOfHoursInYear(short year) {
        return numberOfDaysInYear(year) * 24;
    }
   int numberOfHoursInYear() {
       return numberOfHoursInYear(this->year);
   }
    int numberOfMinutsInyear(short year) {
        return numberOfHoursInYear(year) * 60;
    }
    int numberOfSecondsInYear(short year) {
        return numberOfMinutsInyear(year) * 60;
    }
    static short numberOfDaysInMonth(short year, short month)
    {
        if (month < 1 || month>12) { return 0; }

        int daysOfMnth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (month == 2) ? (isLeapYear(year) ? 29 : 28) : daysOfMnth[month - 1];//the best one way

        //second method

        /*if(month==2){
            return (isLeapYear(year)) ? 29 : 28;
        }
        else return (daysOfMnth[month-1]);*/


        //third method

        /*int daysOfMnth[] = { 1,3,5,7,8,10,12 };
        for (int i = 1; i < 7; i++) {
            if (daysOfMnth[i] == month) { return 31;
            }
        }
         return 30;*/

    }
    short numberOfDaysInMonth() {
        return numberOfDaysInMonth(this->year, this->month);
    }
    int numberOfMinutsInMonth(short year, short month) {
        return numberOfDaysInMonth(year, month) * 60;
    }
    int numberOfSecondsInMonth(short year, short month) {
        return numberOfMinutsInMonth(year, month) * 60;
    }
    static  short dayOfWeeksOrder(short day, short month, short year) {
        int a = (14 - month) / 12;
        int y = year - a;
        int m = month + (12 * a) - 2;
        //Georgean method
        return   (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }//it give the number fo day in the week
    short dayOfWeeksOrder() {
        return dayOfWeeksOrder(this->day,this-> month, this->year);
    }
    static  string dayConverter(short dayOfWeeksOrder) {
        string days[] = { "sunday","monday","tuesday","wednesday","thursday","friday","saturday" };
        return days[dayOfWeeksOrder];
    }   
    static string monthShortName(short month) {
        string months[] = { "jan","feb","mar","apr","may","jun","jul","out","sep","oct","nov","des" };
        return months[month - 1];
    }
    string monthShortName() {
        return monthShortName(this->month);
    }
    static string daysShortName(short day) {
        string days[] = { "sun","mon","tue","wed","thu","fri","sat" };
        return days[day - 1];
    }
    string daysShortName() {
        string days[] = { "sun","mon","tue","wed","thu","fri","sat" };
        return days[dayOfWeeksOrder(day,month,year)];
    }
    static void printMonthCalendar(short month, short year) {

        short nbrDays = numberOfDaysInMonth(year, month);
        short current = dayOfWeeksOrder(1, month, year);

        printf("\n  _______________%s_______________\n\n", monthShortName(month).c_str());

        printf("  sun  mon  tue  wed  thu  fri  sat\n");
        int i;
        for (i = 0; i < current; i++) {
            printf("     ");
        }

        for (int j = 1; j <= nbrDays; j++) {
            printf("%5d", j);

            if (++i == 7) {
                i = 0;
                printf("\n");
            }
        }

        printf("\n  _________________________________\n");

    }
   static void printMonthCalendar(Date date) {
        return printMonthCalendar(date.month, date.year);
    }
    void printMonthCalendar() {
        return printMonthCalendar(*this);
    }
   static void printYearCalendar(short year) {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", year);
        printf("  _________________________________\n");
        for (int i = 1; i <= 12; i++) {

            printMonthCalendar(i, year);
            printf("\n    __________________________\n");

        }
    }
   static void printYearCalendar(Date date) {
        return printYearCalendar(date.year);
    }
   void printYearCalendar() {
       return printYearCalendar(*this);
   }
   static short numberOfDaysFromDate(short day, short month, short year) {
        int totalDays = 0;
        for (int i = 1; i <= month - 1; i++) {
            totalDays += numberOfDaysInMonth(year, i);
        }
        totalDays += numberOfDaysInMonth(year, month);
        return totalDays;
    }
   short numberOfDaysFromDate() {
       return numberOfDaysFromDate(day, month, year);
   }
   static Date convertnbrDaysToDate( int days, short year) {
        Date date;
        date.year = year;
        int remainnigDays = days;
        date.month = 1;
        int nbrOfdays = 0;
        while (true) {
            nbrOfdays = numberOfDaysInMonth(year, date.month);
            if (remainnigDays > nbrOfdays) {
                remainnigDays -= nbrOfdays;
                date.month++;
            }
            else {
                date.day = remainnigDays;
                break;
            }

        }
        return date;
    }
   Date convertnbrDaysToDate(int days) {
       return convertnbrDaysToDate(days, this->year);
   }
    static bool isDateLessThan(Date date1, Date date2) {
        /*if (date1.year < date2.year) {
            return true;
        }
        else if (date1.year == date2.year) {
            if (date1.month < date2.month) {
                return true;
            }

        }
        else if (date1.month == date2.month) {
            if(date1.day<date2.day) { return true; }

        }

        else return false;*/
        return  (date1.year < date2.year) ? true : ((date1.year == date2.year) ? (date1.month < date2.month ? true : (date1.month == date2.month ? date1.day < date2.day : false)) : false);
    }
    bool isDateLessThan(Date date) {
        return isDateLessThan(*this, date);
    }
   static bool isEqualDates(Date date1, Date date2) {
        if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day) {
            return true;
        }
        else return false;
    }
   bool isEqualDates(Date date) {
       return isEqualDates(*this,date);
   }
   static bool isLastDayInMonth(Date date) {
        return (date.day == numberOfDaysInMonth(date.year, date.month));
    }
   bool isLastDayInMonth() {
       return isLastDayInMonth(*this);
   }
   static bool isLastMonthInYear(short month) {
        return (month == 12);

    }
   static Date addOneDay(Date &date) {
        if (isLastDayInMonth(date)) {
            if (isLastMonthInYear(date.month)) {
                date.year++;
                date.month = 1;
                date.day = 1;
            }
            else {
                date.month++;
                date.day = 1;
            }
        }
        else { date.day++; }
        return date;
    }
   Date addOneDay() {
       return addOneDay(*this);
   }
   static void swapDates(Date& date1, Date& date2) {
        Date temp;
        temp.day = date1.day;
        temp.month = date1.month;
        temp.year = date1.year;
        date1.day = date2.day;
        date1.month = date2.month;
        date1.year = date2.year;
        date2.day = temp.day;
        date2.month = temp.month;
        date2.year = temp.year;
    }
   static int getDifferenceInDays(Date date1, Date date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        short swapFlag = 1;

        if (!isDateLessThan(date1, date2)) {
            swapDates(date1, date2);
            swapFlag = -1;

        }
        while (isDateLessThan(date1, date2))
        {
            Days++;
            date1 = addOneDay(date1);
        }
        return IncludeEndDay ? ++Days * swapFlag : Days * swapFlag;

    }
   int getDifferenceInDays(Date date2) {
       return getDifferenceInDays(*this, date2,true);
   }
   static int ageInDays(Date date, Date currentDate) {

        return  getDifferenceInDays(date, currentDate, true);

        //short years=date.year;
        //int sum = 0;
        //sum += numberOfDaysInYear(years) - numberOfDaysFromDate(date.day, date.month, date.year);
        //years++;
        //while (years < currentDate.year) {
        //    sum += numberOfDaysInYear(years);
        //    years++;
        //}
        //return sum += numberOfDaysFromDate(date.day, date.month, date.year);
        /* int sum=getDifferenceInDays(date, currentDate, true);
        return sum;*/
        /*  if (numberOfDaysFromDate(date.day,date.month,date.year) == numberOfDaysFromDate(currentDate.day,currentDate.month,currentDate.year) {
              return 0;

          }*/
    }
   int ageInDays(Date currentDate) {
       return ageInDays(*this, currentDate);
   }
   static Date increaseDateByXDays(Date &date, int days) {
        for (int i = 1; i <= days; i++) {
            date = addOneDay(date);
        }
        return date;
    }
   Date increaseDateByXDays(int days) {
       return increaseDateByXDays(*this,  days);
   }
   static Date increaseDateByOneWeek(Date &date) {
        for (int i = 1; i <= 7; i++) {
            date = addOneDay(date);
        }
        return date;
    }
   Date increaseDateByOneWeek() {
       return increaseDateByOneWeek(*this);
   }
   static Date increaseDateByXWeeks(Date &date, int Weeks) {
        for (int i = 1; i <= Weeks; i++) {
            date = increaseDateByOneWeek(date);
        }
        return date;
    }
   Date increaseDateByXWeeks(int weeks) {
       return increaseDateByXWeeks(*this, weeks);
   }
   static Date increaseDateByOneMonth(Date &date) {
        if (date.month == 12) {
            date.year++;
            date.month = 1;
        }
        else {
            date.month++;
        }
        short nbrDaysInCurrentMnt = numberOfDaysInMonth(date.year, date.month);
        if (date.day != nbrDaysInCurrentMnt) {
            date.day = nbrDaysInCurrentMnt;
        }
        return date;
    }
   Date increaseDateByOneMonth() {
       return increaseDateByOneMonth(*this);
   }
   static Date increaseDateByXMonth(Date &date, int months) {
        for (int i = 1; i <= months; i++) {
            date = increaseDateByOneMonth(date);
        }
        return date;
    }
   Date increaseDateByXMonth(int months) {
       return increaseDateByXMonth(*this, months);
   }
   static Date increaseDateByOneYear(Date &date) {
        date.year++;
        if (date.month == 2 && date.day == 29 && !isLeapYear(date.year)) {
            date.day = 28;
        }
        return date;
    }
   Date increaseDateByOneYear() {
       return increaseDateByOneYear(*this);
   }
   static Date increaseDateByXYears(Date &date, int years) {
        for (int i = 1; i <= years; i++) {
            date = increaseDateByOneYear(date);
        }
        return date;
    }
   Date increaseDateByXYears(int years) {
       return increaseDateByXYears(*this, years);
   }  
   static Date decreaseDateByOneDay(Date &date) {

        if (date.month == 1 && date.day == 1) {
            date.year--;
            date.month = 12;
            date.day = numberOfDaysInMonth(date.year, date.month);
        }
        else if (date.day == 1) {
            date.month--;
            date.day = numberOfDaysInMonth(date.year, date.month);
        }
        else { date.day--; }
        return date;
    }
   Date decreaseDateByOneDay() {
       return decreaseDateByOneDay(*this);
   }
   static Date decreaseDateByXDays(Date &date, int days) {
        for (int i = 1; i <= days; i++) {
            date = decreaseDateByOneDay(date);
        }
        return date;
    }
   Date decreaseDateByXDays(int days) {
       return decreaseDateByXDays(*this, days);
   }
   static Date decreaseDateByOneWeek(Date &date) {
        return decreaseDateByXDays(date, 7);
    }
   Date decreaseDateByOneWeek() {
       return decreaseDateByOneWeek(*this);
   }
   static Date decreaseDateByXWeeks(Date &date, int weeks) {
        for (int i = 1; i <= weeks; i++) {
            date = decreaseDateByOneWeek(date);
        }
        return date;
    }
   Date decreaseDateByXWeeks(int weeks) {
       return decreaseDateByXWeeks(*this, weeks);
   }
   static Date decreaseDateByOneMonth(Date &date) {
        for (int i = 1; i < numberOfDaysInMonth(date.year, date.month); i++) {
            date = decreaseDateByOneDay(date);
        }

        return date;
    }
   Date decreaseDateByOneMonth() {
       return decreaseDateByOneMonth(*this);
   }
   static Date decreaseDateByXMonths(Date &date, int months) {
        for (int i = 1; i <= months; i++) {
            date = decreaseDateByOneMonth(date);
        }
        return date;
    }
   Date decreaseDateByXMonths(int months) {
       return decreaseDateByXMonths(*this, months);
   }
   static Date decreaseDateByOneYear(Date &date) {
        date.year--;
        if (date.month == 2 && date.day == 29 && !isLeapYear(date.year)) {
            date.day = 28;
        }
        return date;
    }
   Date decreaseDateByOneYear() {
       return decreaseDateByOneYear(*this);
   }
   static Date decreaseDateByXYears(Date &date, int years) {
        for (short i = 1; i <= years; i++) {
            date = decreaseDateByOneYear(date);
        }
        return date;
    }
   Date decreaseDateByXYears(int years) {
       return decreaseDateByXYears(*this, years);
   }
   static short dayOfWeekOrder(Date date) {
        return dayOfWeeksOrder(date.day, date.month, date.year);
    }
   static bool isWeekEnd(Date date) {
        short indexDays = dayOfWeekOrder(date);
        return (indexDays == 5 || indexDays == 6);
    }
   bool isWeekEnd() {
       return isWeekEnd(*this);
   }
   static bool isEndOfWeek(Date date) {
        return(dayOfWeekOrder(date) == 6);
    }
   bool isEndOfWeek() {
       return isEndOfWeek(*this);
   }
   static bool isBusnissDay(Date date) {
        return !isWeekEnd(date);
    }
   bool isBusnissDay() {
       return isBusnissDay(*this);
   }
   static short daysUntilEndOfWeek(Date date) {
        return 6 - dayOfWeekOrder(date);
    }
   short daysUntilEndOfWeek() {
       return daysUntilEndOfWeek(*this);
   }
   static short daysUntilEndOfMonth(Date date) {
        Date date1;
        date1.day = numberOfDaysInMonth(date.year, date.month);
        date1.month = date.month;
        date1.year = date.year;
        return  getDifferenceInDays(date, date1, true);

    }
   short daysUntilEndOfMonth() {
       return daysUntilEndOfMonth(*this);
   }
   static short daysUntilEndOfYear(Date date) {
        Date date1;
        date1.day = 31;
        date1.month = 12;
        date1.year = date.year;
        return getDifferenceInDays(date, date1, true);
    }
   short daysUntilEndOfYear() {
       return daysUntilEndOfYear(*this);
   }
   static  short vacationPeriod(Date date1, Date date2) {
        short sum = 0;
        while (isDateLessThan(date1, date2)) {
            if (isBusnissDay(date1)) {
                sum++;
            }
            date1 = addOneDay(date1);
        }
        return sum;

    }
   short vacationPeriod(Date date) {
       return vacationPeriod(*this, date);
   }
   static Date vacationDateStartFromDate(Date& date, short days) {

        short weekEndCounter = 0;
        while (isWeekEnd(date)) {
            date = addOneDay(date);
        }
        for (short i = 1; i <= days + weekEndCounter; i++) {

            if (isWeekEnd(date)) {
                weekEndCounter++;
            }
            date = addOneDay(date);
        }
        while (isWeekEnd(date)) {
            date = addOneDay(date);
        }

        return date;
    }
   Date vacationDateStartFromDate(short days) {
       return vacationDateStartFromDate(*this, days);
   }
   static  bool isDateOneEqualDateTwo(Date date1, Date date2) {
        return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
    }
   bool isDateOneEqualDateTwo(Date date) {
       return  isDateOneEqualDateTwo(*this, date);
   }
   static bool isDateOneBeforeDateTwo(Date date1, Date date2) {
        return isDateLessThan(date1, date2);
    }
   bool isDateOneBeforeDateTwo(Date date) {
       return  isDateOneBeforeDateTwo(*this, date);
   }
   static bool isDAteOneAfterDateTwo(Date date1, Date date2) {
        return (!isDateLessThan(date1, date2) && !isDateOneEqualDateTwo(date1, date2));
    }
   bool isDAteOneAfterDateTwo(Date date) {
       return  isDAteOneAfterDateTwo(*this, date);
   }
    enum dateCompare { before = -1, equal = 0, after = 1 };
   static short compareDates(Date date1, Date date2) {
        if (isDateOneBeforeDateTwo(date1, date2)) {
            return dateCompare::before;
        }
        else if (isDateOneEqualDateTwo(date1, date2)) {
            return dateCompare::equal;
        }
        return dateCompare::after;
    }
   /* bool isOverLapPeriods(Period period1, Period period2) {
        if ((compareDates(period2.endDate, period1.startDate) == dateCompare::before)
            || (compareDates(period2.startDate, period1.endDate) == dateCompare::after)) {
            return false;
        }
        else return true;
    }
    short periodLengthInDays(Period period, bool includeEndDay = false) {
        return getDifferenceInDays(period.startDate, period.endDate, includeEndDay);
    }
    bool isDateInPeriod(Date date, Period period) {
        if (compareDates(date, period.startDate) == dateCompare::before || compareDates(date, period.endDate) == dateCompare::after) {
            return false;
        }
        else return true;
    }
    int lengthOfOverLap(Period period1, Period period2) {
        int Period1Length = periodLengthInDays(period1, true);
        int Period2Length = periodLengthInDays(period2, true);
        int OverlapDays = 0;
        if (!isOverLapPeriods(period1, period2))
            return 0;
        if (Period1Length < Period2Length)
        {
            while (isDateOneBeforeDateTwo(period1.startDate, period1.endDate))
            {
                if (isDateInPeriod(period1.startDate, period2))
                    OverlapDays++;
                period1.startDate = addOneDay(period1.startDate);
            }
        }
        else {
            while (isDateOneBeforeDateTwo(period2.startDate, period2.endDate))
            {
                if (isDateInPeriod(period2.startDate, period1))
                    OverlapDays++;
                period2.startDate = addOneDay(period2.startDate);
            }
        }
        return OverlapDays;
    }*/
   static bool isValidDate(Date date) {

        if (date.day < 1 || date.day>31) {
            return false;
        }
        if (date.month < 1 || date.month>12) {
            return false;
        }
        if (date.month == 12) {
            if (isLeapYear(date.year) && (date.day > 29)) {

                return false;
            }
            else if (!isLeapYear(date.year) && (date.day > 28)) {

                return false;
            }
        }
        short nbrDays = numberOfDaysInMonth(date.year, date.month);
        if (date.day > nbrDays) {
            return false;
        }
        else return true;
    }
   bool isValid() {
       return isValidDate(*this);
   }
    void print() {
        cout << day << "/" << month << "/" << year << endl;
    }
   
};


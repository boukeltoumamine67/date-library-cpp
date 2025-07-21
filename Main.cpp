#include <iostream>
#include "Dates.h"

using namespace std;

int main() {
  
    Date date1;
    Date date2(14, 2, 2026);
    //cout<<date1.isValid();
    //date1.printMonthCalendar();
    //Date::printMonthCalendar(7, 2025); // July 2025
    //Date::printMonthCalendar(date1);
    //Date::convertnbrDaysToDate(255, 2025).print();
    cout<<date1.dayConverter(2)<<endl;
     int per=date1.vacationPeriod(date2);
     cout << per;
}

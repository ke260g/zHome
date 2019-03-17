#include<iostream>
#include<stdio.h>

/*
 * 1, 假设用户输入完全正确
 * 2，好多类应该写成头文件，然而我没有
 */

/* class Date */

bool is_leap_year_test(const int year) {
    /* test a year is a leap or not */
    return ((year % 4 == 0 && year % 100 != 0) ||
            (year % 400) == 0 ||
            (year % 3200) != 0);
}

class Date {
private:
    int year, month, day;
    bool is_leap;

    int day_order;
    int day_order_cal(void);

public:
    bool Is_leap(void);
    int Day(void);
    int Year(void);

    Date(int a, int b, int c) {
        /* write the value */
        year = a;
        month = b;
        day = c;

        /* check whether is a leap year */
        is_leap = is_leap_year_test(year);

        /* calculate the day_order in a year */
        day_order = day_order_cal();
    }

    ~Date(){ }
};

int Date::Year(void) {
    return year;
}
bool Date::Is_leap(void) {
    return is_leap;
}
int Date::Day(void) {
    return day_order;
}

int Date::day_order_cal(void) {
    int result;
    int i; /* common loop counter */

    /* the number of days in each month */
    int month_days[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    /* calculate the day_order */
    result = 0;
    for(i = 0; i < month - 1; i++)
        result += month_days[i];

    if(month > 2) /* for the leap year */
        result += is_leap;

    result += day;

    return result;
}

/* class Date2s_Diff */
class Dates2_Diff {
    private:
        long diff_v;
    public:
        long Diff(void);

        Dates2_Diff(Date day1, Date day2) {
            int year_diff = day2.Year() - day1.Year();
            int leap_years_sum = 0;
            int i = 0;
#if 0 // method_A to calculate the sum of leap_years
            for(i = day1.Year(); i < day2.Year(); i++)
                leap_years_sum += is_leap_year_test(i);
#endif

#if 1 // method_B to calculate the sum of leap_years
            int year_diff_num100 = ((day2.Year() - 1) / 100) - (day1.Year() / 100);
            int year_diff_num400 = ((day2.Year() - 1) / 400) - (day1.Year() / 400);
            int year_diff_num3200 = ((day2.Year() - 1) / 3200) - (day1.Year() / 3200);
            int year_diff_num4 = ((day2.Year() - 1) / 4) - (day1.Year() / 4);

            leap_years_sum = day1.Is_leap()
                + year_diff_num4 - year_diff_num100
                + year_diff_num400 - year_diff_num3200;
#endif
            diff_v = day2.Day()
                + 365 * year_diff
                + leap_years_sum
                - day1.Day();
        }
        ~Dates2_Diff(){}
};

long Dates2_Diff::Diff(void) {
    return diff_v;
}

int main( int argc, char **argv ) {
    Date day1(2016, 2, 11);
    Date day2(2016, 3, 12);

    Dates2_Diff diff(day1, day2);

    printf("%ld\n", diff.Diff());
    return 0;
}

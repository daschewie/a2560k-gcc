#include <sys/time.h>
#include <time.h>
#include "mcp.h"

int gettimeofday (struct timeval *tv, void *tz) {
  struct s_time rtc;
  struct tm t;
  time_t t_of_day;
  
  if(tv) {
    sys_rtc_get_time(&rtc);
    t.tm_year = rtc.year + 100;    // Year - 1900
    t.tm_mon = rtc.month - 1;      // Month, where 0 = jan
    t.tm_mday = rtc.day;           // Day of the month

    if (rtc.is_24hours) {
      t.tm_hour = rtc.hour;
    } else if (rtc.is_pm && rtc.hour >= 1 && rtc.hour <= 11) {
      t.tm_hour = rtc.hour + 12;
    } else if (!rtc.is_pm && rtc.hour == 12) {
      t.tm_hour = 0;
    } else {
      t.tm_hour = rtc.hour;
    }

    t.tm_min = rtc.minute;
    t.tm_sec = rtc.second;
    t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);

    tv->tv_sec = t_of_day;
    tv->tv_usec = 0;
  }

  return 0;
}
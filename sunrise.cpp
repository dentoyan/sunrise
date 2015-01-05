#include <QtCore>
#include "sunrise.h"


Sunrise::Sunrise(double latitude_, double longitude_, double elevation_)
  : latitude(latitude_)
  , longitude(-longitude_)
  , elevation(elevation_)
{
    
}

int Sunrise::julian(const QDate &d)
{
    QDateTime dt(d, QTime(12, 1, 0, 0));
    return dt.toUTC().date().toJulianDay();
}

QTime Sunrise::sunrise(const QDate &d)
{
    if (!d.isValid())
        return QTime();
    
    double j = sunrise(julian(d));
    return date(j).time();
}

QTime Sunrise::noon(const QDate &d)
{
    if (!d.isValid())
        return QTime();
    
    double j = noon(julian(d));
    return date(j).time();
}

QTime Sunrise::sunset(const QDate &d)
{
    if (!d.isValid())
        return QTime();
    
    double j = sunset(julian(d));
    return date(j).time();
}

QDateTime Sunrise::date(double julian)
{
    if (julian < 0.0)
        return QDateTime();
    // The day number is the integer part of the date
    int julianDays = qFloor(julian);
    QDate d = QDate::fromJulianDay(julianDays);
    // The fraction is the time of day
    double julianMSecs = (julian - static_cast<double>(julianDays)) * 86400.0 * 1000.0;
    // Julian days start at noon (12:00 UTC)
    return QDateTime(d, QTime(12, 0, 0, 0), Qt::UTC).addMSecs(qRound(julianMSecs)).toLocalTime();
}



#include "sunrise.h"
#include <iostream>

int main(int argc, char **argv)
{
  QDate d;  
  if (argc != 2)
    d = QDate::currentDate();
  else
    d = QDate::fromString(argv[1], Qt::ISODate);
    
  using namespace std;
  if (!d.isValid()) {
      cerr << "Invalid date" << endl;
      return 1;
  }
  
  cout << d.toString().toStdString() << endl;
  // Sunrise sunrise(16.141, -22.904); // Boa Vista, Cabo Verde


/*
 * Hannover
   Position: 52° 23' 12" N,  9° 41' 52" E
 */
  Sunrise sunrise(52.386667, 9.697778);


  cout << "sunrise: " << sunrise.sunrise(d).toString().toStdString() << endl;
  cout << "noon:    " << sunrise.noon(d).toString().toStdString() << endl;
  cout << "sunset:  " << sunrise.sunset(d).toString().toStdString() << endl;
  
  return 0;
}



/*
 * 
 "Fr. Dez 19 2014" 
 
./sunrise 2014-12-19

 
19. A:  08:10
  U:    16:03
 
 
Sonnenaufgang       08:12
Transit             12:06
Sonnenuntergang     16:01


Algorithm 
 
Calculating Sunrise and Sunset

So you want to calculate sunrise and sunset. Simple (maybe).

If this doesn't make sense to you without real numbers, you might want to check out my in your face sunrise/sunset calculator.

If you want to know where all of the constants come from, check out the source of this information.

Variables:
Jdate = Julian date
lw = West Longitude (75W = 75, 45E = -45)
ln = North Latitude (35N = 35, 25S = -25)
M = Mean Solar Anomaly
n = Julian cycle since Jan 1, 2000
C = Equation of center
λ = Ecliptical longitude of the sun
δ = Declination of the sun
H = Hour Angle (half the arc length of the sun)
Jtransit = Julian date of solar noon on cycle n
Jrise = Julian date of sunrise on cycle n
Jset = Julian date of sunset on cycle n

First, start by calculating the number of days since January 1, 2000. Add that number to 2451545 (the Julian day of January 1, 2000). This will be variable Jdate.

The next step is to calculate the Julian cycle. This is not equal to the days since Jan 1, 2000. Depending on your longitude, this may be a different number.
n* = (Jdate - 2451545 - 0.0009) - (lw/360)
n = round(n*)

Now, it is time to approximate the Julian date of solar noon. This is just an approximation so that we can make some intermediate calculations before we calculate the actual Julian date of solar noon.
J* = 2451545 + 0.0009 + (lw/360) + n

Using the approximate value, calculate the mean solar anomaly. This will get a very close value to the actual mean solar anomaly.
M = [357.5291 + 0.98560028 * (J* - 2451545)] mod 360

Calculate the equation of center
C = (1.9148 * sin(M)) + (0.0200 * sin(2 * M)) + (0.0003 * sin(3 * M))

Now, using C and M, calculate the ecliptical longitude of the sun.
λ = (M + 102.9372 + C + 180) mod 360

Now there is enough data to calculate an accurate Julian date for solar noon.
Jtransit = J* + (0.0053 * sin(M)) - (0.0069 * sin(2 * λ))

To calculate the hour angle we need to find the declination of the sun
δ = arcsin( sin(λ) * sin(23.45) )

Now, calculate the hour angle, which corresponds to half of the arc length of the sun at this latitude at this declination of the sun
H = arccos( [sin(-0.83) - sin(ln) * sin(δ)] / [cos(ln) * cos(δ)] )
Note: If H is undefined, then there is either no sunrise (in winter) or no sunset (in summer) for the supplied latitude.

Okay, time to go back through the approximation again, this time we use H in the calculation
J** = 2451545 + 0.0009 + ((H + lw)/360) + n

The values of M and λ from above don't really change from solar noon to sunset, so there is no need to recalculate them before calculating sunset.
Jset = J** + (0.0053 * sin(M)) - (0.0069 * sin(2 * λ))

Instead of going through that mess again, assume that solar noon is half-way between sunrise and sunset (valid for latitudes < 60) and approximate sunrise.
Jrise = Jtransit - (Jset - Jtransit)

At this point you should convert the Julian dates to something more readable like a regular date. This will be left as an exercise to the reader.

Source: http://aa.quae.nl/en/reken/zonpositie.html
 
 
 */


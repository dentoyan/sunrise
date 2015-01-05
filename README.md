Sunrise Sunset Calculator
=========================

About
-----

This class calculates the Sunrise/Noon/Sunset based on date and location.
The constructor takes in Latitude and Longitude values as doubles.
Optionally an elevation in meters can be specified.

The calculation functions accept dates and return local time values.

Copyright (c) 2014-2015 Joshua Dentoyan


Usage
-----

- ./sunrise 2014-12-19


Example - Sunrise calculator
----------------------------

Display the time of sunrise, noon and sunset for a specified date on a specified location.


```cpp
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
  Sunrise sunrise(16.141, -22.904); // Boa Vista, Cabo Verde

  cout << "sunrise: " << sunrise.sunrise(d).toString().toStdString() << endl;
  cout << "noon:    " << sunrise.noon(d).toString().toStdString() << endl;
  cout << "sunset:  " << sunrise.sunset(d).toString().toStdString() << endl;
 
  return 0;
}
```

License
-------

<a href="LICENSE">LGPLv2.1+</a>.






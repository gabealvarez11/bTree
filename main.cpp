//
//  main.cpp
//  LLTemplate
//
//  Created by Gabe Alvarez on 12/6/16.
//  Copyright © 2016 Gabe Alvarez. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath> 
#include <string>
#include <stdlib.h>
#include "bTree.h"

using namespace std;

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
	double disAustin;
   
	
	friend ostream &operator<<( ostream &output, const Airport &D )
	{ 
         output << D.code << " " << D.longitude << " " << D.latitude << " " << D.disAustin << endl;
         return output;            
    }
	
	void print()
	{
		cout << code << " " << longitude << " " << latitude << " " << disAustin << endl;
	}
	
};

bool operator>(Airport a, Airport b)
{
	return (a.disAustin > b.disAustin) ? true : false;
}

bool operator<(Airport a, Airport b)
{
	return (a.disAustin < b.disAustin) ? true : false;
}

void simpleSort(Airport* aus, int airportCount, Airport* airportArr[]);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main()
{
    ifstream infile;
    int i=0;
    char cNum[10] ;
    Airport* airportArr[13500];
    int   airportCount;
    
	infile.open ("./USAirportCodes.csv", ifstream::in);

    if (infile.is_open())
    {
		int   c=0;
        while (infile.good())
        {
            airportArr[c] = new Airport();
            infile.getline(airportArr[c]->code, 256, ',');
            infile.getline(cNum, 256, ',');
            airportArr[c]->longitude = atof(cNum);
            infile.getline(cNum, 256, '\n');
            airportArr[c]->latitude = atof(cNum);
            
            i++ ;
            c++;
        }
        airportCount = c-1;
        infile.close();
        
    }
    else
    {
        cout << "Error opening file";
    }
   
   cout << "Count: " << airportCount << endl;
   
   Airport* austin = airportArr[10655];
   
   cout << austin->code;
   simpleSort(austin, airportCount, airportArr);
   Airport* farthest;
   
    ofstream output;
	output.open("sorted.csv");
	Airport* a;
	string write;
	for(int z = 0; z < airportCount; z++)
	{
		a = airportArr[z];
		double distanceToAus = distanceEarth(a->latitude, a->longitude, austin->latitude, austin->longitude);
		a->disAustin = distanceToAus;
		output << "" << a->code << "," << a->latitude << "," << a->longitude << "," << distanceToAus << "\n";
	}
   
   output.close();
   
    double dis;
   
      double farthestDis = distanceEarth(airportArr[0]->latitude, airportArr[0]->longitude, austin->latitude, austin->longitude);

      cout << "Farthest Airport: " << airportArr[0]->code << " distance: " << farthestDis << endl;
   
   bTree<Airport> x(2);
   for(int i = 0; i < 1000; i++)
   {
	   x.insert(airportArr[i]);
   }

   x.display();
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void simpleSort(Airport* aus, int airportCount, Airport* airportArr[])
{
	Airport* temp;
	for (int i=0; i < airportCount; i++)
	{	
		for (int j=i; j < airportCount; j++)
		{
			if (distanceEarth(airportArr[i]->latitude, airportArr[i]->longitude, aus->latitude, aus->longitude) < distanceEarth(airportArr[j]->latitude, airportArr[j]->longitude, aus->latitude, aus->longitude))
			//total pointed at by i > total pointed at by j
			{
				//swap pointer to record I with pointer to record j
				temp = airportArr[i];
				airportArr[i] = airportArr[j];
				airportArr[j] = temp;
			}
		}
	}
}
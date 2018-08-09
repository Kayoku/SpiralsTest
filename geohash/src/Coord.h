#ifndef DEFINE_COORD
#define DEFINE_COORD

static const int MAX_LAT = 90;
static const int MIN_LAT = -90;

static const int MAX_LONG = 180;
static const int MIN_LONG = -180;

/*
 * Structure
 * Définit une coordonnée par sa latitude et sa longitude
 */

struct Coord
{
 float latitude;
 float longitude;
};

#endif

#include <iostream>
#include <vector>
#include <string>

#include "gtest/gtest.h"

extern "C" {
#include "geohash.h"
}

const std::vector<double> latitudes  = {42.6, -25.382708, -25.427, -25.383};
const std::vector<double> longitudes = {-5.6, -49.265506, -49.315, -49.266};
const std::vector<std::string> hashs = {"ezs42", "6gkzwgjzn820",
                                        "6gkzmg1u", "6gkzwgjt"};

////////////////////////////////////////////////////////////////////////////
TEST(GeoHash, encode_geohash)
////////////////////////////////////////////////////////////////////////////
{
 int size_test, i, precision;
 struct Coord coord;

 size_test = sizeof(latitudes)/sizeof(latitudes[0]);

 for (i = 0 ; i < size_test ; i++)
 {
  precision = hashs[i].size();
  coord.latitude = latitudes[i];
  coord.longitude = longitudes[i];
  ASSERT_STREQ(encode_geohash(coord, precision), hashs[i].c_str());
 }
}

////////////////////////////////////////////////////////////////////////////
TEST(GeoHash, decode_geohash)
////////////////////////////////////////////////////////////////////////////
{
 int size_test, i;
 struct Coord coord;
 struct Coord_Error max_error;

 size_test = sizeof(latitudes)/sizeof(latitudes[0]);

 for (i = 0 ; i < size_test ; i++)
 {
  coord = decode_geohash(hashs[i].c_str(), &max_error);
  ASSERT_TRUE(
    coord.latitude >= latitudes[i]-max_error.latitude_error &&
    coord.latitude <= latitudes[i]+max_error.latitude_error &&
    coord.longitude >= longitudes[i]-max_error.longitude_error &&
    coord.longitude <= longitudes[i]+max_error.longitude_error);
 }
}

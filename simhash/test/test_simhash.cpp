#include <iostream>
#include <vector>
#include <openssl/md5.h>

#include "gtest/gtest.h"

extern "C" {
#include "simhash.h"
}

/**************************************************************************/
TEST(SimHash, md5_hash)
/**************************************************************************/
{
 std::vector<std::string> strings = {
                   "premier test",
                   "ceci est une longue phrase",
                   "Voila un nouveau hash",
                   "blablablabla"};
 std::vector<std::string> hashs  = {
                   "6598609863c7f869be3347ef3f91aa62",
                   "09abd41e19959d87956d9712706d7e3c",
                   "3d751b36ca259c45f90b9d38e08b9f7c",
                   "5993d7a73d9f9a694e411ba0788cfe2d"};

 int size = 4, i;
 char md5_temp[2*MD5_DIGEST_LENGTH+1] = "";

 for (i = 0; i < size ; i++)
 {
  memset(md5_temp, 0, MD5_DIGEST_LENGTH);
  md5_hash(strings[i].c_str(), md5_temp);
  ASSERT_TRUE(strcmp(md5_temp, hashs[i].c_str()) == 0);
 }
}

/**************************************************************************/
TEST(SimHash, hamming_distance)
/**************************************************************************/
{
 std::string str = "Je suis une phrase de test pour voir si cela marche";
 std::string str2 = "Je suis une phrase de test pour voir si cela marche";
 std::string str3 = "Phrase totalement différente";

 ASSERT_TRUE(hamming_distance(str.c_str(), str2.c_str(), 2, 1) == 0);
 ASSERT_FALSE(hamming_distance(str.c_str(), str3.c_str(), 2, 1) == 0);
}

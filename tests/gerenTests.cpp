#define BOOST_TEST_MODULE gerenTests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "lib/msgParse.hpp"

BOOST_AUTO_TEST_CASE(TestMsgParse){
   BOOST_CHECK(messageParse(string()));
}

#include "pch.h"
#include "../EMS/SearchEngine.h"
#include "mock_DataBase.h"
#include "../Types.h"
#include <iostream>
using namespace std;

TEST(SEARCHENGINE, SearchByEmployeeNum) {
    list<Employee> db;
    db.emplace_back(Employee{ 2015123099, {"VXIHXOTH", "JHOP"}, CL::CL3, {010, 3112, 2609}, {1977,12,11}, CERTI::ADV });
    db.emplace_back(Employee{ 2017112609, {"FB", "NTAWR"}, CL::CL4, {010, 5645, 6122}, {1986,12,03}, CERTI::PRO });
    db.emplace_back(Employee{ 2018115040, {"TTETHU", "HBO"}, CL::CL3, {010, 4581, 2050}, {2008,07,18}, CERTI::ADV });
    db.emplace_back(Employee{ 1988114052, {"NQ", "LVARW"}, CL::CL4, {010, 4528, 3059}, {1991,10,21}, CERTI::PRO });
    db.emplace_back(Employee{ 2019129568, {"SRERLALH", "HMEF"}, CL::CL2, {010, 3091, 9521}, {1964,9,10}, CERTI::PRO });
    db.emplace_back(Employee{ 2017111236, {"VSID", "TVO"}, CL::CL1, {010, 3669, 1077}, {2012,7,18}, CERTI::PRO });
    db.emplace_back(Employee{ 2018117906, {"TWU", "QSOLT"}, CL::CL4, {010, 6672, 7186}, {2003,4,13}, CERTI::PRO });
    db.emplace_back(Employee{ 2008123556, {"WN", "XV"}, CL::CL1, {010, 7986, 5047}, {2010,6,14}, CERTI::PRO });
    db.emplace_back(Employee{ 2002117175, {"SBILHUT", "LDEXRI"}, CL::CL4, {010, 2814, 1699}, {1995,7,4}, CERTI::ADV });
    db.emplace_back(Employee{ 2003113260, {"HH", "LTUPF"}, CL::CL2, {010, 5798, 5383}, {1979,10,18}, CERTI::PRO });
    db.emplace_back(Employee{ 2014130827, {"RPO", "JK"}, CL::CL4, {010, 3231, 1698}, {2009,2,1}, CERTI::ADV });
    db.emplace_back(Employee{ 2001122329, {"DN", "WD"}, CL::CL4, {010, 7174, 5680}, {2007,11,17}, CERTI::PRO });
    db.emplace_back(Employee{ 2008108827, {"RTAH", "VNUP"}, CL::CL4, {010, 9031, 2726}, {1978,4,17}, CERTI::ADV });
    db.emplace_back(Employee{ 1985125741, {"FBAH", "RTIJ"}, CL::CL1, {010, 8900, 1478}, {1978,2,28}, CERTI::ADV });
    db.emplace_back(Employee{ 2008117441, {"BMU", "MPOSXU"}, CL::CL3, {010, 2703, 3153}, {2001,2,15}, CERTI::ADV });
    db.emplace_back(Employee{ 2010127115, {"KBU", "MHU"}, CL::CL3, {010, 3284, 4054}, {1966,8,14}, CERTI::ADV });
    db.emplace_back(Employee{ 2012117017, {"LFIS", "JJIVL"}, CL::CL1, {010, 7914, 4067}, {2012,8,12}, CERTI::PRO });
    db.emplace_back(Employee{ 2011125777, {"TKOQKIS", "HC"}, CL::CL1, {010, 6734, 2289}, {1999,10,1}, CERTI::PRO });
    db.emplace_back(Employee{ 2011109136, {"QKAHCEX", "LTODDO"}, CL::CL4, {010, 2627, 8566}, {1964,1,30}, CERTI::PRO });
    db.emplace_back(Employee{ 2005101762, {"VCUHLE", "HMU"}, CL::CL4, {010, 3988, 9289}, {2003,8,19}, CERTI::PRO });

    SearchEngine se;


    //EXPECT_EQ(0, size(se.Search(db, 65000000)));
    //EXPECT_EQ(0, size(se.Search(db, 22000000)));
}


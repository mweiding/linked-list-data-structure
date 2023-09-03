#include "testList.h"

#include <memory>

// empty list

TEST(ListTest, Test_EmptyList) {
list<int, std::string> l;
EXPECT_TRUE(l.isEmpty());
}

// insert and search

TEST(ListTest, SearchTest_OneElementInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin(1, "Eins");
l += tin;
EXPECT_EQ("Eins", *l.search(1));
}

// insert and popHead

TEST(ListTest, InsertTest_OneElementInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin(1, "Eins");
l += tin;
EXPECT_FALSE(l.isEmpty());
auto tout = l.popHead();
EXPECT_TRUE(l.isEmpty());
EXPECT_EQ(tin, tout);
}

TEST(ListTest, InsertTest_TwoElementsInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(2, "Zwei");
l += tin1;
l += tin2;
EXPECT_FALSE(l.isEmpty());
auto tout1 = l.popHead();
EXPECT_FALSE(l.isEmpty());
EXPECT_EQ(tin1, tout1);
auto tout2 = l.popHead();
EXPECT_TRUE(l.isEmpty());
EXPECT_EQ(tin2, tout2);
}

TEST(ListTest, InsertTest_TwoElementsWithSameKey) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(1, "Zwei");
l += tin1;
l += tin2;
EXPECT_FALSE(l.isEmpty());
auto tout1 = l.popHead();
EXPECT_TRUE(l.isEmpty());
EXPECT_EQ(tin2, tout1);
}

// remove

TEST(ListTest, RemoveTest_NoElementInList) {
list<int, std::string> l;
EXPECT_TRUE(l.isEmpty());
l -= 1;
EXPECT_TRUE(l.isEmpty());
}

TEST(ListTest, RemoveTest_OneElementInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin(1, "Eins");
l += tin;
EXPECT_FALSE(l.isEmpty());
l -= 1;
EXPECT_TRUE(l.isEmpty());
}

TEST(ListTest, RemoveTest_TwoElementsInListRemove1_2) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(2, "Zwei");
l += tin1;
l += tin2;
EXPECT_FALSE(l.isEmpty());
l -= 1;
EXPECT_FALSE(l.isEmpty());
l -= 2;
EXPECT_TRUE(l.isEmpty());
}

TEST(ListTest, RemoveTest_TwoElementsInListRemove2_1) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(2, "Zwei");
l += tin1;
l += tin2;
EXPECT_FALSE(l.isEmpty());
l -= 2;
EXPECT_FALSE(l.isEmpty());
l -= 1;
EXPECT_TRUE(l.isEmpty());
}

TEST(ListTest, RemoveTest_TwoElementsWithSameKey) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(1, "Zwei");
l += tin1;
l += tin2;
EXPECT_FALSE(l.isEmpty());
l -= 1;
EXPECT_TRUE(l.isEmpty());
}

TEST(ListTest, RemoveTest_KeyNotExisting) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(2, "Zwei");
l += tin1;
l += tin2;

EXPECT_FALSE(l.isEmpty());
l -= 3;

EXPECT_EQ(*l.search(1), "Eins");
EXPECT_EQ(*l.search(2), "Zwei");
}

// sort

TEST(ListTest, SortTest_OneElementInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin(1, "Eins");
l += tin;
auto lessThan = [](int x, int y) { return x < y; };
EXPECT_TRUE(l.isSorted(lessThan));

}

TEST(ListTest, SortTest_NoElementInList) {
list<int, std::string> l;
auto lessThan = [](int x, int y) { return x < y; };
EXPECT_TRUE(l.isSorted(lessThan));
}

TEST(ListTest, SortTest_TwoElementsInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(2, "Zwei");
l += tin2;
l += tin1;
auto lessThan = [](int x, int y) { return x < y; };
EXPECT_FALSE(l.isSorted(lessThan));
l.sort(lessThan);
EXPECT_TRUE(l.isSorted(lessThan));
}

TEST(ListTest, SortTest_ThreeElementsInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(1, "Eins");
std::tuple<int, std::string> tin2(2, "Zwei");
std::tuple<int, std::string> tin3(3, "Drei");
l += tin3;
l += tin2;
l += tin1;
auto lessThan = [](int x, int y) { return x < y; };
EXPECT_FALSE(l.isSorted(lessThan));
l.sort(lessThan);
EXPECT_TRUE(l.isSorted(lessThan));
}

TEST(ListTest, SortTest_SevenElementsInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(2, "");
std::tuple<int, std::string> tin2(15, "");
std::tuple<int, std::string> tin3(43, "");
std::tuple<int, std::string> tin4(17, "");
std::tuple<int, std::string> tin5(4, "");
std::tuple<int, std::string> tin6(8, "");
std::tuple<int, std::string> tin7(47, "");
l += tin1;
l += tin2;
l += tin3;
l += tin4;
l += tin5;
l += tin6;
l += tin7;
auto lessThan = [](int x, int y) { return x < y; };
EXPECT_FALSE(l.isSorted(lessThan));
l.sort(lessThan);
EXPECT_TRUE(l.isSorted(lessThan));
auto greaterThan = [](int x, int y) { return x > y; };
EXPECT_FALSE(l.isSorted(greaterThan));
l.sort(greaterThan);
EXPECT_TRUE(l.isSorted(greaterThan));
}

TEST(ListTest, SortTest_ReverseOrderWithOneCorrectInList) {
list<int, std::string> l;
std::tuple<int, std::string> tin1(10, "");
std::tuple<int, std::string> tin2(9, "");
std::tuple<int, std::string> tin3(7, "");
std::tuple<int, std::string> tin4(5, "");
std::tuple<int, std::string> tin5(3, "");
std::tuple<int, std::string> tin6(1, "");
std::tuple<int, std::string> tin7(2, "");
l += tin1;
l += tin2;
l += tin3;
l += tin4;
l += tin5;
l += tin6;
l += tin7;
auto lessThan = [](int x, int y) { return x < y; };
EXPECT_FALSE(l.isSorted(lessThan));
l.sort(lessThan);
EXPECT_TRUE(l.isSorted(lessThan));
auto greaterThan = [](int x, int y) { return x > y; };
EXPECT_FALSE(l.isSorted(greaterThan));
l.sort(greaterThan);
EXPECT_TRUE(l.isSorted(greaterThan));
}


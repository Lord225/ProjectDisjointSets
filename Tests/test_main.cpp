#include "pch.h"
#include <vector>
#include "../ProjectDisjointSets/Implementations/DisjointSetMap.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetList.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTrees.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesCom.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesComRan.h"
#include "../ProjectDisjointSets/Implementations/DisjointSetTreesRan.h"

#define MAKE_SET_TEST_MACRO(TestName, Implementation) TEST(TestMakeSet, TestName) { \
auto set = Implementation<int>(); \
const auto el1 = set.MakeSet(0); \
const auto el2 = set.MakeSet(1); \
EXPECT_EQ(set.GetElement(el1), 0); \
EXPECT_EQ(set.GetElement(el2), 1); \
} \

#define FIND_SET_TEST_MACRO(TestName, Implementation) TEST(TestFind, TestName) { \
auto set = Implementation<int>();\
auto universe = std::vector<Implementation<int>::NodeType>();\
\
for (int i = 0; i < 10; i++) {\
	universe.emplace_back(set.MakeSet(i));\
}\
set.Union(universe[0], universe[1]);\
ASSERT_EQ(set.Find(universe[0]), set.Find(universe[1]));\
set.Union(universe[2], universe[3]);\
ASSERT_EQ(set.Find(universe[2]), set.Find(universe[3]));\
set.Union(universe[0], universe[2]);\
ASSERT_EQ(set.Find(universe[0]), set.Find(universe[0]));\
ASSERT_EQ(set.Find(universe[0]), set.Find(universe[1]));\
ASSERT_EQ(set.Find(universe[0]), set.Find(universe[2]));\
ASSERT_EQ(set.Find(universe[0]), set.Find(universe[3]));\
for (size_t i = 4; i < 10; i++) {\
	ASSERT_NE(set.Find(universe[0]), set.Find(universe[i]));\
}\
set.Union(universe[4], universe[5]);\
set.Union(universe[6], universe[7]);\
ASSERT_NE(set.Find(universe[4]), set.Find(universe[6]));\
ASSERT_NE(set.Find(universe[5]), set.Find(universe[6]));\
ASSERT_NE(set.Find(universe[4]), set.Find(universe[7]));\
ASSERT_NE(set.Find(universe[5]), set.Find(universe[7]));}

#define UNION_SET_TEST_MACRO(TestName, Implementation) TEST(TestUnion, TestName) { \
auto set = Implementation<int>();\
auto universe = std::vector<Implementation<int>::NodeType>();\
for (int i = 0; i < 100; i++) {\
	universe.emplace_back(set.MakeSet(i));\
}\
for (int i = 1; i < 100; i++) {\
	set.Union(universe[0], universe[i]);\
}\
for (int i = 1; i < 100; i++) {\
	ASSERT_EQ(set.Find(universe[0]), set.Find(universe[i]));\
}\
universe.emplace_back(set.MakeSet(101));\
\
for (int i = 0; i < 100; i++) {\
	ASSERT_NE(set.Find(universe[i]), set.Find(universe[100]));\
}\
auto set2 = Implementation<int>();\
auto universe2 = std::vector<Implementation<int>::NodeType>();\
for (int i = 0; i < 100; i++) {\
	universe2.emplace_back(set2.MakeSet(i));\
}\
for (int i = 0; i < 49; i++) {\
	set2.Union(universe2[i], universe2[i + 1]);\
}\
for (int i = 50; i < 99; i++) {\
	set2.Union(universe2[i], universe2[i + 1]);\
}\
for (int i = 1; i < 50; i++) {\
	ASSERT_EQ(set2.Find(universe2[0]), set2.Find(universe2[i]));\
	ASSERT_EQ(set2.Find(universe2[50]), set2.Find(universe2[i + 50]));\
	ASSERT_NE(set2.Find(universe2[0]), set2.Find(universe2[i + 50]));\
}\
set2.Union(universe2[2], universe2[51]);\
for (int i = 0; i < 100; i++) {\
	for (int j = 0; j < 100; j++) {\
		ASSERT_EQ(set2.Find(universe2[i]), set2.Find(universe2[j]));\
	}\
}}\

namespace Tests
{
	MAKE_SET_TEST_MACRO(MapTest, MapImplementation::DisjointSetMap);
	MAKE_SET_TEST_MACRO(ListTest, ListImplementation::DisjointSetList);
	MAKE_SET_TEST_MACRO(TreesTest, TreesImplementation::DisjointSetTrees);
	MAKE_SET_TEST_MACRO(TreesComTest, TreesComImplementation::DisjointSetTreesCom);
	MAKE_SET_TEST_MACRO(TreesComRanTest, TreesComRanImplementation::DisjointSetTreesComRan);
	MAKE_SET_TEST_MACRO(TreesRanTest, TreesRanImplementation::DisjointSetTreesRan);

	FIND_SET_TEST_MACRO(MapTest, MapImplementation::DisjointSetMap);
	FIND_SET_TEST_MACRO(ListTest, ListImplementation::DisjointSetList);
	FIND_SET_TEST_MACRO(TreesTest, TreesImplementation::DisjointSetTrees);
	FIND_SET_TEST_MACRO(TreesComTest, TreesComImplementation::DisjointSetTreesCom);
	FIND_SET_TEST_MACRO(TreesComRanTest, TreesComRanImplementation::DisjointSetTreesComRan);
	FIND_SET_TEST_MACRO(TreesRanTest, TreesRanImplementation::DisjointSetTreesRan);

	UNION_SET_TEST_MACRO(MapTest, MapImplementation::DisjointSetMap);
	UNION_SET_TEST_MACRO(ListTest, ListImplementation::DisjointSetList);
	UNION_SET_TEST_MACRO(TreesTest, TreesImplementation::DisjointSetTrees);
	UNION_SET_TEST_MACRO(TreesComTest, TreesComImplementation::DisjointSetTreesCom);
	UNION_SET_TEST_MACRO(TreesComRanTest, TreesComRanImplementation::DisjointSetTreesComRan);
	UNION_SET_TEST_MACRO(TreesRanTest, TreesRanImplementation::DisjointSetTreesRan);

	TEST(TestPreciseUnion, TreesTest) {
		auto set = TreesImplementation::DisjointSetTrees<int>();
		auto universe = std::vector<TreesImplementation::DisjointSetTrees<int>::NodeType>(); 
		for (int i = 0; i < 100; i++) {
			universe.emplace_back(set.MakeSet(i)); 
		}
		auto x = set.Find(universe[0]);

		for (int i = 0; i < 99; i++) {
			set.Union(universe[i+1], universe[i]);
		}

		auto repr = universe[99];
		for (int i = 0; i < 100; i++) {
			ASSERT_EQ(repr, set.Find(universe[i]));
		}
		for (int i = 0; i < 99; i++) {
			ASSERT_EQ(universe[i]->parent, universe[i+1]); 
		}
	}
	TEST(TestPreciseUnion, TreesComTest) {
		auto set = TreesComImplementation::DisjointSetTreesCom<int>();
		auto universe = std::vector<TreesComImplementation::DisjointSetTreesCom<int>::NodeType>();

		for (int i = 0; i < 10; i++) {
			universe.emplace_back(set.MakeSet(i));
		}

		set.Union(universe[0], universe[1]);
		set.Union(universe[0], universe[2]);
		set.Union(universe[0], universe[3]);
		set.Union(universe[4], universe[5]);
		set.Union(universe[5], universe[6]);
		set.Union(universe[1], universe[6]);
		set.Union(universe[7], universe[8]);
		set.Union(universe[8], universe[9]);
		set.Union(universe[0], universe[9]);

		for (int i = 0; i < 10; i++) {
			ASSERT_EQ(set.Find(universe[0]), set.Find(universe[i]));
		}

		const auto x = set.Find(universe[0]);

		for (size_t i = 0; i < 10; i++){
			ASSERT_EQ(universe[0]->parent, x);
		}
	}
	TEST(TestPreciseUnion, TreesRanTest) {
		auto set = TreesRanImplementation::DisjointSetTreesRan<int>();
		auto universe = std::vector<TreesRanImplementation::DisjointSetTreesRan<int>::NodeType>();

		for (int i = 0; i < 10; i++) {
			universe.emplace_back(set.MakeSet(i));
		}

		set.Union(universe[0], universe[1]);

		ASSERT_EQ(universe[0]->rank, 1);
		ASSERT_EQ(universe[1]->rank, 0);

		set.Union(universe[2], universe[3]);
		set.Union(universe[2], universe[1]);

		ASSERT_EQ(universe[0]->rank, 1);
		ASSERT_EQ(universe[1]->rank, 0);
		ASSERT_EQ(universe[2]->rank, 2);
		ASSERT_EQ(universe[3]->rank, 0);

		set.Union(universe[4], universe[5]);
		set.Union(universe[4], universe[2]);

		ASSERT_EQ(universe[0]->rank, 1);
		ASSERT_EQ(universe[1]->rank, 0);
		ASSERT_EQ(universe[2]->rank, 2);
		ASSERT_EQ(universe[3]->rank, 0);
		ASSERT_EQ(universe[4]->rank, 1);
		ASSERT_EQ(universe[5]->rank, 0);

		ASSERT_EQ(universe[4]->parent, universe[2]);
	}
}
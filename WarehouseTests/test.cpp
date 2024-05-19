#include "pch.h"
#include "..\WarehouseProject\Warehouse.cpp"
#include "..\WarehouseProject\StorageSpace.cpp"

TEST(GENERIC, generic_test) {
	EXPECT_TRUE(true);
}

TEST(TestCaseName, TestName) {
	Warehouse warehouse(2);
	warehouse.Put("Cock");
  EXPECT_EQ(warehouse.getSize(), 1);
}
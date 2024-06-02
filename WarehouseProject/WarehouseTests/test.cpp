#include "pch.h"
#include "..\WarehouseApp\Warehouse.h"
#include "..\WarehouseApp\Warehouse.cpp"




TEST(WarehouseTest, Test1) {
    Warehouse test_warehouse("warehouse_data.json");
    ASSERT_FALSE(test_warehouse.find("Foo", "electronics"));
}

TEST(WarehouseTest, Test2) {
    Warehouse test_warehouse("warehouse_data.json");
    test_warehouse.put("Foo", "electronics");
    ASSERT_TRUE(test_warehouse.find("Foo", "electronics"));
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
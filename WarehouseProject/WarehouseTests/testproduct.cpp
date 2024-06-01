#include "pch.h"
#include "..\WarehouseApp\Warehouse.h"
#include "..\WarehouseApp\Warehouse.cpp"




TEST(WarehouseTest, Test1) {
    Warehouse test_warehouse("warehouse_data.json");
    ASSERT_FALSE(test_warehouse.find("Foo", "Electronics"));
}

TEST(WarehouseTest, Test2) {
    Warehouse test_warehouse("warehouse_data.json");
    test_warehouse.put("Foo", "Electronics");
    ASSERT_TRUE(test_warehouse.find("Foo", "Electronics"));
}

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}
#include "pch.h"
#include "..\WarehouseApp\Warehouse.h"
#include "..\WarehouseApp\Warehouse.cpp"




TEST(WarehouseTest, Test1) {
    Warehouse test_warehouse("warehouse_data.json");
}

TEST(WarehouseTest, Test2) {
    Warehouse test_warehouse("warehouse_data.json");
    test_warehouse.acceptDelivery("InitialDelivery.json")
    ASSERT_TRUE(test_warehouse.find("Laptop Lenovo Legion V"));
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
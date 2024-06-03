#include "pch.h"
#include "..\WarehouseApp\Warehouse.h"
#include "..\WarehouseApp\Warehouse.cpp"

#include "..\WarehouseApp\StorageSpace.h"
#include "..\WarehouseApp\StorageSpace.cpp"

#include "..\WarehouseApp\Area.h"
#include "..\WarehouseApp\Area.cpp"

#include "..\WarehouseApp\Shelving.h"
#include "..\WarehouseApp\Shelving.cpp"

#include "..\WarehouseApp\Box.h"
#include "..\WarehouseApp\Box.cpp"

#include "..\WarehouseApp\Product.h"
#include "..\WarehouseApp\Product.cpp"



TEST(WarehouseTest, Test1) {
    Warehouse test_warehouse("../WarehouseApp/warehouse_data.json");
}

TEST(WarehouseTest, Test2) {
    Warehouse test_warehouse("warehouse_data.json");
    test_warehouse.acceptDelivery("delivery1.json");
    ASSERT_TRUE(test_warehouse.find("NVIDIA GeForce GTX 1660 Super"));
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
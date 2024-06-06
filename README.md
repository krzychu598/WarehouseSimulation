# Warehouse Project

Team 209.5-magazyn
Krzysztof Wnorowski, Maksymilian Zieliński, Paweł Marton

## WarehouseApp :
The Warehouse App project consists of several classes representing real-life warehouse-related objects. Below is an overview of the main classes and their functionalities:

### StorageSpace
The StorageSpace class is a base class for storage-related functionalities. It handles attributes and methods related to the size of storage spaces.

### Warehouse
The Warehouse class is a subclass of StorageSpace and represents the core concept of the warehouse in the project. It contains instances of the Area class and is responsible for initializing the state of warehouse based on a json file, accepting and sending out deliveries.

### Area
inherits from StorageSpace and represents an area within the warehouse. Contains instances of 'Shelving'. It handles operations related to storing and retrieving items from boxes on shelves. Shelvings have different priorities representing how easy it is to access them.

### Shelving
The Shelving class represents a shelf within an area. It inherits from StorageSpace and contains instances of InBox. It handles operations related to storing and retrieving items from boxes on shelves. Shelvings have different priorities representing how easy it is to access it.

### Box
The Box class represents a generic container used for storing products within the warehouse. It serves as the base class for more specialized types of boxes, such as InBox and OutBox, which respectively handle storage inside the warehouse and sending out deliveries.

### Employee
Each employee has level of experience that determines their performance. To do any action Employee of specified profession must be free.

### Product
it has attributes for type, kind, name and more.

## BoxGenerator :
Project works in parallel with WarehouseApp. It generates files representing deliveries and requests. It simulates economic trends, making generation less random. All functionality is included inside a Delivery class.

### Delivery
Based on templates, delivery class instances create json files of specified type and size. Products included in files are partially random. The frequency of appearance, however, is influenced by supply/demand and current trends.  
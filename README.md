# 209.5 Magazyn

Team 209.5-magazyn
Krzysztof Wnorowski, Maksymilian Zieliński, Paweł Marton

## An idea to build upon:
* There is a base class StorageSpace
* Warehouse is a subclass of StorageSpace that represents the concept given as a project topic.
* Warehouse contains a few StorageArea class instances. StorageArea inherits from StorageSpace and is used to store different kinds of specified products.
* Warehouse should have a method which role is to assign new products and/or deliveries to appropriate StorageArea based on its location and type of stored products.
* All actions performed should be preserved in a log so they can be seen easily.

You're welcome to suggest any changes.
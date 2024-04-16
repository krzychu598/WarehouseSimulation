# 209.5 Magazyn

Team 209.5-magazyn
Krzysztof Wnorowski, Maksymilian Zieliński, Paweł Marton

## Our initial idea :
* There is a base class StorageSpace
* Warehouse is a subclass of StorageSpace that represents the concept given as a project topic.
* Warehouse contains a few Area class instances. Area inherits from StorageSpace and is used to store different kinds of specified products.
* Warehouse should have a method which role is to assign new products and/or deliveries to appropriate Area based and type of stored products.
* Then Area class instance assigns products based on its priority to Shelving class.
* Shelving class instances have different access methods. Shelving with priority A can be accessed by standard employees while these of priotity C can only be accessed by employees with forklift. That is why most commonly used products should be stored in highest-class shelvings.
* Shelving class instances have fixed size. They can be filled with boxes and they themselves contain products.
* Both Boxes and individual products may be accessed.
* To do any action Employee of specified profession must be free.
* Every action takes time. No action can be performed if all employees are occupied.
* All actions performed should be preserved in a log so they can be seen easily. Log updates dynamically.
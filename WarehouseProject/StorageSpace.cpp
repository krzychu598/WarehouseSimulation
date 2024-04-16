#include "StorageSpace.h"

StorageSpace::StorageSpace(int s){
	size = s;
}
int StorageSpace::GetSize() const {
	return size;
}
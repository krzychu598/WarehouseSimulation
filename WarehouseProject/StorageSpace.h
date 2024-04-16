#pragma once
class StorageSpace
{
public:
	int GetSize() const;
protected:
	StorageSpace(int size);
	int size;
};


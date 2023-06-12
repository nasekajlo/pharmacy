#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Drug.h"

typedef int ID;


template <typename Product>
class Storage {
	std::vector<Product> products;
public:
	Storage(std::vector<Product> products) :
		products(products) {};

	virtual ~Storage() {};
	
	bool isAvailable(ID id) {
		for (int i = 0; i < products.size(); i++) {
			if (products[i].id == id)
				return true;
		}
		return false;
	}

	void addProductToWaitingList(Product product) {
		this->products.push_back(product);
	}
};
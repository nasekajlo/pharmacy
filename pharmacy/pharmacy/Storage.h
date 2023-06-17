#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Drug.h"

typedef int ID;

// <product, amount on the storage>
template <typename Product>
class Storage {
	std::vector <std::pair<Product, int>> products;
public:
	Storage(std::vector <std::pair<Product, int>> products) :
		products(products) {};

	Storage() {};
	virtual ~Storage() {};
	
	bool isAvailable(std::string name) {
		for (int i = 0; i < products.size(); i++) {
			if (products[i].first->name == name)
				return true;
		}
		return false;
	}
	Product getProduct(std::string name) {
		for (int i = 0; i < products.size(); i++) {
			if (products[i].first->name == name)
				return products[i].first;
		}
	}
	void addProductToWaitingList(Product product, int desired_quantity) {
		bool isExist = 0;
		for (int i = 0; i < products.size(); i++) {
			if (products[i].first->name == product->name)
			{
				products[i].second = desired_quantity;
				isExist = 1;
			}
				
		}
		if (!isExist)
			this->products.push_back(std::make_pair(product, desired_quantity));
	}

	//decrease waiting time for ordered drugs
	//decrease tha quantity of the sold drug by sold quantity
	void updateStorage(Product& product, int quantity_sold) {
		for (int i = 0; i < products.size(); i++) {
			if (products[i].first->waiting_time != 0) {
				products[i].first->waiting_time--;
			}
			if (products[i].first->id == product->id) {
				products[i].second -= quantity_sold;
			}
		}
	}

	int getQuantityOnStorage(Product product) {
		for (int i = 0; i < products.size(); i++) {
			if (products[i].first->name == product->name)
				return products[i].second;
		}
	}
};
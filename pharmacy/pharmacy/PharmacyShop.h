#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <time.h>
#include "Storage.h"
#include "Seller.h"
#include "Customer.h"
#include "Drug.h"

template <typename Product>
class PharmacyShop {
private:
	std::string name;
	Storage<Product> storage;
	Seller seller;
public:
	PharmacyShop(Storage<Product> storage, Seller seller, std::string name) :
		storage(storage), seller(seller), name(name) {};

	void greeting() {
		std::cout << seller;
		std::cout << "You are welcome to " << name << std::endl;
	}

	void askForPurchase(Customer& customer) {
		std::cout << "What do you want to buy, " << customer.getName() << "?" << std::endl;
	}
	
	bool isAvailable(std::string name) {
		return storage.isAvailable(name);
	}

	Product getProduct(std::string name) {
		return storage.getProduct(name);
	}
	void printInformationAboutDrug(Product product) {
		product->printInformation();
	}

	bool needPrescription(Product product) {
		return product->need_prescription;
	}

	void askForPrescription() {
		std::cout << "Do you have prescription for this drug?" << std::endl;
		std::cout << "Type 'yes' or 'no'" << std::endl;
	}
	
	//random quantity of day for waiting an ordered product
	void orderProduct(Product product, int desired_quantity) {
		srand(time(NULL));
		int waiting_time = 2;
		product->setWaitingTime(waiting_time);
		storage.addProductToWaitingList(product, desired_quantity);
		int quantity_sold = 0;
		storage.updateStorage(product, quantity_sold);
	}

	bool sellProduct(Product product, int quantity_sold, Customer& customer) {
		int general_quantity = storage.getQuantityOnStorage(product);
		if (general_quantity < quantity_sold) {
			return 0;
		}
		else {
			storage.updateStorage(product, quantity_sold);
			customer.addToReceipt(product->price * quantity_sold);
			return 1;
		}
	}
};
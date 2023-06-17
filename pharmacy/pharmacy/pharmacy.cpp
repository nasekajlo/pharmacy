// pharmacy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include "Customer.h"
#include "Drug.h"
#include "PharmacyShop.h"
#include "Seller.h"
#include "Storage.h"

typedef int ID;

int main()
{
	std::ifstream fin("drugs.txt");
	std::vector<std::pair<Drug*, int>> products;
	for (int i = 0; i < 100; i++) {
		std::string name;
		fin >> name;
		ID id;
		fin >> id;
		float price;
		fin >> price;
		std::string producent;
		fin >> producent;
		int quantity_on_storage;
		fin >> quantity_on_storage;
		if (i % 4 == 0) {
			DrugWithPrescription* drug_prescription = new DrugWithPrescription(name, id, price, producent);
			products.push_back(std::make_pair(drug_prescription, quantity_on_storage));
		}
		else {
			DrugNonPrescription* drug_non_prescription = new DrugNonPrescription(name, id, price, producent);
			products.push_back(std::make_pair(drug_non_prescription, quantity_on_storage));
		}
	}
	Storage<Drug*> storage(products);
	Seller seller(10, "John");
	PharmacyShop<Drug*> pharmacy_shop(storage, seller, "Apotheke");
	//Customer customer;
	std::cout << "What are your ID and name?" << std::endl;
	ID id;
	while (std::cin >> id) {
		std::cin.ignore();
		std::string name;
		std::getline(std::cin, name);
		Customer customer(id, name);
		pharmacy_shop.greeting();
		pharmacy_shop.askForPurchase(customer);
		std::string drug_name;
		while (std::cin >> drug_name) {
			if (pharmacy_shop.isAvailable(drug_name)) {
				pharmacy_shop.printInformationAboutDrug(pharmacy_shop.getProduct(drug_name));
				if (pharmacy_shop.needPrescription(pharmacy_shop.getProduct(drug_name))) {
					pharmacy_shop.askForPrescription();
					std::string answer;
					while (std::cin >> answer && answer != "yes" && answer != "no") {
						std::cout << "incorrect data" << std::endl;
					}
					if (answer == "yes") {
						std::cout << "What quantity of " << drug_name << " do you need?" << std::endl;
						int quantity;
						std::cin >> quantity;
						if (pharmacy_shop.sellProduct(pharmacy_shop.getProduct(drug_name), quantity, customer)) {
							std::cout << "Nice, you can take this drugs" << std::endl;
						}
						else {
							std::cout << "There is no so many drugs on the storage" << std::endl;
	
							std::cout << "Do you want to order it?" << std::endl;
							std::cout << "Type 'yes' or 'no'" << std::endl;
							std::string answer;
							while (std::cin >> answer && answer != "yes" && answer != "no") {
								std::cout << "incorrect data" << std::endl;
							}
							if (answer == "yes") {
								std::cout << "How many drugs do you want to order?" << std::endl;
								int desired_quantity;
								std::cin >> desired_quantity;
								srand(time(NULL));
								pharmacy_shop.orderProduct(pharmacy_shop.getProduct(drug_name), desired_quantity);
								std::cout << "Nice, you have ordered " << drug_name << std::endl;
								std::cout << "You have to wait for it from 1 to 3 days" << std::endl;
							}
						}
					}
					else {
						std::cout << "You need a prescription, sorry(" << std::endl;
					}
				}
				else
				{
					std::cout << "What quantity of " << drug_name << " do you need?" << std::endl;
					int quantity;
					std::cin >> quantity;
					if (pharmacy_shop.sellProduct(pharmacy_shop.getProduct(drug_name), quantity, customer)) {
						std::cout << "Nice, you can take this drugs" << std::endl;
					}
					else {
						std::cout << "There is no so many drugs on the storage, choose another one!" << std::endl;
						std::cout << "Sorry, but this drug is not available now, you can order it and wait for it" << std::endl;
						std::cout << "Do you want to order it?" << std::endl;
						std::cout << "Type 'yes' or 'no'" << std::endl;
						std::string answer;
						while (std::cin >> answer && answer != "yes" && answer != "no") {
							std::cout << "incorrect data" << std::endl;
						}
						if (answer == "yes") {
							std::cout << "How many drugs do you want to order?" << std::endl;
							int desired_quantity;
							std::cin >> desired_quantity;
							srand(time(NULL));
							//int waiting_time = rand() % 100 + 1;
			
							pharmacy_shop.orderProduct(pharmacy_shop.getProduct(drug_name), desired_quantity);
							std::cout << "Nice, you have ordered " << drug_name << std::endl;
							std::cout << "You have to wait for it from 1 to 3 days" << std::endl;
						}
					}
				}
			}
			else
			{
				std::cout << "Sorry, but this drug is not available now, you can order it and wait for it" << std::endl;
				std::cout << "Do you want to order it?" << std::endl;
				std::cout << "Type 'yes' or 'no'" << std::endl;
				std::string answer;
				while (std::cin >> answer && answer != "yes" && answer != "no") {
					std::cout << "incorrect data" << std::endl;
				}
				if (answer == "yes") {
					std::cout << "How many drugs do you want to order?" << std::endl;
					int desired_quantity;
					std::cin >> desired_quantity;
					//srand(time(NULL));
					//int waiting_time = rand() % 3 + 1;
					ID id = rand() % 1000000 + 100;
					PRICE price = rand() % 100 + 10;
					std::string producent = "Ukrain";
					Drug* new_drug = new DrugWithPrescription(drug_name, id, price, producent, desired_quantity);
					pharmacy_shop.orderProduct(new_drug, desired_quantity);
					std::cout << "Nice, you have ordered " << drug_name << std::endl;
					std::cout << "You have to wait for it from 1 to 3 days" << std::endl;
				}
			}
			std::cout << "Do you want to contiunue purchases?" << std::endl;
			std::cout << "Type 'yes' or 'no'" << std::endl;
			std::string answer;
			while (std::cin >> answer && answer != "yes" && answer != "no") {
				std::cout << "incorrect data" << std::endl;
			}
			if (answer == "yes") {
				pharmacy_shop.askForPurchase(customer);
			}
			else {
				int receipt = customer.getReceipt();
				std::cout << "Thank you for your purchases!" << std::endl;
				std::cout << "Your receipt is " << receipt << "$." << std::endl;
				std::cout << "See you next time!" << std::endl;
				break;
			}
		}
		std::cout << "Please, next person" << std::endl;
		std::cout << "What are your ID and name?" << std::endl;
	}
}
 

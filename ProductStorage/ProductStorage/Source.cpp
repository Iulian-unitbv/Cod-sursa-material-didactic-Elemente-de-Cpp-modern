#include <iostream>

#include "ProductsDatabase.h"

int main() {

	db::ProductStorage storage;
	if (!storage.Initialize())
	{
		std::cout << "Failed to initialize the database!";
		return -1;
	}

	auto products = storage.GetProducts();
	for (const auto& product : products)
		std::cout << product;

	while (true)
	{
		std::cout << "Enter the product ID to add to the shopping basket, or enter \'0\' to exit: ";
		int productId;
		std::cin >> productId;
		if (productId == 0)
			break;

		std::cout << "Enter the quantity: ";
		int quantity;
		std::cin >> quantity;
		storage.AddProductToShoppingBasket(productId, quantity);
	}

	auto rows = storage.GetBasket();

	double totalPrice = 0.;
	for (const auto& row : rows)
	{
		const auto& [name, price, quantity] = row;
		std::cout << "name: " << name <<
			", price: " << price <<
			", quantity: " << quantity << std::endl;
		totalPrice += price * quantity;
	}
	std::cout << "Total price: " << totalPrice << "\n";

	return 0;
}
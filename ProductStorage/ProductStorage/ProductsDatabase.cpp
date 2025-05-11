#include "ProductsDatabase.h"

using namespace db;

bool ProductStorage::Initialize()
{
	m_db.sync_schema();
	auto initProductsCount = m_db.count<Product>();
	if (initProductsCount == 0)
		PopulateStorage();

	auto productsCount = m_db.count<Product>();
	return productsCount != 0;
}

void ProductStorage::PopulateStorage()
{
	std::vector<Product> products{
			Product{ -1, "Milk",  5.f },
			Product{ -1, "Egg",   0.2f },
			Product{ -1, "Flour", 2.f },
			Product{ -1, "Butter", 8.f },
			Product{ -1, "Salt",  2.f },
			Product{ -1, "Jam",   5.f }
	};
	m_db.insert_range(products.begin(), products.end());
}

std::vector<Product> ProductStorage::GetProducts()
{
	return m_db.get_all<Product>();
}

void ProductStorage::AddProductToShoppingBasket(int productId, int quantity)
{
	ShoppingBasketRow sbrow;
	sbrow.SetIdProduct(productId);
	sbrow.SetQuantity(quantity);
	m_db.insert(sbrow);
	//m_db.insert(ShoppingBasketRow{ -1, productId ,quantity });
}

std::vector<std::tuple<std::string, float, int>> ProductStorage::GetBasket()
{
	return m_db.select(
		sql::columns(&Product::GetName, &Product::GetPrice, &ShoppingBasketRow::GetQuantity),
		sql::inner_join<ShoppingBasketRow>(sql::on(sql::c(&Product::GetId) == &ShoppingBasketRow::GetIdPoduct))
	);
}

#include "Product.h"
#include <format>

using namespace db;


int Product::GetId() const
{
	return m_id;
}

Product::Product(int id, const std::string& name, float price)
	:m_id{ id }, m_name{ name }, m_price{ price }
{
}

std::string Product::GetName()const
{
	return m_name;
}

float Product::GetPrice()const
{
	return m_price;
}

void Product::SetId(int id)
{
	m_id = id;
}

void Product::SetName(const std::string& name)
{
	m_name = name;
}

void Product::SetPrice(float price)
{
	m_price = price;
}

std::ostream& db::operator<<(std::ostream& out, const Product& product)
{
	return out << std::format("id: {}, name: {}, price: {}\n",
		product.GetId(),
		product.GetName(),
		product.GetPrice());
}

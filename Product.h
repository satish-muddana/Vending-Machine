
#ifndef PRODUCT_H
#define PRODUCT_H

#include<string>
using namespace std;

class Product {
	private:
		int productId;
		string productName;
        int productPrice;

	public:
        Product();
        Product(int, string, int);
        const string getProductName();
        const int getProductId();
        const int getProductPrice();
        void setProductName(string);
        void setProductId(int);
        void setPrice(int);
};

Product::Product() {
    this->productId = 0;
    this->productName = "";
    this->productPrice = 0;
}

Product::Product(int productId, string productName, int productPrice) {
    this->productId = productId;
    this->productName = productName;
    this->productPrice = productPrice;
}

const string Product::getProductName() {
    return productName;
}

const int Product::getProductId() {
    return productId;
}

const int Product::getProductPrice() {
    return productPrice;
}

void Product::setProductName(string productName) {
    productName = productName;
}

void Product::setProductId(int productId) {
    productId = productId;
}

void Product::setPrice(int price) {
    productPrice = price;
}

#endif
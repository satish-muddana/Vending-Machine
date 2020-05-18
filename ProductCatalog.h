#include<map>
#include<iostream>
#include<iomanip>
#include "Product.h"

using namespace std;

class ProductCatalog {
    private:
        map<int, Product*> mapProducts;
        map<int, int> productCnt;
    public:
        ProductCatalog();
        void initialize();
        void addProducts(Product*, int);
        void removeProducts(int);
        void emptyProducts();
        Product* getProduct(int);
        bool checkProductStatus(int);
        bool checkProductQuantity(int, int);
        void displayProducts();
        void updateCatalog(map<int, int>& currMapProducts);
        void insertDefaultProducts();
        void insertDefaultQuantity();
        void updateProduct(int, int);
        void addQuantity(int, int);
        void removeQuantity(int, int);

};

ProductCatalog::ProductCatalog() {
    initialize();
}

void ProductCatalog::initialize() {
    insertDefaultProducts();
    insertDefaultQuantity();
    return;
}


void ProductCatalog::insertDefaultQuantity() {
    map<int, Product*>::iterator iter;
    for (iter = mapProducts.begin(); iter != mapProducts.end(); iter++) {
        Product *currProduct = iter->second;
        int productId = currProduct->getProductId();
        productCnt[productId] = 15;
    }
}

void ProductCatalog::insertDefaultProducts() {
    mapProducts[1] = new Product(1, "Oreo", 200);
    mapProducts[2] = new Product(2, "KitKat", 175);
    mapProducts[3] = new Product(3, "Coke", 225);
    mapProducts[4] = new Product(4, "Lays", 150);
    mapProducts[5] = new Product(5, "Bagel", 200);
    mapProducts[6] = new Product(6, "Snicker", 250);
    mapProducts[7] = new Product(7, "Cheetos", 100);
    mapProducts[8] = new Product(8, "Peanuts", 95);
    mapProducts[9] = new Product(9, "Noodles", 150);
    mapProducts[10] = new Product(10, "Pasta", 500);
    mapProducts[11] = new Product(11, "Reeses", 400);
    mapProducts[12] = new Product(12, "Burger", 700);
}

void ProductCatalog::addProducts(Product* currProduct, int productQuantity = 0) {
    int productId = currProduct->getProductId();
    if (mapProducts.find(productId) == mapProducts.end()) {
        mapProducts[productId] = currProduct;
    }
    addQuantity(productId, productQuantity);
    return;
}

void ProductCatalog::addQuantity(int productId, int productQuantity) {
    if (productCnt.find(productId) == productCnt.end()) {
        productCnt[productId] = 0;
    }
    productCnt[productId] += productQuantity;
    return;
}

void ProductCatalog::removeProducts(int productId) {
    if (mapProducts.find(productId) != mapProducts.end()) {
        mapProducts.erase(productId);
    }
    if (productCnt.find(productId) != productCnt.end()) {
        productCnt.erase(productId);
    }
    return;
}

void ProductCatalog::removeQuantity(int productId, int productQuantity) {
    if (productCnt.find(productId) != productCnt.end()) {
        productCnt[productId] -= productQuantity;
        productCnt[productId] = max(0, productCnt[productId]);
    }
    return;
}

void ProductCatalog::emptyProducts() {
    mapProducts.clear();
    productCnt.clear();
    return;
}

Product* ProductCatalog::getProduct(int productId) {
    if (mapProducts.find(productId) != mapProducts.end()) {
        return mapProducts[productId];
    }
    Product *emptyProduct = new Product();
    return emptyProduct;
}

bool ProductCatalog::checkProductStatus(int productId) {
    return (mapProducts.find(productId) != mapProducts.end());
}

bool ProductCatalog::checkProductQuantity(int productId, int productQuanity) {
    if (productCnt.find(productId) != productCnt.end()) {
        return productQuanity <= productCnt[productId];
    }
    return false;
}

void ProductCatalog::displayProducts() {
    map<int, int>::iterator iter;
    std::cout << endl;
    std::cout << "PRODUCTS LIST:" << endl;
    std::cout << "************************************************************" << endl;
    std::cout << "Product Name" << " \t | " << "Product Id" << " \t | " << "Product Price" << " | "<< "Quantity" << endl;
    std::cout << "************************************************************" << endl;
    for (iter = productCnt.begin(); iter != productCnt.end(); iter++) {
        int productId = iter->first;
        Product *prod = mapProducts[productId];
        std::cout << prod->getProductName() << "\t\t" << " | " << prod->getProductId() << "\t\t" << " | " << (double)prod->getProductPrice()/100 << "\t\t" << " | "<< iter->second << endl;
    }
    std::cout << endl;
    return;
}
void ProductCatalog::updateProduct(int productId, int productQuantity) {
    productCnt[productId] -= productQuantity;
}

void ProductCatalog::updateCatalog(map<int, int>& currMapProducts) {
    map<int, int>::iterator iter;
    for (iter = currMapProducts.begin(); iter != currMapProducts.end(); iter++) {
        if (productCnt.find(iter->first) != productCnt.end()) {
            productCnt[iter->first] += iter->second;
        }
    }
    return;
}
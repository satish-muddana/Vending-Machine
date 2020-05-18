#include<map>
#include<iostream>
#include "Product.h"

using namespace std;

class Cart {
    private:
        map<int, int> mapCartItems;

    public:
        void addItemToCart(int, int);
        void removeItemFromCart(int, int);
        void changeQuantity(int, int);
        void emptyCart();
        map<int, int> getItemsFromCart();
        int checkOut(); 
        void changeQuantity(int, bool);     
};

map<int, int> Cart::getItemsFromCart() {
    return mapCartItems;
}

void Cart::emptyCart() {
    mapCartItems.clear();
}

void Cart::addItemToCart(int productId, int productQuantity) {
    if (mapCartItems.find(productId) == mapCartItems.end()) {
        mapCartItems[productId] = 0;
    }
    mapCartItems[productId] += productQuantity;
    return;
}

void Cart::removeItemFromCart(int productId, int productQuantity) {
    if (mapCartItems.find(productId) != mapCartItems.end()) {
        mapCartItems[productId] -= productQuantity;
        mapCartItems[productId] = max(0, mapCartItems[productId]);
    }
    return;
}
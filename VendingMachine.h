#include<string>
#include<vector>
#include "ProductCatalog.h"
#include "DenominationCatalog.h"
#include "Cart.h"

using namespace std;

class VendingMachine {
    private:
        ProductCatalog *prodCat;
        DenominationCatalog *denCat;
        map<Product, int> cart;
        int amount;
        int amountInserted;
        Cart *myCart;
        bool adminUser;

    public:
        VendingMachine();
        void initialize();
        bool processRefund(int);
        void cancelTransaction();
        void processTransaction(int);
        void addProductsToCart();
        void addProductsToCatalog();
        void removeProductsFromCatalog();
        void emptyProductsFromCatalog();
        void addDenominations();
        void removeDenominations();
        void emptyDenominations();
        void addDenominationTypes();
        void removeDenominationTypes();
        void resetMachine();
        int checkOut();
        void enterCash(int);
        void cartOptions();
        void paymentOptions();
        void denominationOptions();
        void userOptions();
        void userInitialize();
        void adminInitialize();
        void displayProducts();
        void showDenominations();
        ~VendingMachine();
};

VendingMachine::VendingMachine() {
    prodCat = new ProductCatalog();
    denCat = new DenominationCatalog();
    myCart = new Cart();
    adminUser = false;
    initialize();
}

VendingMachine::~VendingMachine() {
    if (prodCat) {
        prodCat = NULL;
        delete prodCat;
    }
    if (denCat) {
        denCat = NULL;
        delete denCat;
    }
    if (myCart) {
        myCart = NULL;
        delete myCart;
    }
}

void VendingMachine::userOptions() {
    std::cout << "USER OPTIONS:" << endl;
    std::cout << " 1        --> ADMIN ACCESS." << endl;
    std::cout << " 2        --> USER ACCESS." << endl;
    std::cout << endl;
    std::cout << "YOUR INPUT : ";
}

void VendingMachine::initialize() {
    std::cout << endl;
    userOptions();
    string input = "";
    cin >> input;
    if (input == "1") {
        adminUser = true;
        adminInitialize();
        initialize();
    }
    else if (input == "2") {
        adminUser = false;
        userInitialize();
    }
    else {
        cout << "SELECT CORRECT OPTION" << endl;
        initialize();
    }
    return;
}

void VendingMachine::displayProducts() {
    prodCat->displayProducts();
}

void VendingMachine::adminInitialize() {
    string input = "";
    bool optionsFlag = true;
    while (optionsFlag) {
        cartOptions();
        cin >> input;
        int inputVal = 0;
        try {
            inputVal = stoi(input);
        }
        catch (...){
            inputVal = 0;
        }
        switch(inputVal) {
            case 1:
                addProductsToCatalog();
                break;
            case 2:
                removeProductsFromCatalog();
                break;
            case 3:
                emptyProductsFromCatalog();
                break;
            case 4:
                displayProducts();
                break;
            case 5:
                addDenominations();
                break;
            case 6:
                removeDenominations();
                break;
            case 7:
                emptyDenominations();
                break;
            case 8:
                showDenominations();
                break;
            case 9:
                addDenominationTypes();
                break;
            case 10:
                removeDenominationTypes();
                break;
            case 11:
                resetMachine();
                break;
            default:
                optionsFlag = false;
                break;
        }
    }

}

void VendingMachine::emptyProductsFromCatalog() {
    prodCat->emptyProducts();
}

void VendingMachine::addDenominationTypes() {
    string denominationType = "";
    int denominationValue = 0;

    std::cout << "Enter Denomination Type" << endl;
    cin >> denominationType;

    std::cout << "Enter Denomination Value" << endl;
    cin >> denominationValue;

    denCat->addDenominationTypes(denominationType, denominationValue);
    return;

}

void VendingMachine::removeDenominationTypes() {
    string denominationType = "";

    std::cout << "Enter Denomination Type" << endl;
    cin >> denominationType;

    denCat->removeDenominationTypes(denominationType);
    return;
}

void VendingMachine::removeProductsFromCatalog() {
    int productId = 0;

    std::cout << "Enter Product Id : ";
    cin >> productId;
    prodCat->removeProducts(productId);
    return;

}

void VendingMachine::showDenominations() {
    denCat->showDenominations();
    return;
}

void VendingMachine::addProductsToCatalog() {
    int productId = 0, productPrice = 0, productQuantity = 0;
    string productName = "";

    std::cout << "Enter Product Id : ";
    cin >> productId;

    std::cout << "Enter Product Price : ";
    cin >> productPrice;

    std::cout << "Enter Product Name : ";
    cin >> productName;

    std::cout << "Enter Product Quanitity : ";
    cin >> productQuantity;

    Product *currProduct = new Product(productId, productName, productPrice);
    prodCat->addProducts(currProduct, productQuantity);
}

void VendingMachine::addDenominations() {
    int denominationFlag = 0, denominationQuantity = 0;

    denominationOptions();
    cin >> denominationFlag;

    std::cout << "Add Denomination Quantity" << endl;
    cin >> denominationQuantity;
    denCat->addDenominations(denominationFlag, denominationQuantity);
    return;
}

void VendingMachine::emptyDenominations() {
    denCat->emptyDenominations();
}

void VendingMachine::removeDenominations() {
    int denominationFlag = 0, denominationQuantity = 0;

    denominationOptions();
    cin >> denominationFlag;

    std::cout << "Add Denomination Quantity" << endl;
    cin >> denominationQuantity;
    denCat->removeDenominations(denominationFlag, denominationQuantity);
    return;
}

void VendingMachine::userInitialize() {
    std::cout << endl;
    map<int, int> checkOutProducts;
    prodCat->displayProducts();
    addProductsToCart();
}

bool VendingMachine::processRefund(int refundPrice) {
    vector<string> vecDenominations = denCat->getAvailableDenominations();
    map<string, int> refundDenominations;

    for (int i = 0; i < vecDenominations.size() && refundPrice != 0; i++) {
        int denominationValue = denCat->getDenominationValue(vecDenominations[i]);
        int numDenominations = 0;
        if (refundPrice > denominationValue) {
            numDenominations = refundPrice / denominationValue;
            if (denCat->getNumDenominations(vecDenominations[i]) < numDenominations) {
                std::cout << "SORRY FOR THE INCONVENIENCE. WE DO NOT HAVE ENOUGH FUNDS TO PROCESS THE CHANGE." << endl;
                return false;
            }
            refundDenominations[vecDenominations[i]] = numDenominations;
            refundPrice -= numDenominations * denominationValue;
        }
    }
    denCat->updateDenominations(refundDenominations);
    return true;
}

void VendingMachine::cancelTransaction() {
    map<int, int> currMapProducts;
    currMapProducts = myCart->getItemsFromCart();
    prodCat->updateCatalog(currMapProducts);
    myCart->emptyCart();
    std::cout << "!!!!! YOUR TRANSACTION IS CANCELLED !!!!!" << endl;
    initialize();
    return;
}

void VendingMachine::processTransaction(int refundPrice) {
    if (!processRefund(refundPrice)) {
        cancelTransaction();
        return;
    }
    myCart->emptyCart();
    if (refundPrice > 0) {
        std::cout << "PLEASE COLLECT THE CHANGE: " << (double)refundPrice/100 << " USD" << endl;
    }
    std::cout << "YOUR TRANSACTION IS SUCCESSFULL." << endl;
    std::cout << "PLEASE COLLECT YOUR ITEMS." << endl;
    initialize();
    return;
}

void VendingMachine::addProductsToCart() {
    int productId = 0, productQuantity = 0;
    string flag = "";
    int inputVal = 0;
    while (true) {
        productId = 0;
        productQuantity = 0;
        flag = "";
        cartOptions();
        
        cin >> flag;

        try {
            inputVal = stoi(flag);
        }
        catch(...) {
            inputVal = 0;
        }

        if (inputVal == 1) {
            prodCat->displayProducts();
            std::cout << "Enter PRODUCT ID : ";
            cin >> productId;
            if (!prodCat->checkProductStatus(productId)) {
                std::cout << "The selected product is not available. Please add a different product" << endl;
                continue;
            }
            std::cout << "Enter QUANTITY   : ";
            cin >> productQuantity;
            if (!prodCat->checkProductQuantity(productId, productQuantity)) {
                std::cout << "We don't have the Stock. Please select the available quantity." << endl;
                continue;
            }
            myCart->addItemToCart(productId, productQuantity);
            prodCat->updateProduct(productId, productQuantity);
            std::cout << endl;
            std::cout << "********************************" << endl;;
            std::cout << "Item Added to Cart Successfully" << endl;
            std::cout << "********************************" << endl;
            std::cout << endl;
        }
        else if (inputVal == 2) {
            map<int, int> mapProducts;
            map<int, int>::iterator iter;
            mapProducts = myCart->getItemsFromCart();
            std::cout << endl;
            std::cout << " MY CART:" << endl;
            std::cout << endl;
            std::cout << "********************************************" << endl;
            std::cout << "Product Name" << " \t | " << "Product Price" << " | "<< "Quantity" << endl;
            std::cout << "********************************************" << endl;
            for (iter = mapProducts.begin(); iter != mapProducts.end(); iter++) {
                Product *currProduct = prodCat->getProduct(iter->first);
                std::cout << currProduct->getProductName() << "\t\t" << " | " << (double)currProduct->getProductPrice()/100 << "\t\t" << " | "<< iter->second << endl;
            }
            std::cout << endl;
        }
        else if (inputVal == 3) {

            if ((myCart->getItemsFromCart()).empty()) {
                std::cout << "YOUR CART IS EMPTY" << endl;
                std::cout << "PLEASE ADD ITEMS TO YOUR CART BEFORE CHECKING OUT" << endl;
            }

            int totalPrice = checkOut();

            std::cout << endl;
            std::cout << "TOTAL COST : " << double(totalPrice)/100 << " USD" << endl;
            std::cout << endl;
            enterCash(totalPrice);
        }
        else {
            cancelTransaction();
            break;
        }
    }
    return;
}

int VendingMachine::checkOut() {
    map<int, int> currProducts;
    map<int, int>::iterator iter;
    currProducts = myCart->getItemsFromCart();
    int totalPrice = 0;
    for (iter = currProducts.begin(); iter != currProducts.end(); iter++) {
        Product* currProduct = prodCat->getProduct(iter->first);
        totalPrice += currProduct->getProductPrice() * iter->second;
    }
    return totalPrice;
}

void VendingMachine::paymentOptions() {
    std::cout << "PAYMENT OPTIONS:" << endl;
    std::cout << " 1        --> ADD DENOMINATION." << endl;
    std::cout << " 2        --> PROCESS TRANSACTION." << endl;
    std::cout << " ANY KEY  --> CANCEL the TRANSACTION." << endl;
    std::cout << endl;
    std::cout << "YOUR INPUT : ";
    return;
}

void VendingMachine::denominationOptions() {
    std::cout << endl;

    std::cout << "DENOMINATION OPTIONS:" << endl;

    vector<string> availableDenominations;
    availableDenominations = denCat->getAvailableDenominations();
    for (int i = 0; i < availableDenominations.size(); i++) {
        std::cout << " " << i+1 << "        --> " << availableDenominations[i] << endl;
    }
    std::cout << " ANY KEY  --> CANCEL the TRANSACTION." << endl;
    std::cout << endl;
    std::cout << "YOUR INPUT : ";

}

void VendingMachine::resetMachine() {
    prodCat->initialize();
    denCat->initialize();
    return;
}

void VendingMachine::enterCash(int totalPrice) {
    int denominationFlag = 0;
    string flag = "";
    int enteredPrice = 0;
    string denominationType = "";
    int inputVal = 0;
    int denominationQuantity = 0;

    while (true) {
        flag = "";
        denominationFlag = 0;
        paymentOptions();
        cin >> flag;

        try {
            inputVal = stoi(flag);
        }
        catch(...) {
            inputVal = 0;
        }

        if (inputVal == 1) {
            denominationOptions();
            cin >> denominationFlag;
            cout << "Enter Denomination Quantity" << endl;
            cin >> denominationQuantity;
            denominationType = denCat->getDenominationType(denominationFlag);
            denCat->addDenomination(denominationType);
            enteredPrice += denCat->getDenominationValue(denominationType);
            std::cout << endl;
            std::cout << "TOTAL AMOUNT ENTERED : " << (double)enteredPrice/100 << " USD" << endl;
            std::cout << endl;
        }
        else if (inputVal == 2) {
            if (enteredPrice < totalPrice) {
                std::cout << "INSUFFICIENT AMOUNT. PLEASE ENTER THE CORRECT AMOUNT" << endl;
                cout << endl;
                continue;
            }
            else {
                processTransaction(enteredPrice - totalPrice);
            }
            break;
        }
        else {
            cancelTransaction();
            break;
        }
    }
    return;
}

void VendingMachine::cartOptions() {
    std::cout << "CART OPTIONS:" << endl;
    if (adminUser) {
        std::cout << " 1        --> ADD PRODUCTS." << endl;
        std::cout << " 2        --> REMOVE PRODUCTS." << endl;
        std::cout << " 3        --> EMPTY PRODUCTS." << endl;
        std::cout << " 4        --> DISPLAY PRODUCTS." << endl;
        std::cout << " 5        --> ADD DENOMINATIONS." << endl;
        std::cout << " 6        --> REMOVE DENOMINATIONS." << endl;
        std::cout << " 7        --> EMPTY DENOMINATIONS." << endl;
        std::cout << " 8        --> SHOW DENOMINATIONS." << endl;
        std::cout << " 9        --> REMOVE DENOMINATION TYPES." << endl;
        std::cout << " 10       --> REMOVE DENOMINATION TYPES." << endl;
        std::cout << " 11       --> RESET MACHINE." << endl;
        std::cout << " ANY KEY  --> CANCEL." << endl;
    }
    else {
        std::cout << " 1        --> ADD an Item to the CART." << endl;
        std::cout << " 2        --> VIEW the items in the CART." << endl; 
        std::cout << " 3        --> CHECKOUT the CART." << endl;
        std::cout << " ANY KEY  --> CANCEL the TRANSACTION." << endl;
    }
    
    std::cout  << endl;
    std::cout  << "YOUR INPUT : ";
}
#include<map>
#include<string>
#include<vector>
using namespace std;

class DenominationCatalog {
    private:
        map<string, int> mapDenominations;
        map<string, int> mapdenominationValue;

        vector<string> availableDenominations;
    public:
        DenominationCatalog();
        void defaultDenominationTypes();
        void addDenominationTypes(string, int);
        void removeDenominationTypes(string);
        void initialize();
        void addDenominations(int, int);
        void removeDenominations(int, int);
        void emptyDenominations();
        vector<string> getAvailableDenominations();
        void addDenomination(string);
        int getDenominationValue(string);
        void emptyCatalog();
        int getNumDenominations(string);
        void updateDenominations(map<string, int>&);
        string getDenominationType(int);
        void defaultDenominations();
        int totalCash();
        void defaultDenominationValues();
        void showDenominations();
};


DenominationCatalog::DenominationCatalog() {
    initialize();
}

string DenominationCatalog::getDenominationType(int denominationFlag) {
    return availableDenominations[denominationFlag-1];
}

void DenominationCatalog::emptyDenominations() {
    map<string, int>::iterator iter;
    for (iter = mapDenominations.begin(); iter != mapDenominations.end(); iter++) {
        mapDenominations[iter->first] = 0;
    }
    return;
}

void DenominationCatalog::addDenominationTypes(string denominationType, int denominationValue) {
    vector<string>::iterator iter;
    for (iter = availableDenominations.begin(); iter != availableDenominations.end(); iter++) {
        if (*iter == denominationType) {
            mapdenominationValue[denominationType] = denominationValue;
            return;
        }
    }
    availableDenominations.push_back(denominationType);
    mapdenominationValue[denominationType] = denominationValue;
    return;
}

void DenominationCatalog::removeDenominationTypes(string denominationType) {
    vector<string>::iterator iter;
    for (iter = availableDenominations.begin(); iter != availableDenominations.end(); iter++) {
        if (*iter == denominationType) {
            availableDenominations.erase(iter);
            break;
        }
    }
    mapdenominationValue[denominationType] = 0;
    mapDenominations[denominationType] = 0;
    return;
}

void DenominationCatalog::defaultDenominationTypes() {
    availableDenominations.push_back("TEN");
    availableDenominations.push_back("DOLLAR");
    availableDenominations.push_back("QUARTER");
    availableDenominations.push_back("DIME");
    availableDenominations.push_back("CENT");

}

void DenominationCatalog::defaultDenominationValues() {
    for (int i = 0; i < availableDenominations.size(); i++) {
        if (availableDenominations[i] == "TEN") {
            mapdenominationValue[availableDenominations[i]] = 1000;
        }
        else if (availableDenominations[i] == "DOLLAR") {
            mapdenominationValue[availableDenominations[i]] = 100;
        }
        else if (availableDenominations[i] == "QUARTER") {
            mapdenominationValue[availableDenominations[i]] = 25;
        }
        else if (availableDenominations[i] == "DIME") {
            mapdenominationValue[availableDenominations[i]] = 10;
        }
        else if (availableDenominations[i] == "CENT") {
            mapdenominationValue[availableDenominations[i]] = 1;
        }
        else {
            mapdenominationValue[availableDenominations[i]] = 0;
        }
        
    }
    return;
}

void DenominationCatalog::initialize() {
    defaultDenominationTypes();
    defaultDenominations();
    defaultDenominationValues();
    return;
}

void DenominationCatalog::defaultDenominations() {
    for (int i = 0; i < availableDenominations.size(); i++) {
        mapDenominations[availableDenominations[i]] = 100;
    }
    return;
}

void DenominationCatalog::addDenominations(int denominationFlag, int denominationQuantity) {
    string denominationType = "";
    denominationType = availableDenominations[denominationFlag-1];
    if (mapDenominations.find(denominationType) != mapDenominations.end()) {
        mapDenominations[denominationType] += denominationQuantity;
    }
    return;
}

void DenominationCatalog::removeDenominations(int denominationFlag, int denominationQuantity) {
    string denominationType = "";
    denominationType = availableDenominations[denominationFlag-1];
    if (mapDenominations.find(denominationType) != mapDenominations.end()) {
        mapDenominations[denominationType] -= denominationQuantity;
        mapDenominations[denominationType] = max(0, mapDenominations[denominationType]);
    }
    return;
}

void DenominationCatalog::addDenomination(string denominationType) {
    mapDenominations[denominationType] += 1;
    return;
}

vector<string> DenominationCatalog::getAvailableDenominations() {
    return availableDenominations;
}

int DenominationCatalog::getDenominationValue(string denominationType) {
    if (mapdenominationValue.find(denominationType) != mapdenominationValue.end()) {
        return mapdenominationValue[denominationType];
    }
    return 0;
}

void DenominationCatalog::emptyCatalog() {
    map<string, int>::iterator iter;
    for (iter = mapDenominations.begin(); iter != mapDenominations.end(); iter++) {
        iter->second = 0;
    }
    return;
}

int DenominationCatalog::getNumDenominations(string denominationType) {
    return mapDenominations[denominationType];
}

void DenominationCatalog::updateDenominations(map<string, int>& currDenominations) {
    map<string, int>::iterator iter;
    for (iter = currDenominations.begin(); iter != currDenominations.end(); iter++) {
        mapDenominations[iter->first] -= iter->second;
    }
    return;
}

int DenominationCatalog::totalCash() {
    map<string, int>::iterator iter;
    int totalPrice = 0;
    for (iter = mapDenominations.begin(); iter != mapDenominations.end(); iter++) {
        if (mapdenominationValue.find(iter->first) != mapdenominationValue.end())
            totalPrice += mapdenominationValue[iter->first] * iter->second;
    }
    return totalPrice;
}

void DenominationCatalog::showDenominations() {
    map<string, int>::iterator iter;
    std::cout << endl;
    std::cout << "DENOMINATIONS LIST:" << endl;
    std::cout << "********************************" << endl;
    std::cout << "Denomination Name" <<  " | "<< "Quantity" << endl;
    std::cout << "********************************" << endl;
    for (iter = mapDenominations.begin(); iter != mapDenominations.end(); iter++) {
        std::cout << iter->first << "\t\t" << " | " << iter->second << endl;
    }
    std::cout << endl;
    return;
}
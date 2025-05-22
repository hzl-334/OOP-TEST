
// order class 
class Order{
private:
vector<string> flavorOptions = {"Vanilla", "Chocolate", "Strawberry"};
vector<string> sizeOptions = {"Small", "Medium", "Large"};

public:
Order(string f, unique_ptr<Topping> t, string s): flavor(f), topping(move(t)), size(s) {}

void show() const {
    cout << " - Flavor: " << flavor << "\n";
    cout << " - Topping: " << topping << "\n";
    cout << " - Size: " << size << "\n";
    }

    // Getters
    string getFlavor() const { return flavor; }
    string getSize() const { return size; }
    string getToppingName() const { return topping->getName(); }
    string getToppingType() const { return topping->getType(); }


}; 


// sundae class represents sundae built
class Sundae {
public:
    string flavor;
    string topping;
    string size;

    void build() {
        cout << "\nBuild the sundae!\n";
        cout << "Choose the correct flavor (Vanilla, Chocolate, Strawberry): ";
        getline(cin, flavor);
        cout << "Choose the correct topping (Sprinkles, Cherry, Oreos): ";
        getline(cin, topping);
        cout << "Choose the correct size (Small, Medium, Large): ";
        getline(cin, size);
    }
};

//ingredient class
class Ingredient {
public:
    virtual string getName() const = 0;
    virtual string getCategory() const = 0;
    virtual ~Ingredient() {}
};
// //mixins 
// class MixIns:public Ingredient{

// }; 

// //syrups 
// class Syrup:public Ingredient{

// }; 

//topping class
class Topping : public Ingredient {
public:
    virtual string getType() const = 0;  
    string getCategory() const override { return "Topping"; }
};

//different toppings subclass 
class FruitTopping : public Topping {
private:
    string name;

public:
    FruitTopping(string n) : name(n) {}
    string getName() const override { return name; }
    string getType() const override { return "Fruit topping"; }
};

class SweetTopping : public Topping {
private:
    string name;

public:
    SweetTopping(string n) : name(n) {}
    string getName() const override { return name; }
    string getType() const override { return "Sweet topping"; }
};

class ToppingList {
private:
    vector<function<unique_ptr<FruitTopping>()>> fruitOptions;
    vector<function<unique_ptr<SweetTopping>()>> sweetOptions;

public:
    ToppingList() {
        fruitOptions.push_back([]() { return make_unique<FruitTopping>("Banana"); });
        fruitOptions.push_back([]() { return make_unique<FruitTopping>("Cherry"); });

        sweetOptions.push_back([]() { return make_unique<SweetTopping>("Sprinkles"); });
        sweetOptions.push_back([]() { return make_unique<SweetTopping>("Oreos"); });
    }

    unique_ptr<Topping> getRandomFruitTopping() const {
        int index = rand() % fruitOptions.size();
        return fruitOptions[index]();
    }

    unique_ptr<Topping> getRandomSweetTopping() const {
        int index = rand() % sweetOptions.size();
        return sweetOptions[index]();
    }

    unique_ptr<Topping> getRandomTopping() const {
        vector<function<unique_ptr<Topping>()>> all;

        for (const auto& f : fruitOptions)
            all.push_back([=]() { return f(); });

        for (const auto& s : sweetOptions)
            all.push_back([=]() { return s(); });

        int index = rand() % all.size();
        return all[index]();
    }
};

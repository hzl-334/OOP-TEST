#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <cstdlib> 
#include <string> 
using namespace std; 


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


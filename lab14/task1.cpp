#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RecipeTemplate {
protected:
    vector<string> ingredients;

    virtual void listIngredients() {
        cout << "Ingredients:" << endl;
        for (const auto& ingredient : ingredients) {
            cout << "- " << ingredient << endl;
        }
    }

    virtual void prepareRecipe() = 0;

    virtual void serveDish() {
        cout << "Serve the dish" << endl;
    }

public:
    void makeRecipe() {
        listIngredients();
        prepareRecipe();
        serveDish();
    }

    virtual ~RecipeTemplate() = default;
};

class CakeRecipe : public RecipeTemplate {
public:
    CakeRecipe() {
        ingredients = {"Flour", "Sugar", "Eggs", "Butter", "Baking Powder"};
    }

    void prepareRecipe() override {
        cout << "Preparing cake:" << endl;
        cout << "1. Mix dry ingredients" << endl;
        cout << "2. Cream butter and sugar" << endl;
        cout << "3. Add eggs one at a time" << endl;
        cout << "4. Combine all and bake at 350°F for 30 minutes" << endl;
    }

    void serveDish() override {
        cout << "Serve the cake with frosting" << endl;
    }
};

class SaladRecipe : public RecipeTemplate {
public:
    SaladRecipe() {
        ingredients = {"Lettuce", "Potatoes", "Cucumber", "Olive Oil", "Sour cream"};
    }

    void prepareRecipe() override {
        cout << "Preparing salad:" << endl;
        cout << "1. Wash, peel and cook the potatoes" << endl;
        cout << "2. Wash and chop vegetables" << endl;
        cout << "3. Mix in a bowl" << endl;
        cout << "4. Drizzle with oil and Sour cream" << endl;
        cout << "5. Toss gently" << endl;
    }
};

int main() {
    RecipeTemplate* cake = new CakeRecipe();
    RecipeTemplate* salad = new SaladRecipe();

    cout << "Making Cake:" << endl;
    cake->makeRecipe();

    cout << "\nMaking Salad:" << endl;
    salad->makeRecipe();

    delete cake;
    delete salad;

    return 0;
}
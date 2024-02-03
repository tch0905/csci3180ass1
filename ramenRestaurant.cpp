//submit this file

#include "ramenRestaurant.h"
#include "noodle.h"
#include "soup.h"
#include "pork.h"
#include <iostream>
using std::cout;
using std::endl;

RamenRestaurant::RamenRestaurant(int ingredientStorageCapacity) : ingredientStorageCapacity(ingredientStorageCapacity)
{
    ingredientStorage = new Ingredient*[ingredientStorageCapacity]; //create a dynamic array of Ingredient pointers, of size ingredientStorageCapacity
    for(int i=0; i<ingredientStorageCapacity; i++) //we should set all ingredientStorage slots to nullptr's since our storage is literally empty at the beginning
        ingredientStorage[i] = nullptr;
}

RamenRestaurant::~RamenRestaurant()
{
    //TODO: implement this function
    //Hint: use "delete" for non-array dynamic objects, and use "delete []" for dynamic arrays


}

bool RamenRestaurant::isStorageFull()
{
    return ingredientStorageUsed == ingredientStorageCapacity;
}

void RamenRestaurant::addFoodToStorage(Ingredient* food)
{
    for(int i = 0; i < ingredientStorageCapacity; i++)
    {
        if(ingredientStorage[i] == nullptr) //check if we have found the first non-empty storage slot
        {
            ingredientStorage[i] = food; //add the ingredient to that slot then
            break; //this is important to stop our loop here: what would happen if we don't?
        }
    }
    ingredientStorageUsed++; //update the state
}

bool RamenRestaurant::prepareNoodle(int softness)
{
    if(isStorageFull()) //cannot prepare new noodles when the storage is full
    {
        cout << "Whoops! No more storage space for the new noodle! :(" << endl;
        return false;
    }
    addFoodToStorage(new Noodle(softness)); //prepare it and store it
    cout << "Noodle (" << softness << "% softness) has been prepared and added to storage! :)" << endl;
    return true;
}

bool RamenRestaurant::prepareSoup(int spiciness)
{
    if(isStorageFull()) //cannot prepare new soup when the storage is full
    {
        cout << "Whoops! No more storage space for the new soup! :(" << endl;
        return false;
    }
    addFoodToStorage(new Soup(spiciness)); //prepare it and store it
    cout << "Soup (" << spiciness << "% spiciness) has been prepared and added to storage! :)" << endl;
    return true;
}

bool RamenRestaurant::preparePork()
{
    if(isStorageFull()) //cannot prepare new pork when the storage is full
    {
        cout << "Whoops! No more storage space for the new pork! :(" << endl;
        return false;
    }
    addFoodToStorage(new Pork()); //prepare it and store it
    cout << "Pork has been prepared and added to storage! :)" << endl;
    return true;
}

bool RamenRestaurant::prepareAndServeRamen(int requiredNoodleSoftness, int requiredSoupSpiciness, bool doublePork)
{
    //TODO: implement this function
    /*
        Hint:
        ingredientStorage[i] is merely an Ingredient pointer.
        Therefore, you cannot directly use it like a Noodle pointer even though the object it points to is actually a Noodle object. For example, the following won't compile:
            cout << ingredientStorage[i]->getSoftness() << endl;
        In C++, you can use dynamic_cast for trying to cast it to a Noodle pointer like this:
            Noodle* realNoodlePointer = dynamic_cast<Noodle*>(ingredientStorage[i]);
        The good thing about dynamic_cast is that it gives you a nullptr if the casting fails when ingredientStorage[i] doesn't really point to a Noodle object.
        It is useful for checking what object it is pointing to.
        Of course, before you do dynamic_cast, you should make sure ingredientStorage[i] is not really a nullptr itself first.
    */
    /*
        Please copy and use the following for the success message:
        cout << "Ramen has been skillfully prepared and happily served! :)" << endl;

        Please copy and use the following for the failure message:
        cout << "Oh no, we cannot prepare the ramen requested! :(" << endl;
    */
    int num_pork = doublePork ? 2 :1;
    cout << "prepareAndServeRamen running"  << endl;
    cout << "The requiredNoodleSoftness is equal to " << requiredNoodleSoftness<< endl;
    cout << "The requiredSoupSpiciness is equal to " << requiredSoupSpiciness<< endl;
    if (ingredientStorage == nullptr) {
        cout << "Oh no, we cannot prepare the ramen requested! :(" << endl;
        return false;
    }

    // Check each ingredient in ingredientStorage
    for (int i = 0; i < ingredientStorageCapacity; i++) {
        cout << "For loop i = " << i  << endl;
        // Make sure ingredientStorage[i] is not nullptr
        if (ingredientStorage[i] != nullptr) {
            // Check if ingredientStorage[i] points to a Noodle object
            cout << "ingredientStorage[i] != nullptr "  << endl;
            Noodle* noodlePtr = dynamic_cast<Noodle*>(ingredientStorage[i]);
            // Not necessary code just for checking and debuging
            if (noodlePtr == nullptr) {
                cout << "noodlePtr == nullptr"  << endl;
                cout << "This is not Noodle, next slot plz"  << endl;
                break;
            }
            if (noodlePtr != nullptr) {
                // Check required noodle softness
                cout << "noodlePtr != nullptr"  << endl;
                cout << "the noodlePtr->getSoftness() = " << noodlePtr->getSoftness() << endl;
                if (noodlePtr->getSoftness() > requiredNoodleSoftness) {
                    cout << "the noodlePtr->getSoftness() > requiredNoodleSoftness" << endl;
                    cout << "Ramen has been skillfully prepared and happily served! :)" << endl;
                    return true;
                }
            }
        }
    }

    // If all checks pass, ramen can be prepared and served
    cout << "Oh no, we cannot prepare the ramen requested! :(" << endl;
    return false;

}

void RamenRestaurant::update()
{
    //update the states for each of the ingredients stored
    for(int i = 0; i < ingredientStorageCapacity; i++)
        if(ingredientStorage[i] != nullptr) //of course, we have to make sure the current storage slot is not really empty
            ingredientStorage[i]->update(); //so update it
}

void RamenRestaurant::print()
{
    cout << "Currently, we have " << ingredientStorageUsed << " ingredient" << (ingredientStorageUsed!=1?"s":"") << " in the restaurant storage: " << endl;
    for(int i = 0; i < ingredientStorageCapacity; i++) //go through our whole ingredient storage
    {
        cout << "Slot " << i << ": ";
        if(ingredientStorage[i] == nullptr) //nullptr means an empty slot at index i
            cout << "empty";
        else
            ingredientStorage[i]->print(); //invoke the print function for the ingredient - it will call the correct function (Noodle's or Soup's) depending on the actual class of the object the pointer points to: it is a dynamic binding
        cout << endl;
    }
    cout << "And... " << ramenServed << " bowl" << (ramenServed!=1?"s":"") << " of Hellish Teemo Ramen proudly served so far!" << endl;
    cout << endl;
}

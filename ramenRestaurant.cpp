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
    for (int i = 0; i < ingredientStorageCapacity; i++) {
        delete ingredientStorage[i];
    }
//    delete[] ingredientStorage;


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


    // Check if ingredientStorage is nullptr
    if (ingredientStorage == nullptr) {
//        cout << "Oh no, we cannot prepare the ramen requested! :(" << endl;
        return false;
    }

    int num_pork = doublePork ? 2 :1;

    Noodle* suitableNoodle = nullptr;
    Soup* suitableSoup = nullptr;
    Pork* suitablePork1 = nullptr;
    Pork* suitablePork2 = nullptr;
    int back_index[4] = {-1,-1,-1,-1};


//    use for debug only
//    cout << "prepareAndServeRamen running"  << endl;
//    cout << "The requiredNoodleSoftness is equal to " << requiredNoodleSoftness<< endl;
//    cout << "The requiredSoupSpiciness is equal to " << requiredSoupSpiciness<< endl;


    // Check each ingredient in ingredientStorage
    for (int i = 0; i < ingredientStorageCapacity; i++) {
//        cout << "For loop i = " << i << endl;
        if (suitableNoodle != nullptr && suitableSoup != nullptr && suitablePork1 != nullptr &&
            (num_pork == 1 || suitablePork2 != nullptr))
            break;
        // find it is suitable noodle or soup or pork
        if (suitableNoodle == nullptr) {
            Noodle *nP = dynamic_cast<Noodle *> (ingredientStorage[i]);
            if ((nP != nullptr && nP->isGood())&& nP->getSoftness() >= requiredNoodleSoftness) {
                back_index[0] = i;
                suitableNoodle = nP;
                ingredientStorage[i] = nullptr;
                continue;
            }
        }
        if (suitableSoup == nullptr) {
            Soup *sP = dynamic_cast<Soup *> (ingredientStorage[i]);
            if (( sP != nullptr && sP->isGood()) && sP->getSpiciness() >= requiredSoupSpiciness) {
                back_index[1] = i;
                suitableSoup = sP;
                ingredientStorage[i] = nullptr;
                continue;
            }
        }
        if (suitablePork1 == nullptr) {
            Pork *sPork1 = dynamic_cast<Pork *> (ingredientStorage[i]);
            if (sPork1 != nullptr && sPork1->isGood()) {
                back_index[2] = i;
                suitablePork1 = sPork1;
                ingredientStorage[i] = nullptr;
                continue;
            }
        } else if (suitablePork2 == nullptr) {
            Pork *sPork2 = dynamic_cast<Pork *> (ingredientStorage[i]);
            if ( sPork2 != nullptr  && sPork2->isGood()) {
                back_index[2] = i;
                suitablePork2 = sPork2;
                ingredientStorage[i] = nullptr;
                continue;
            }
        }
    }

    if (suitableNoodle == nullptr || suitableSoup == nullptr ||
        suitablePork1 == nullptr || (num_pork == 2 && suitablePork2 == nullptr)) {
        cout << "Oh no, we cannot prepare the ramen requested! :(" << endl;
        ingredientStorage[back_index[0]] = (back_index[0] != -1) ? suitableNoodle : nullptr;
        ingredientStorage[back_index[1]] = (back_index[1] != -1) ? suitableNoodle : nullptr;
        ingredientStorage[back_index[2]] = (back_index[2] != -1) ? suitableNoodle : nullptr;
        ingredientStorage[back_index[3]] = (back_index[3] != -1) ? suitableNoodle : nullptr;


        return false;

    }

//    delete suitableNoodle;
//    delete suitableSoup;
//    delete suitablePork1;
    ingredientStorageUsed = ingredientStorageUsed -3;
    if (num_pork == 2) {
        delete suitablePork2;
        ingredientStorageUsed--;
    }





    // If all checks pass, ramen can be prepared and served
    ramenServed++;
    cout << "Ramen has been skillfully prepared and happily served! :)" << endl;
    return true;

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

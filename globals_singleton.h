//
// Created by hodyah on 30/12/2019.
//

#ifndef FLIGHT_PROJECT_GLOBALS_SINGLETON_H
#define FLIGHT_PROJECT_GLOBALS_SINGLETON_H

#include "ToAeroplaneClient.h"
#include "FromAeroplaneServer.h"
#include "simpleCommandFromFileToMap.h"

#include <vector>
#include <map>
#include <string>

using namespace std;

typedef vector<string>::iterator iter;

class app  // זה הסינגלטון היחיד שלנו!
{
public:

    static app * globals;

    ToAeroplaneClient * client = nullptr;

    FromAeroplaneServer * server = nullptr;

    map<string, Var *> * varsMap = new map<string, Var *>;

    /** מפת הסוגרים המסולסלים */
    map<iter, iter> * matching_curly_brackets = new map<iter, iter>;

    /**
     דואג להפעיל את המנעול של מפת המשתנים לפני הבלוק ולשחרר אותו אחרי
     */
    template <typename Func> void do_with_vars_map(Func f)
    {
        varsMapMutex.lock();

        f();

        varsMapMutex.unlock();
    }

    friend int main(int, char**); // כדי שמיין תקרא לקונסטרקטור ולדיסטרקטור

private:

    app() = default; // קונסטרקטור שלא עושה כלום, אבל הוא פרטי

    ~app()
    {
        delete client;
        delete server;
        delete matching_curly_brackets;

        do_with_vars_map([&]() {
            for (auto &str_var_pair : *varsMap) {
                delete str_var_pair.second; // delete all vars from the dict
            }
        });

        delete varsMap; // then delete the dict itself
    }

    mutex varsMapMutex;
};

//class DoesNotHaveThisIteratorInMapBrackets: public exception{};
//
//class MapItToBeginBracketSingleton: public Singleton<unordered_map<
//        vector<string>::iterator*, vector<string>::iterator*>> {
//public:
//    /**
//    * @param paren itartor to place in vector that begin block
//    * @return itartor to end block
//    */
//    static vector<string>::iterator getMatchingParen(vector<string>::iterator paren){
//        vector<string>::iterator anserItartor;
//        try{anserItartor = *it->at(&paren);}
//        catch (...){throw DoesNotHaveThisIteratorInMapBrackets();}
//        return anserItartor;
//    }
//    friend class ifWhileCommandFileToMap;
//};

//vector<string>::iterator getMatchingParen(vector<string>::iterator paren){
//    vector<string>::iterator anserItartor;
//    try{anserItartor = *this->mapCloseBracketsIt[&paren];}
//    catch (...){throw NotHaveThisItartorInMapBrackets();}
//    MapItToBeginBracketSingleton::it = this->mapCloseBracketsIt;
//    return anserItartor;
//}
#endif //FLIGHT_PROJECT_GLOBALS_SINGLETON_H
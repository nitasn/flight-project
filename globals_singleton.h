//
// Created by hodyah on 30/12/2019.
//

#ifndef FLIGHT_PROJECT_GLOBALS_SINGLETON_H
#define FLIGHT_PROJECT_GLOBALS_SINGLETON_H

#include "ToAeroplaneClient.h"
#include "FromAeroplaneServer.h"

#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string>::iterator iter;

class app  // זה הסינגלטון היחיד שלנו!
{

public:

    static app * globals;

    /** אם זה טרו, פונקציות שרואות לנכון מוסיפות הדפסות כדי לספר על דברים מעניינים שקורים */
    bool verbose = false;

    ToAeroplaneClient * client = nullptr;

    FromAeroplaneServer * server = nullptr;

    std::map<std::string, Var *> * varsMap = new std::map<std::string, Var *>;

    /** מפת הסוגרים המסולסלים */
    std::map<iter, iter> * matching_curly_brackets = new std::map<iter, iter>;

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

    app() = default; // קונסטרקטור שלא עושה כלום, אבל הוא פרטי כדי שרק מיין יוכל לקרוא לו

    ~app() // גם פרטי - רק מיין יכול לקרוא לו
    {
        delete client;
        delete server;
        delete matching_curly_brackets;

        do_with_vars_map([&]()
        {
            for (auto &str_var_pair : *varsMap)

                delete str_var_pair.second; // delete all var pointers from varsMap

        });

        delete varsMap; // then delete the dict itself
    }

    std::mutex varsMapMutex;
};

#endif //FLIGHT_PROJECT_GLOBALS_SINGLETON_H
//
// Created by hodyah on 30/12/2019.
//

#ifndef FLIGHT_PROJECT_SINGLTONGLOBALS_H
#define FLIGHT_PROJECT_SINGLTONGLOBALS_H
#include "singlton.h"
#include "ToAeroplaneClient.h"
#include "FromAeroplaneServer.h"
#include "simpleCommandFromFileToMap.h"

class ToAeroplaneClientSingleton : public Singleton<ToAeroplaneClient>
{
    friend class connectControlClient; // todo לכתוב ספציפית מי החברים
};

class FromAeroplaneServerSingleton : public Singleton<FromAeroplaneServer>
{
    friend class Command; // todo לכתוב ספציפית מי החברים
};

class VarsMap
{
// todo אם אני עושה דליט למפה, זה עושה דליט לכל המשתנים שבה? לבדוק
public: // todo לכתוב ספציפית מי החברים
    static Singleton<map<string, Var *>> mapSingleton;
    static Singleton<mutex> mutexSingleton;

    // במקום להסתבך עם המנעול בכל שימוש במפה אפשר לשלוח קטע קוד לפונקציה הזאת...
    template <typename Func> static void do_synchronously(Func f)
    {
        VarsMap::mutexSingleton.it->lock();

        f();

        VarsMap::mutexSingleton.it->unlock();
    }
};
#endif //FLIGHT_PROJECT_SINGLTONGLOBALS_H



//
// Created by hodyah on 30/12/2019.
//

#ifndef FLIGHT_PROJECT_SINGLTON_H
#define FLIGHT_PROJECT_SINGLTON_H
template <typename T> class Singleton {
private:

public:
    static T* it; // todo make private and define friends for each sub class
    static void destruct() { delete it; }
};

template <typename T> T* Singleton<T>::it = nullptr;


#endif //FLIGHT_PROJECT_SINGLTON_H

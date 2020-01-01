//#include "controlFly.h"
//#include <unordered_set>
//
//
//using namespace std;
//void parse(vector<string>::iterator& begin);
//
//struct Var {
//    double data;
//    string addressInSimulator;
//};
//
//class Server {
//    unordered_set<string> toRead;
//
//};
//
//unordered_map<string, Var> vars;
//
////template<class T> class Singleton {
////    T *t = nullptr;
////
////public:
////    T* getIt()
////    {
////        if (t == nullptr)
////            t = new T;
////        return t;
////    }
////};
///**
// * print the string if he not var or expression.
// * if she var print her value, if expression calculate him and print
// * @param begin
// */
//void printCommand(vector<string>::iterator& begin) {
//    if (vars.find(*begin) != vars.end()) {
//        cout << vars[*begin].data << endl;
//    } else {
//        Interpreter interp;
//        try {
//            interp.returnNumStack(*begin);
//        } catch (string *error) {
//            cout << *begin << endl;
//        } catch (int error) {
//            Expression* toPrint = interp.interpret(*begin);
//            cout << toPrint->calculate() << endl;
//        }
//    }
//    begin++;
//}
///**
// * sleep the main thread acurdding the number in queue
// * @param inputQueue the command queue
// */
//void sleepCommand(vector<string>::iterator& runOnVector){
//    this_thread::sleep_for(chrono::seconds(atoi(((runOnVector)->c_str()))));
//    runOnVector++;
//}
//
//
//
//
//unordered_map<string, function<void(vector<string>::iterator& runOnVector)>> mapCommandFunctions = {
//        {"if", ifCommand},
//        {"print", printCommand}
//};
//
/////////// VERY IMPORTANT NOTE: VECTOR MUST BEGIN WITH "{" AND END WITH "}"
////void parse(vector<string>::iterator& begin)
////{
////    while (auto iter = begin; iter != end; iter++)
////    {
////        if (mapCommandFunctions.find(*iter) != mapCommandFunctions.end());
////        {
////            auto func = mapCommandFunctions[*iter];
////            func(++iter);
////        } else
////        {
////            // x = 0
////            if (*iter == "}") {
////                iter++;
////                return;
////            }
////        }
////    }
////}
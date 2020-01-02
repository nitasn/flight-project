//
//#include "controlFly.h"
//#include "lexer.h"
//#include "simpleCommandFromFileToMap.h"
//#include "singltonGlobals.h"

/*
 * בייסיקלי מה כל מה שיש כאן פוזר קצת למיין, קצת לפרסר, וקצת לסינגלטון
 */


////
//// Created by hodyah on 20/12/2019.
////
///**
// * controlFly class control all the act in the play.
// * play all the function, save all information and update
// * the method accurding what they need
// */
//void controlFly::playControlFly(string fileCommandName) {
//
//    try{
//        this->lexerFile = (fileCommandName);
//        this->commandVector = lexerFile.splitFile();
//    } catch (...){
//        printf("problem with lexer. check your file\n");
//        return;
//    }
//    try{
//        VarsMap::mutexSingleton.it = new mutex;
//        VarsMap::mapSingleton.it = new map<string, Var*>;
//
//        vector<string>::iterator runOnVactor =  this->commandVector->begin();
//        parse(runOnVactor, this->commandVector->end());
//
//        VarsMap::mutexSingleton.destruct();
//        VarsMap::mapSingleton.destruct();
//
//    }catch (...){
////        delete(*this->varMapUpdateServer, *this->varMapSendClient,
////                *this->commandQueue, this->serverObject);
//    }
//    //TODO close the client and server deldte the command in map
////    delete(*this->varMapUpdateServer, *this->varMapSendClient,
////            *this->commandQueue, this->serverObject);
//}

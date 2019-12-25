////
//// Created by Nitsan BenHanoch on 22/12/2019.
////
//
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//struct strings_array {
//
//    const size_t size;
//    string *const arr; // a const pointer to a mutable array
//
//    explicit strings_array(size_t size) : size(size), arr(new string[size]) {}
//
//    ~strings_array() { delete[] arr; }
//};
//
//strings_array *split(const string &text, char delimiter) { // here i am, reinventing the wheel
//
//    size_t num_elements = count(text.begin(), text.end(), delimiter) + 1;
//    // why does num_elements == count(delimiter) + 1? consider "ab;cd;ef" with the delimiter ';'
//    auto *result = new strings_array(num_elements);
//
//    size_t next_del;
//    size_t prev_del = 0;
//    size_t i = 0; // index to strings_array's arr
//
//    while ((next_del = text.find(delimiter, prev_del)) != string::npos) { // while next del exists
//        result->arr[i++] = text.substr(prev_del, next_del - prev_del); // put substr in strings_array's arr
//        prev_del = next_del + 1; // update prev_del to not include the found delimiter in the next substr
//    }
//    result->arr[i] = text.substr(prev_del); // the substring that's after the last delimiter
//
//    return result;
//}
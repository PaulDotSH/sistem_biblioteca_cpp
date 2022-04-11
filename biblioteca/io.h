//
// Created by administrator on 4/9/22.
//

#ifndef SISTE_BIBLIOTECA_CPP_IO_H
#define SISTE_BIBLIOTECA_CPP_IO_H

#include <iostream>

class IO {
public:
    static IO& GetInstance() {
        // Allocate with `new` in case IO is not trivially destructible.
        static IO* singleton = new IO();
        return *singleton;
    }

    //aici bagi read si write in fisiere la json thingy

    static void TestFunc() {
        std::cout<<"SINGLETON"<<std::endl;
    }

private:
    IO() = default;

    // Delete copy/move so extra instances can't be created/moved.
    IO(const IO&) = delete;
    IO& operator=(const IO&) = delete;
    IO(IO&&) = delete;
    IO& operator=(IO&&) = delete;
};

#endif //SISTE_BIBLIOTECA_CPP_IO_H

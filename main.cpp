#include <iostream>
#include <memory>
#include "DBDriver.h"
#include "MongoDriver.h"


std::shared_ptr<DBDriver> db{new MongoDriver};

void hello()
{
    std::cout << "FUNS-server\nVersion " << 1 << "." << 0 << "\n";
    std::cout << "Using " << db->getDriverName() << " driver." << std::endl;
}

int main( const int, const char** )
{
    hello();
    return EXIT_SUCCESS;
}

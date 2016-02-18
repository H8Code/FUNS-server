#include <iostream>
#include <memory>
#include "Service.h"
#include "MongoDriver.h"


std::shared_ptr<DBDriver> db{new MongoDriver};

void hello()
{
    std::cout << "FUNS-server\nVersion " << 1 << "." << 0 << "\n";
    std::cout << "Using " << db->getDriverName() << " driver." << std::endl;
}

int main( const int, const char** )
{
    auto s = std::make_shared<FUNSService>(db);
    hello();
    s->start();
    return EXIT_SUCCESS;
}

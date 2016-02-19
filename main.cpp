#include <iostream>
#include <memory>
#include "RESTService.h"
#include "MongoDriver.h"


std::shared_ptr<DBDriver> db{new MongoDriver};

void hello()
{
    std::cout << "FUNS-server\nVersion " << 1 << "." << 0 << "\n";
    std::cout << "Using " << db->get_driver_name() << " driver." << std::endl;
}

int main( const int, const char** )
{
    auto s = std::make_shared<RESTService>(db);
    hello();
    s->start();
    return EXIT_SUCCESS;
}

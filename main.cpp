#include "Controller.h"

#ifdef VRJUGGLER
#include <cstdlib>
#include "tp2.h"
#include <vrj/Kernel/Kernel.h>


int main(int argc, char* argv[])
{
    vrj::Kernel* kernel = vrj::Kernel::instance();
    OsgNav application(kernel, argc, argv);

    if ( argc <= 1 )
    {
        std::cout << "\n\nUsage: " << argv[0]
                  << " vjconfigfile\n\n";
        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        kernel->loadConfigFile(argv[i]);
    }

    kernel->start();

    kernel->setApplication(&application);
    kernel->waitForKernelStop();

    new Controller(VRJUGGLER_STRATEGY);
    return 0;
}
#endif

int main()
{
    new Controller(SDL_STRATEGY);
    return 0;
}


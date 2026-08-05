#include <process/Process.hpp>
#include <iostream>

// cree le programme principal
int main(int _argc, char **_argv)
{
    // cree le process principal
    process::Process process(_argc, _argv);
    // execute le process principal
    process.run();

    return 0;
}

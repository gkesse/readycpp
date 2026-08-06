#include <process/Process.hpp>

#include <module/trace/backtrace/Trace.hpp>

// cree le programme principal
int main(int _argc, char **_argv)
{
    // initialise le nom du binaire
    module::trace::backtrace::Trace::setBinaryName(_argv[0]);
    // cree le process principal
    process::Process process(_argc, _argv);
    // execute le process principal
    process.run();

    return 0;
}

#include "module/trace/backtrace/Trace.hpp"

#include <gtest/gtest.h>

int main( int _argc, char** _argv )
{
    module::trace::backtrace::Trace::setBinaryName( _argv[0] );
    ::testing::InitGoogleTest( &_argc, _argv );
    return RUN_ALL_TESTS();
}

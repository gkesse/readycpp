#include <gtest/gtest.h>
#include <module/trace/backtrace/Trace.hpp>

int main( int argc, char** argv )
{
    module::trace::backtrace::Trace::setBinaryName( argv[0] );
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

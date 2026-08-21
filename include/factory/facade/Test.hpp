#pragma once

#include "facade/Test.hpp"

namespace factory::facade
{
// cree une factory facade test
class Test
{
    DECLARE_FACADE_FACTORY( Test, Test )
};
} // namespace factory::facade

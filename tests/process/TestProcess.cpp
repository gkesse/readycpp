#include <process/Process.hpp>

#include <gtest/gtest.h>

namespace process
{
    TEST(TestProcess, Test_General)
    {
        // cree le module process
        Process process;

        // teste le nombre de modules
        EXPECT_TRUE(process.m_module_list.size() == 3);
    }

    TEST(TestProcess, Test_Module_Inconnu)
    {
        // cree le module inconnu
        Process::Module DEF_MODULE_INCONNU{Process::MODULE_TYPE::INCONNU, "inconnu", "Le module est inconnu."};

        // cree le module process
        Process process;

        // recupere le module inconnu
        Process::Module module_inconnu = process.m_module_list.at(0);

        // teste le module inconnu
        EXPECT_TRUE(module_inconnu == DEF_MODULE_INCONNU);
    }
}

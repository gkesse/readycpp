#include <factory/Facade.hpp>

#include <exception/Exception.hpp>
#include <facade/Bdd.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace factory
{
    // cree la classe de fixture
    class TestFacadeFactory : public ::testing::Test
    {
    protected:
        // initialise le test avant son execution
        void SetUp() override {}
        // nettoye le test apres son execution
        void TearDown() override {}
    };

    // teste le chargement d'une factory
    TEST_F(TestFacadeFactory, Test_Chargement_Factory)
    {
        // cree une structure de tests parametriques
        struct TestParam
        {
            int m_index;
            process::Process::Module m_module;
        };

        // cree une liste de structure de tests parametriques
        using TestParamList = std::vector<TestParam>;

        // cree un module bdd
        const process::Process::Module DEF_MODULE_BDD =
            {Facade::MODULE_TYPE::BDD, "MODULE_BDD_NAME", "MODULE_BDD_DESCRIPTION"};

        // remplit une liste de structure de tests parametriques
        const TestParamList test_param_list = {
            // {m_index: 0 | m_module: DEF_MODULE_BDD}
            {0, DEF_MODULE_BDD},
        };

        // execute un test parametrique
        auto runTest = [&](const TestParam &_test_param)
        {
            // cree un mock de process
            process::Process process;

            // initialise les arguments cli
            process.setModule(_test_param.m_module);

            // cree une factory facade
            Facade factory_facade(process);
            Facade::sFacade facade = factory_facade.create();

            EXPECT_TRUE(std::dynamic_pointer_cast<facade::Facade>(facade) != nullptr);
            EXPECT_TRUE(std::dynamic_pointer_cast<facade::Bdd>(facade) != nullptr);
        };

        // execute les tests parametriques
        for (const auto &test_param : test_param_list)
        {
            runTest(test_param);
        }
    }

    // teste le chargement d'une factory invalide
    TEST_F(TestFacadeFactory, Test_Chargement_Factory_Invalide)
    {
        // cree une structure de tests parametriques
        struct TestParam
        {
            int m_index;
            process::Process::Module m_module;
        };

        // cree une liste de structure de tests parametriques
        using TestParamList = std::vector<TestParam>;

        // cree un module help
        const process::Process::Module DEF_MODULE_HELP =
            {Facade::MODULE_TYPE::HELP, "MODULE_BDD_NAME", "MODULE_BDD_DESCRIPTION"};

        // remplit une liste de structure de tests parametriques
        const TestParamList test_param_list = {
            // {m_index: 0 | m_module: DEF_MODULE_HELP}
            {0, DEF_MODULE_HELP},
        };

        // execute un test parametrique
        auto runTest = [&](const TestParam &_test_param)
        {
            // cree un mock de process
            process::Process process;

            // initialise les arguments cli
            process.setModule(_test_param.m_module);

            try
            {
                // cree une factory facade
                Facade factory_facade(process);
                FAIL() << "Exception attendue (execption::Exception) non levee.";
            }
            catch (const exception::Exception &e)
            {
                // teste la capture de l'exception levee
                EXPECT_TRUE(std::string(e.what()) == "Le chargement de la factory fonction a echoue.");
            }
            catch (const std::exception &e)
            {
                // teste la capture de l'exception levee
                EXPECT_TRUE(std::string(e.what()) == "Le chargement de la factory fonction a echoue.");
                FAIL() << "Exception attendue (execption::Exception) non levee.";
            }
            catch (...)
            {
                // teste la capture de l'exception levee
                FAIL() << "Exception attendue (execption::Exception) non levee.";
            }
        };

        // execute les tests parametriques
        for (const auto &test_param : test_param_list)
        {
            runTest(test_param);
        }
    }
}

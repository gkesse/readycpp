#include <exception/process/Module.hpp>

#include <gtest/gtest.h>

namespace exception::process
{
    // cree la classe de fixture
    class TestModule : public ::testing::Test
    {
    protected:
        // initialise le test avant son execution
        void SetUp() override {}
        // nettoye le test apres son execution
        void TearDown() override {}
    };

    // teste la capture de l'exception par defaut
    TEST_F(TestModule, Test_Exception_Par_Defaut)
    {
        try
        {
            // leve une exception
            throw Module();
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (const Module &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "Erreur lors du chargement du module.");
        }
        catch (const exception::Exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "Erreur lors du chargement du module.");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (const std::exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "Erreur lors du chargement du module.");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (...)
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
    }

    // teste la capture de l'exception par donnees
    TEST_F(TestModule, Test_Exception_Par_Donnees)
    {
        try
        {
            // leve une exception
            throw Module("MESSAGE_ERREUR_EXCEPTION_MODULE");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (const Module &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION_MODULE");
        }
        catch (const exception::Exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION_MODULE");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (const std::exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION_MODULE");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (...)
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
    }

    // teste la capture de l'exception parente
    TEST_F(TestModule, Test_Exception_Parente)
    {
        try
        {
            // leve une exception
            throw Module("MESSAGE_ERREUR_EXCEPTION_MODULE");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (const exception::Exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION_MODULE");
        }
        catch (const std::exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION_MODULE");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (...)
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
    }

    // teste la capture de l'exception standard
    TEST_F(TestModule, Test_Exception_Standard)
    {
        try
        {
            // leve une exception
            throw Module("MESSAGE_ERREUR_EXCEPTION_MODULE");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (const std::exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION_MODULE");
        }
        catch (...)
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
    }

    // teste la capture de l'exception globale
    TEST_F(TestModule, Test_Exception_Globale)
    {
        try
        {
            // leve une exception
            throw Module("MESSAGE_ERREUR_EXCEPTION_MODULE");
            FAIL() << "Exception attendue (execption::process::Module) non levee.";
        }
        catch (...)
        {
            // teste l'exception levee
            SUCCEED() << "Exception attendue (execption::process::Module) non levee.";
        }
    }
}

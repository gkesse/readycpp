#include <exception/process/Module.hpp>

#include <gtest/gtest.h>

namespace exception::process
{
    TEST(TestModule, Test_General)
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

    TEST(TestModule, Test_Module)
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

    TEST(TestModule, Test_Exception)
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

    TEST(TestModule, Test_Standard)
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

    TEST(TestModule, Test_Global)
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

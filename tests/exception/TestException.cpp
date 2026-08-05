#include <exception/Exception.hpp>

#include <gtest/gtest.h>

namespace exception
{
    // cree la classe de fixture
    class TestException : public ::testing::Test
    {
    protected:
        // initialise le test avant son execution
        void SetUp() override {}
        // nettoye le test apres son execution
        void TearDown() override {}
    };

    // teste la capture de l'exception par defaut
    TEST_F(TestException, Test_Exception_Par_Defaut)
    {
        try
        {
            // leve une exception
            throw Exception();
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch (const Exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "Un probleme a ete rencontre.");
        }
        catch (const std::exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "Un probleme a ete rencontre.");
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch (...)
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }

    // teste la capture de l'exception par donnees
    TEST_F(TestException, Test_Exception_Par_Donnees)
    {
        try
        {
            // leve une exception
            throw Exception("MESSAGE_ERREUR_EXCEPTION");
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch (const Exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION");
        }
        catch (const std::exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION");
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch (...)
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }

    // teste la capture de l'exception standard
    TEST_F(TestException, Test_Exception_Standard)
    {
        try
        {
            // leve une exception
            throw Exception("MESSAGE_ERREUR_EXCEPTION");
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch (const std::exception &e)
        {
            // teste l'exception levee
            EXPECT_TRUE(std::string(e.what()) == "MESSAGE_ERREUR_EXCEPTION");
        }
        catch (...)
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }

    // teste la capture de l'exception globale
    TEST_F(TestException, Test_Exception_Globale)
    {
        try
        {
            // leve une exception
            throw Exception("MESSAGE_ERREUR_EXCEPTION");
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch (...)
        {
            // teste l'exception levee
            SUCCEED() << "Exception attendue (execption::Exception) non levee.";
        }
    }
}

#include <exception/Exception.hpp>

#include <gtest/gtest.h>

namespace exception
{
    TEST(TestException, Test_General)
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

    TEST(TestException, Test_Exception)
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

    TEST(TestException, Test_Standard)
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

    TEST(TestException, Test_Global)
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

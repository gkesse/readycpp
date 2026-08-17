#include "process/Process.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace process
{
// cree la classe de fixture
class TestProcess : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

// teste le nombre de modules
TEST_F( TestProcess, Test_Nombre_Modules )
{
    // cree le module process
    Process process;

    // teste le nombre de modules
    EXPECT_TRUE( process.m_module_list.size() >= 2 );
}

// teste le module inconnu
TEST_F( TestProcess, Test_Module_Inconnu )
{
    // cree le module inconnu
    Process::Module DEF_MODULE_INCONNU = { Process::MODULE_TYPE::INCONNU, "inconnu", "Le module est inconnu." };

    // cree le module process
    Process process;

    // recupere le module inconnu
    Process::Module module_inconnu = process.m_module_list.at( 0 );

    // teste le module inconnu
    EXPECT_TRUE( module_inconnu == DEF_MODULE_INCONNU );
}

// teste le module d'aide
TEST_F( TestProcess, Test_Module_Aide )
{
    // cree le module d'aide
    Process::Module DEF_MODULE_HELP = { Process::MODULE_TYPE::HELP, "help", "Affiche l'aide." };

    // cree le module process
    Process process;

    // recupere le module d'aide
    Process::Module module_help = process.m_module_list.at( 1 );

    // teste le module inconnu
    EXPECT_TRUE( module_help == DEF_MODULE_HELP );
}

// teste l'affichage du menu d'aide
TEST_F( TestProcess, Test_Affichage_Menu_Aide )
{
    // cree un process
    Process process;

    // affiche l'aide
    process.run();
}

// teste l'egalite entre 2 modules
TEST_F( TestProcess, Test_Egalite_Modules )
{
    // cree une structure de tests parametriques
    struct TestParam
    {
        // cree une structure de resultat
        struct Result
        {
            bool m_est_egal;
        };

        int             m_index;
        Process::Module m_module;
        Result          m_result;
    };

    // cree une liste de structure de tests parametriques
    using TestParamList = std::vector<TestParam>;

    // cree un module d'aide ok (1, 1)
    const Process::Module DEF_MODULE_HELP_OK_1_1 = { Process::MODULE_TYPE::HELP, "MODULE_NAME_1", "MODULE_DESCRIPTION_1" };

    // cree un module de bdd nok (1, 1)
    const Process::Module DEF_MODULE_BDD_NOK_1_1 = { Process::MODULE_TYPE::BDD, "MODULE_NAME_1", "MODULE_DESCRIPTION_1" };

    // cree un module d'aide nok (2, 1)
    const Process::Module DEF_MODULE_HELP_NOK_2_1 = { Process::MODULE_TYPE::HELP, "MODULE_NAME_2", "MODULE_DESCRIPTION_1" };

    // cree un module d'aide nok (1, 2)
    const Process::Module DEF_MODULE_HELP_NOK_1_2 = { Process::MODULE_TYPE::HELP, "MODULE_NAME_1", "MODULE_DESCRIPTION_2" };

    // remplit une liste de structure de tests parametriques
    const TestParamList test_param_list = {
        // {m_index: 0 | m_module: DEF_MODULE_HELP_OK_1_1 | m_result:
        // {m_est_egal:
        // true}}
        { 0, DEF_MODULE_HELP_OK_1_1, { true } },
        // {_index: 1 | m_module: DEF_MODULE_BDD_NOK_1_1 | m_result:
        // {m_est_egal:
        // false}}
        { 1, DEF_MODULE_BDD_NOK_1_1, { false } },
        // {_index: 2 | m_module: DEF_MODULE_HELP_NOK_2_1 | m_result:
        // {m_est_egal:
        // false}}
        { 2, DEF_MODULE_HELP_NOK_2_1, { false } },
        // {_index: 3 | m_module: DEF_MODULE_HELP_NOK_1_2 | m_result:
        // {m_est_egal:
        // false}}
        { 3, DEF_MODULE_HELP_NOK_1_2, { false } },
    };

    // execute un test parametrique
    auto runTest = [&]( const TestParam& _test_param )
    {
        if ( _test_param.m_result.m_est_egal )
        {
            EXPECT_TRUE( DEF_MODULE_HELP_OK_1_1 == _test_param.m_module );
        }
        else
        {
            EXPECT_TRUE( DEF_MODULE_HELP_OK_1_1 != _test_param.m_module );
        }
    };

    // execute les tests parametriques
    for ( const auto& test_param : test_param_list )
    {
        runTest( test_param );
    }
}

// teste le chargement d'un module
TEST_F( TestProcess, Test_Chargement_Module )
{
    // cree une structure de tests parametriques
    struct TestParam
    {
        // cree une structure de resultat
        struct Result
        {
            bool            m_est_ok;
            Process::Module m_module;
        };

        int              m_index;
        Process::ArgList m_arg_list;
        Result           m_result;
    };

    // cree une liste de structure de tests parametriques
    using TestParamList = std::vector<TestParam>;

    // cree des arguments cli vide (ok)
    const Process::ArgList DEF_ARGS_VIDE_OK = { "readycpp", "" };

    // cree des arguments cli inconnu (nok)
    const Process::ArgList DEF_ARGS_INCONNU_NOK = { "readycpp", "unknown" };

    // cree des arguments cli inconnu (ok)
    const Process::ArgList DEF_ARGS_INCONNU_OK = { "readycpp", "inconnu" };

    // cree des arguments cli help (ok)
    const Process::ArgList DEF_ARGS_HELP_OK = { "readycpp", "help" };

    // cree des arguments cli bdd (ok)
    const Process::ArgList DEF_ARGS_BDD_OK = { "readycpp", "bdd" };

    // cree un module inconnu (ok)
    const Process::Module DEF_MODULE_INCONNU_OK = { Process::MODULE_TYPE::INCONNU, "inconnu", "Le module est inconnu." };

    // cree un module inconnu (ok)
    const Process::Module DEF_MODULE_HELP_OK = { Process::MODULE_TYPE::HELP, "help", "Affiche l'aide." };

    // cree un module bdd (ok)
    const Process::Module DEF_MODULE_BDD_OK = { Process::MODULE_TYPE::BDD, "bdd", "Execute le module de gestion de base de donnees." };

    // remplit une liste de structure de tests parametriques
    const TestParamList test_param_list = {
        // {m_index: 0 | m_arg_list: DEF_ARGS_VIDE_OK | m_result: {m_est_ok:
        // false
        // | m_module: DEF_MODULE_HELP_OK}}
        { 0, DEF_ARGS_VIDE_OK, { true, DEF_MODULE_HELP_OK } },
        // {m_index: 1 | m_arg_list: DEF_ARGS_INCONNU_NOK | m_result: {m_est_ok:
        // false | m_module: DEF_MODULE_INCONNU_OK}}
        { 1, DEF_ARGS_INCONNU_NOK, { false, DEF_MODULE_INCONNU_OK } },
        // {_index: 2 | m_arg_list: DEF_ARGS_INCONNU_OK | m_result: {m_est_ok:
        // false | m_module: DEF_MODULE_INCONNU_OK}}
        { 2, DEF_ARGS_INCONNU_OK, { false, DEF_MODULE_INCONNU_OK } },
        // {_index: 3 | m_arg_list: DEF_ARGS_HELP_OK | m_result: {m_est_ok: true
        // |
        // m_module: DEF_MODULE_HELP_OK}}
        { 3, DEF_ARGS_HELP_OK, { true, DEF_MODULE_HELP_OK } },
        // {_index: 4 | m_arg_list: DEF_ARGS_BDD_OK | m_result: {m_est_ok: true
        // |
        // m_module: DEF_MODULE_BDD_OK}}
        { 4, DEF_ARGS_BDD_OK, { true, DEF_MODULE_BDD_OK } },
    };

    // execute un test parametrique
    auto runTest = [&]( const TestParam& _test_param )
    {
        // cree un process
        Process process;

        // charge les arguments cli
        process.m_arg_list = _test_param.m_arg_list;

        // cree un module
        Process::Module module;

        // charge le module
        bool est_ok = process.loadModule( module );

        EXPECT_TRUE( est_ok == _test_param.m_result.m_est_ok );
        EXPECT_TRUE( module == _test_param.m_result.m_module );
    };

    // execute les tests parametriques
    for ( const auto& test_param : test_param_list )
    {
        runTest( test_param );
    }
}

// teste l'execution d'un module
TEST_F( TestProcess, Test_Execution_Module )
{
    // cree une structure de tests parametriques
    struct TestParam
    {
        // cree une structure de resultat
        struct Result
        {
            bool m_est_ok;
        };

        int              m_index;
        Process::ArgList m_arg_list;
        Result           m_result;
    };

    // cree une liste de structure de tests parametriques
    using TestParamList = std::vector<TestParam>;

    // cree des arguments cli inconnu (nok)
    const Process::ArgList DEF_ARGS_INCONNU_NOK = { "readycpp", "unknown" };

    // cree des arguments cli inconnu (ok)
    const Process::ArgList DEF_ARGS_INCONNU_OK = { "readycpp", "inconnu" };

    // cree des arguments cli help (ok)
    const Process::ArgList DEF_ARGS_HELP_OK = { "readycpp", "help" };

    // cree des arguments cli bdd (ok)
    const Process::ArgList DEF_ARGS_BDD_OK = { "readycpp", "bdd" };

    // remplit une liste de structure de tests parametriques
    const TestParamList test_param_list = {
        // {m_index: 0 | m_arg_list: DEF_ARGS_INCONNU_NOK | m_result: {m_est_ok:
        // false}}
        { 0, DEF_ARGS_INCONNU_NOK, { false } },
        // {_index: 1 | m_arg_list: DEF_ARGS_INCONNU_OK | m_result: {m_est_ok:
        // false}}
        { 1, DEF_ARGS_INCONNU_OK, { false } },
        // {_index: 2 | m_arg_list: DEF_ARGS_HELP_OK | m_result: {m_est_ok:
        // true}}
        { 2, DEF_ARGS_HELP_OK, { true } },
        // {_index: 3 | m_arg_list: DEF_ARGS_BDD_OK | m_result: {m_est_ok:
        // true}}
        { 3, DEF_ARGS_BDD_OK, { true } },
    };

    // execute un test parametrique
    auto runTest = [&]( const TestParam& _test_param )
    {
        // cree un process
        Process process;

        // charge les arguments cli
        process.m_arg_list = _test_param.m_arg_list;

        // cree un module
        Process::Module module;

        // charge le module
        bool est_ok = process.loadModule( module );

        EXPECT_TRUE( est_ok == _test_param.m_result.m_est_ok );
    };

    // execute les tests parametriques
    for ( const auto& test_param : test_param_list )
    {
        runTest( test_param );
    }
}
} // namespace process

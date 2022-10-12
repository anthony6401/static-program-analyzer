#include "components/sp/validator/SimpleValidator.h"
#include "components/sp/validator/states/NestedState.h"
#include "components/sp/validator/states/IfState.h"
#include "components/sp/validator/states/ElseState.h"
#include "components/sp/SimpleToken.h"
#include <catch.hpp>
#include <vector>

TEST_CASE("validator program state") {
    SECTION("program state invalid line") {
        SimpleValidator validator = SimpleValidator();
        std::vector<SpTokenType> invalidTokenTypes{ SpTokenType::TELSE, SpTokenType::TREAD,
            SpTokenType::TPRINT, SpTokenType::TCALL, SpTokenType::TWHILE, SpTokenType::TIF, SpTokenType::TASSIGN};
        for (SpTokenType invalidType : invalidTokenTypes) {
            try {
                validator.validateLine(invalidType, 1);
            } catch (std::invalid_argument e){
                REQUIRE(e.what() == std::string("Received invalid SIMPLE code line. Expected Procedure::1"));
            }
        }
    }
    SECTION("program state valid line") {
        SimpleValidator validator = SimpleValidator();
        validator.validateLine(SpTokenType::TPROCEDURE, 1);
        REQUIRE(validator.isValidCode());
    }
}

TEST_CASE("validator nested state") {
    SECTION("Nested state invalid line") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new NestedState(&validator));
        try {
            validator.validateLine(SpTokenType::TPROCEDURE, 1);
        } catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid SIMPLE code line. Unexpected procedure::1"));
        }
        try {
            validator.validateLine(SpTokenType::TELSE, 1);
        } catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid SIMPLE code line. Unexpected else::1"));
        }
    }
    SECTION("Nested state valid line") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new NestedState(&validator));
        std::vector<SpTokenType> validTokenTypes{ SpTokenType::TREAD, SpTokenType::TPRINT, SpTokenType::TCALL,
            SpTokenType::TWHILE, SpTokenType::TIF, SpTokenType::TASSIGN };
        for (SpTokenType validType : validTokenTypes) {
            validator.validateLine(validType, 1);
        }
        REQUIRE(true);
    }

    SECTION("Nested state no stmts check") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new NestedState(&validator));
        try {
            validator.close();
        } catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("No stmts where expected"));
        }
    }
}

TEST_CASE("validator If state") {
    SECTION("If state invalid line") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new IfState(&validator));
        try {
            validator.validateLine(SpTokenType::TPROCEDURE, 1);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid SIMPLE code line. Unexpected procedure::1"));
        }
        try {
            validator.validateLine(SpTokenType::TELSE, 1);
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Received invalid SIMPLE code line. Unexpected else::1"));
        }
    }

    SECTION("If state valid line") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new IfState(&validator));
        std::vector<SpTokenType> validTokenTypes{ SpTokenType::TREAD, SpTokenType::TPRINT, SpTokenType::TCALL,
            SpTokenType::TWHILE, SpTokenType::TIF, SpTokenType::TASSIGN };
        for (SpTokenType validType : validTokenTypes) {
            validator.validateLine(validType, 1);
        }
        REQUIRE(true);
    }

    SECTION("If state no stmts check") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new IfState(&validator));
        try {
            validator.close();
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("No stmts where expected"));
        }

        validator.validateLine(SpTokenType::TASSIGN, 1);
        validator.close();
        validator.validateLine(SpTokenType::TELSE, 1);
        validator.close();
        try {
            validator.close();
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("No stmts where expected"));
        }
    }
}

TEST_CASE("validator Else state") {
    SECTION("Else state invalid line") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new ElseState(&validator));
        std::vector<SpTokenType> invalidTokenTypes{ SpTokenType::TPROCEDURE, SpTokenType::TREAD,
            SpTokenType::TPRINT, SpTokenType::TCALL, SpTokenType::TWHILE, SpTokenType::TIF, SpTokenType::TASSIGN };
        for (SpTokenType invalidType : invalidTokenTypes) {
            try {
                validator.validateLine(invalidType, 1);
            }
            catch (std::invalid_argument e) {
                REQUIRE(e.what() == std::string("Received invalid SIMPLE code line. Expected Else::1"));
            }
        }
    }
    SECTION("Else state isValidCode") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new ElseState(&validator));
        REQUIRE(!validator.isValidCode());
    }

    SECTION("else state no stmts check") {
        SimpleValidator validator = SimpleValidator();
        validator.setState(new ElseState(&validator));
        try {
            validator.close();
        }
        catch (std::invalid_argument e) {
            REQUIRE(e.what() == std::string("Else statement expected"));
        }
    }
}
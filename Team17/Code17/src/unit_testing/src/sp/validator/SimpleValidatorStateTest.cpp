#include "components/sp/validator/SimpleValidator.h"
#include "components/sp/SimpleToken.h"
#include <catch.hpp>
#include <regex>
#include <vector>

TEST_CASE("validator program state") {
    SECTION("program state invalid line") {
        SimpleValidator validator = SimpleValidator();
        std::vector<SpTokenType> invalidTokenTypes{ SpTokenType::TELSE, SpTokenType::TREAD,
            SpTokenType::TPRINT, SpTokenType::TCALL, SpTokenType::TWHILE, SpTokenType::TIF, SpTokenType::TASSIGN, SpTokenType::TVARIABLE,
            SpTokenType::TCONSTANT, SpTokenType::TCLOSE, SpTokenType::TOPR, SpTokenType::TEXPR, SpTokenType::TSTMTLIST};
        for (SpTokenType invalidType : invalidTokenTypes) {
            try {
                validator.validateLine(invalidType, 1);
            } catch (std::invalid_argument e){
                REQUIRE(e.what() == std::string("Received invalid SIMPLE code line. Expected Procedure::1"));
            }
        }
    }
    SECTION("program state invalid line") {
        SimpleValidator validator = SimpleValidator();
        validator.validateLine(SpTokenType::TPROCEDURE, 1);
        REQUIRE(validator.isValidCode());
    }
}

TEST_CASE("validator nested state") {
    SECTION("nested state invalid line") {
        SimpleValidator validator = SimpleValidator();
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
    SECTION("program state invalid line") {
        SimpleValidator validator = SimpleValidator();
        validator.validateLine(SpTokenType::TPROCEDURE, 1);
        REQUIRE(validator.isValidCode());
    }
}
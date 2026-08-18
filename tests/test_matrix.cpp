#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "matrix.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

TEST_CASE("ooray::Matrix - Constructors and Element Access", "[Matrix]") {
    SECTION("Default constructor initializes to Identity Matrix") {
        ooray::Matrix m;
        REQUIRE(m[0, 0] == 1.0f); REQUIRE(m[0, 1] == 0.0f); REQUIRE(m[0, 2] == 0.0f); REQUIRE(m[0, 3] == 0.0f);
        REQUIRE(m[1, 0] == 0.0f); REQUIRE(m[1, 1] == 1.0f); REQUIRE(m[1, 2] == 0.0f); REQUIRE(m[1, 3] == 0.0f);
        REQUIRE(m[2, 0] == 0.0f); REQUIRE(m[2, 1] == 0.0f); REQUIRE(m[2, 2] == 1.0f); REQUIRE(m[2, 3] == 0.0f);
        REQUIRE(m[3, 0] == 0.0f); REQUIRE(m[3, 1] == 0.0f); REQUIRE(m[3, 2] == 0.0f); REQUIRE(m[3, 3] == 1.0f);
    }

    SECTION("C-Struct Conversion Interoperability") {
        ::Matrix rawMat = MatrixIdentity();
        ooray::Matrix wrapped = rawMat;

        REQUIRE(wrapped == ooray::Matrix::Identity());

        ::Matrix extracted = wrapped;
        REQUIRE(extracted.m0 == 1.0f);
        REQUIRE(extracted.m5 == 1.0f);
    }
}

TEST_CASE("ooray::Matrix - Arithmetic and Transformations", "[Matrix]") {
    SECTION("Matrix Addition and Subtraction") {
        ooray::Matrix a = ooray::Matrix::Identity();
        ooray::Matrix b = ooray::Matrix::Identity();

        ooray::Matrix sum = a + b;
        REQUIRE(sum[0, 0] == 2.0f);
        REQUIRE(sum[1, 1] == 2.0f);

        ooray::Matrix diff = sum - a;
        REQUIRE(diff == ooray::Matrix::Identity());
    }

    SECTION("Matrix Multiplication") {
        ooray::Matrix trans = ooray::Matrix::Translate(2.0f, 3.0f, 4.0f);
        ooray::Matrix identity = ooray::Matrix::Identity();

        ooray::Matrix result = trans * identity;
        REQUIRE(result[0, 3] == 2.0f);
        REQUIRE(result[1, 3] == 3.0f);
        REQUIRE(result[2, 3] == 4.0f);
    }

    SECTION("Determinant, Transpose, and Inversion") {
        ooray::Matrix trans = ooray::Matrix::Translate(5.0f, -2.0f, 3.0f);

        REQUIRE_THAT(trans.Determinant(), WithinRel(1.0f, 0.0001f));

        ooray::Matrix inv = trans.Inverted();
        ooray::Matrix identityCheck = trans * inv;

        REQUIRE_THAT((identityCheck[0, 3]), WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT((identityCheck[1, 3]), WithinAbs(0.0f, 0.0001f));
        REQUIRE_THAT((identityCheck[2, 3]), WithinAbs(0.0f, 0.0001f));
    }
}
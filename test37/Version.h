/// @file
/// @brief Contains protocol version definition.

#pragma once

#include "comms/version.h"

/// @brief Version of the protocol specification.
#define TEST37_SPEC_VERSION (0U)

namespace test37
{

/// @brief Version of the protocol specification.
inline constexpr unsigned specVersion()
{
    return TEST37_SPEC_VERSION;
}

} // namespace test37


// Generated compile time check for minimal supported version of the COMMS library
static_assert(COMMS_MAKE_VERSION(2, 0, 0) <= comms::version(),
    "The version of COMMS library is too old");


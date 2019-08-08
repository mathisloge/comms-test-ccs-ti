/// @file
/// @brief Contains definition of all client input messages bundle.

#pragma once

#include <tuple>
#include "test37/message/Msg1.h"
#include "test37/options/DefaultOptions.h"

namespace test37
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = test37::options::DefaultOptions>
using ClientInputMessages =
    std::tuple<
        test37::message::Msg1<TBase, TOpt>
    >;

} // namespace input

} // namespace test37



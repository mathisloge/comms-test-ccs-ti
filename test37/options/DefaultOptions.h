/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace test37
{

namespace options
{

/// @brief Default (empty) options of the protocol.
struct DefaultOptions
{
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for Layers of
        ///     @ref test37::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     test37::frame::FrameLayers::Data layer.
            using Data = comms::option::app::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     test37::frame::FrameLayers::Id layer.
            using Id = comms::option::app::EmptyOption;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace test37



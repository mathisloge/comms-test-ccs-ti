/// @file
/// @brief Contains definition of protocol default options for bare-metal application
///    where usage of dynamic memory allocation is disabled.

#pragma once

#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

namespace test37
{

namespace options
{

/// @brief Default options for bare-metal application where usage of dynamic
///    memory allocation is diabled.
struct BareMetalDefaultOptions
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
            using Data = comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>;
            
            /// @brief Extra options for @ref
            ///     test37::frame::FrameLayers::Id layer.
            using Id = comms::option::app::InPlaceAllocation;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace test37



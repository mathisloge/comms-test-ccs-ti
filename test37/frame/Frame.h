/// @file
/// @brief Contains definition of <b>"Frame"</b> frame class.

#pragma once

#include <cstdint>
#include "comms/field/IntValue.h"
#include "comms/options.h"
#include "comms/protocol/ChecksumLayer.h"
#include "comms/protocol/MsgDataLayer.h"
#include "comms/protocol/MsgIdLayer.h"
#include "comms/protocol/MsgSizeLayer.h"
#include "comms/protocol/SyncPrefixLayer.h"
#include "comms/protocol/checksum/BasicSum.h"
#include "test37/field/FieldBase.h"
#include "test37/field/MsgId.h"
#include "test37/input/AllMessages.h"
#include "test37/options/DefaultOptions.h"

namespace test37
{

namespace frame
{

/// @brief Layers definition of @ref Frame frame class.
/// @tparam TOpt Protocol options.
/// @see @ref Frame
/// @headerfile "test37/frame/Frame.h"
template <typename TOpt = test37::options::DefaultOptions>
struct FrameLayers
{
    /// @brief Definition of layer "Data".
    using Data =
        comms::protocol::MsgDataLayer<
            typename TOpt::frame::FrameLayers::Data
        >;
    
    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            test37::field::MsgId<TOpt>,
            TMessage,
            TAllMessages,
            Data,
            typename TOpt::frame::FrameLayers::Id
        >;
    
    /// @brief Scope for field(s) of @ref Size layer.
    struct SizeMembers
    {
        /// @brief Definition of <b>"Size"</b> field.
        struct Size : public
            comms::field::IntValue<
                test37::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::NumValueSerOffset<4>
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return "Size";
            }
            
        };
        
    };
    
    /// @brief Definition of layer "Size".
    template <typename TMessage, typename TAllMessages>
    using Size =
        comms::protocol::MsgSizeLayer<
            typename SizeMembers::Size,
            Id<TMessage, TAllMessages>
        >;
    
    /// @brief Scope for field(s) of @ref Checksum layer.
    struct ChecksumMembers
    {
        /// @brief Definition of <b>"Checksum"</b> field.
        struct Checksum : public
            comms::field::IntValue<
                test37::field::FieldBase<>,
                std::uint16_t
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return "Checksum";
            }
            
        };
        
    };
    
    /// @brief Definition of layer "Checksum".
    template <typename TMessage, typename TAllMessages>
    using Checksum =
        comms::protocol::ChecksumLayer<
            typename ChecksumMembers::Checksum,
            comms::protocol::checksum::BasicSum<typename ChecksumMembers::Checksum::ValueType>,
            Size<TMessage, TAllMessages>
        >;
    
    /// @brief Scope for field(s) of @ref Sync layer.
    struct SyncMembers
    {
        /// @brief Definition of <b>"Sync"</b> field.
        struct Sync : public
            comms::field::IntValue<
                test37::field::FieldBase<>,
                std::uint16_t,
                comms::option::def::FailOnInvalid<comms::ErrorStatus::ProtocolError>,
                comms::option::def::DefaultNumValue<43981L>,
                comms::option::def::ValidNumValue<43981L>
            >
        {
            /// @brief Name of the field.
            static const char* name()
            {
                return "Sync";
            }
            
        };
        
    };
    
    /// @brief Definition of layer "Sync".
    template <typename TMessage, typename TAllMessages>
    using Sync =
        comms::protocol::SyncPrefixLayer<
            typename SyncMembers::Sync,
            Checksum<TMessage, TAllMessages>
        >;
    
    /// @brief Final protocol stack definition.
    template<typename TMessage, typename TAllMessages>
    using Stack = Sync<TMessage, TAllMessages>;
    
};

/// @brief Definition of <b>"Frame"</b> frame class.
/// @tparam TMessage Common interface class of all the messages
/// @tparam TAllMessages All supported input messages.
/// @tparam TOpt Frame definition options
/// @headerfile "test37/frame/Frame.h"
template <
   typename TMessage,
   typename TAllMessages = test37::input::AllMessages<TMessage>,
   typename TOpt = test37::options::DefaultOptions
>
class Frame : public
    FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    using Base =
        typename FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>;
public:
    /// @brief Allow access to frame definition layers.
    /// @details See definition of @b COMMS_PROTOCOL_LAYERS_ACCESS macro
    ///     from COMMS library for details.
    ///
    ///     The generated functions are:
    ///     @li layer_data() for @ref FrameLayers::Data layer.
    ///     @li layer_id() for @ref FrameLayers::Id layer.
    ///     @li layer_size() for @ref FrameLayers::Size layer.
    ///     @li layer_checksum() for @ref FrameLayers::Checksum layer.
    ///     @li layer_sync() for @ref FrameLayers::Sync layer.
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        id,
        size,
        checksum,
        sync
    );
};

} // namespace frame

} // namespace test37



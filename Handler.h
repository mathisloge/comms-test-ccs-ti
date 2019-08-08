/*
 * Handler.h
 *
 *  Created on: 08.08.2019
 *      Author: logemann_m
 */

#ifndef HANDLER_H_
#define HANDLER_H_
#include "comms/comms.h"
#include <test37/Message.h>
#include <test37/message/Msg1.h>
#include <test37/frame/Frame.h>


class Handler
{
public:
    using Interface =
            test37::Message<
                comms::option::app::IdInfoInterface,
                comms::option::app::ReadIterator<const std::uint8_t*>,
                comms::option::app::WriteIterator<std::uint8_t*>,
                comms::option::app::LengthInfoInterface,
                comms::option::app::Handler<Handler>
            >;

    using Msg1 = test37::message::Msg1<Interface>;
    using Frame = test37::frame::Frame<Interface>;
    void handle(Msg1& msg);

    void handle(Interface& msg);

    bool getMsg1Received() const;

    void reset();
    Handler();
    virtual ~Handler();
private:
    bool m_msg1Received = false;
};


#endif /* HANDLER_H_ */

/*
 * Handler.cpp
 *
 *  Created on: 08.08.2019
 *      Author: logemann_m
 */

#include <Handler.h>


Handler::Handler()
{

}

void Handler::handle(Msg1& msg)
{
    static_cast<void>(msg);
    m_msg1Received = true;
}

void Handler::handle(Interface& msg)
{
    static_cast<void>(msg);
    m_msg1Received = false;
}

bool Handler::getMsg1Received() const
{
    return m_msg1Received;
}

void Handler::reset()
{
    m_msg1Received = false;
}

Handler::~Handler()
{
}


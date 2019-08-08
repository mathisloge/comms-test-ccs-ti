#include <vector>
#include <cstdint>
#include "comms/comms.h"
#include "test37/Message.h"
#include "test37/message/Msg1.h"
#include "test37/frame/Frame.h"
#include "Handler.h"
/**
 * main.cpp
 */
int main()
{
    Handler handler;
    std::vector<std::uint8_t> outBuf;
    Handler::Frame frame;
    Handler::Msg1 msg1;
    outBuf.resize(frame.length(msg1));
    auto* writeIter = &outBuf[0];
    auto es = frame.write(msg1, writeIter, outBuf.size());
    while(es != comms::ErrorStatus::Success) {
        // loop forever
    }


    auto comsumed = comms::processAllWithDispatch(&outBuf[0], outBuf.size(), frame, handler);

    while(comsumed) {
        // loop forever
    }

	return 0;
}

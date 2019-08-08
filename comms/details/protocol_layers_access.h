//
// Copyright 2017 - 2019 (C). Alex Robenko. All rights reserved.
//

// This file is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "comms/details/macro_common.h"
#include "comms/details/reverse_macro_args.h"

#define COMMS_LAYER_TYPE_1 COMMS_EXPAND(::ThisLayer)
#define COMMS_LAYER_TYPE_2 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_1
#define COMMS_LAYER_TYPE_3 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_2
#define COMMS_LAYER_TYPE_4 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_3
#define COMMS_LAYER_TYPE_5 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_4
#define COMMS_LAYER_TYPE_6 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_5
#define COMMS_LAYER_TYPE_7 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_6
#define COMMS_LAYER_TYPE_8 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_7
#define COMMS_LAYER_TYPE_9 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_8
#define COMMS_LAYER_TYPE_10 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_9
#define COMMS_LAYER_TYPE_11 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_10
#define COMMS_LAYER_TYPE_12 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_11
#define COMMS_LAYER_TYPE_13 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_12
#define COMMS_LAYER_TYPE_14 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_13
#define COMMS_LAYER_TYPE_15 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_14
#define COMMS_LAYER_TYPE_16 COMMS_EXPAND(::NextLayer) COMMS_LAYER_TYPE_15

#define COMMS_DO_LAYER_TYPE_INTERNAL_(N, B_) typename B_ COMMS_EXPAND(COMMS_LAYER_TYPE_ ## N)
#define COMMS_DO_LAYER_TYPE_INTERNAL(N, B_) COMMS_EXPAND(COMMS_DO_LAYER_TYPE_INTERNAL_(N, B_))
#define COMMS_DO_LAYER_TYPE(B_, ...) \
    COMMS_EXPAND(COMMS_DO_LAYER_TYPE_INTERNAL(COMMS_NUM_ARGS(__VA_ARGS__), B_))


#define COMMS_LAYER_CALL_1 COMMS_EXPAND(.thisLayer())
#define COMMS_LAYER_CALL_2 COMMS_EXPAND(.nextLayer())
#define COMMS_LAYER_CALL_3 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_2
#define COMMS_LAYER_CALL_4 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_3
#define COMMS_LAYER_CALL_5 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_4
#define COMMS_LAYER_CALL_6 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_5
#define COMMS_LAYER_CALL_7 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_6
#define COMMS_LAYER_CALL_8 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_7
#define COMMS_LAYER_CALL_9 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_8
#define COMMS_LAYER_CALL_10 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_9
#define COMMS_LAYER_CALL_11 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_10
#define COMMS_LAYER_CALL_12 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_11
#define COMMS_LAYER_CALL_13 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_12
#define COMMS_LAYER_CALL_14 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_13
#define COMMS_LAYER_CALL_15 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_14
#define COMMS_LAYER_CALL_16 COMMS_EXPAND(.nextLayer()) COMMS_LAYER_CALL_15

#define COMMS_DO_LAYER_CALL_INTERNAL_(N, B_) COMMS_EXPAND(B_) COMMS_EXPAND(COMMS_LAYER_CALL_ ## N)
#define COMMS_DO_LAYER_CALL_INTERNAL(N, B_) COMMS_EXPAND(COMMS_DO_LAYER_CALL_INTERNAL_(N, B_))
#define COMMS_DO_LAYER_CALL(B_, ...) \
    COMMS_EXPAND(COMMS_DO_LAYER_CALL_INTERNAL(COMMS_NUM_ARGS(__VA_ARGS__), B_))

#ifdef COMMS_MUST_DEFINE_BASE

#define COMMS_ACCESS_LAYER_FUNC(c_, n_) \
    COMMS_DO_LAYER_TYPE_INTERNAL(c_, Base)& COMMS_CONCATENATE(layer_, n_)()
#define COMMS_ACCESS_LAYER_CONST_FUNC(c_, n_) \
    const COMMS_DO_LAYER_TYPE_INTERNAL(c_, Base)& COMMS_CONCATENATE(layer_, n_)() const

#else // #ifdef COMMS_MUST_DEFINE_BASE
#define COMMS_ACCESS_LAYER_FUNC(c_, n_) FUNC_AUTO_REF_RETURN(COMMS_CONCATENATE(layer_, n_), decltype(COMMS_DO_LAYER_CALL_INTERNAL(c_, COMMS_EXPAND(comms::protocol::toProtocolLayerBase(*this)))))
#define COMMS_ACCESS_LAYER_CONST_FUNC(c_, n_) FUNC_AUTO_REF_RETURN_CONST(COMMS_CONCATENATE(layer_, n_), decltype(COMMS_DO_LAYER_CALL_INTERNAL(c_, COMMS_EXPAND(comms::protocol::toProtocolLayerBase(*this)))))
#endif // #ifdef COMMS_MUST_DEFINE_BASE

#define COMMS_ACCESS_LAYER_ACC_FUNC(c_, n_) \
    COMMS_ACCESS_LAYER_FUNC(c_, n_) {\
        return COMMS_DO_LAYER_CALL_INTERNAL(c_, comms::protocol::toProtocolLayerBase(*this)); \
    } \
    COMMS_ACCESS_LAYER_CONST_FUNC(c_, n_) {\
        return COMMS_DO_LAYER_CALL_INTERNAL(c_, comms::protocol::toProtocolLayerBase(*this)); \
    }

#define COMMS_ACCESS_LAYER_ACC_FUNC_1(n_) COMMS_ACCESS_LAYER_ACC_FUNC(1, n_)
#define COMMS_ACCESS_LAYER_ACC_FUNC_2(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(2, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_1(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_3(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(3, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_2(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_4(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(4, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_3(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_5(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(5, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_4(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_6(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(6, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_5(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_7(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(7, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_6(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_8(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(8, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_7(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_9(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(9, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_8(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_10(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(10, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_9(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_11(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(11, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_10(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_12(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(12, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_11(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_13(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(13, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_12(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_14(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(14, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_13(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_15(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(15, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_14(__VA_ARGS__))
#define COMMS_ACCESS_LAYER_ACC_FUNC_16(n_, ...) \
    COMMS_ACCESS_LAYER_ACC_FUNC(16, n_) \
    COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_15(c_, __VA_ARGS__))


#define COMMS_CHOOSE_ACCESS_LAYER_ACC_FUNC_(N, ...) COMMS_EXPAND(COMMS_ACCESS_LAYER_ACC_FUNC_ ## N(__VA_ARGS__))
#define  COMMS_CHOOSE_ACCESS_LAYER_ACC_FUNC(N, ...) COMMS_EXPAND(COMMS_CHOOSE_ACCESS_LAYER_ACC_FUNC_(N, __VA_ARGS__))
#define COMMS_DO_ACCESS_LAYER_ACC_FUNC(...) \
    COMMS_EXPAND(COMMS_CHOOSE_ACCESS_LAYER_ACC_FUNC(COMMS_NUM_ARGS(__VA_ARGS__), __VA_ARGS__))












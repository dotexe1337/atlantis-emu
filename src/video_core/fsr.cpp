// SPDX-FileCopyrightText: Copyright 2023 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <cmath>
#include "video_core/fsr.h"

namespace FSR {
namespace {
// Reimplementations of the constant generating functions in ffx_fsr1.h
// GCC generated a lot of warnings when using the official header.
u32 AU1_AH1_AF1(f32 f) {
    static constexpr u32 base[512]{
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040,
        0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x0c00, 0x1000, 0x1400, 0x1800, 0x1c00, 0x2000,
        0x2400, 0x2800, 0x2c00, 0x3000, 0x3400, 0x3800, 0x3c00, 0x4000, 0x4400, 0x4800, 0x4c00,
        0x5000, 0x5400, 0x5800, 0x5c00, 0x6000, 0x6400, 0x6800, 0x6c00, 0x7000, 0x7400, 0x7800,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff, 0x7bff,
        0x7bff, 0x7bff, 0x7bff, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
        0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8001, 0x8002, 0x8004, 0x8008,
        0x8010, 0x8020, 0x8040, 0x8080, 0x8100, 0x8200, 0x8400, 0x8800, 0x8c00, 0x9000, 0x9400,
        0x9800, 0x9c00, 0xa000, 0xa400, 0xa800, 0xac00, 0xb000, 0xb400, 0xb800, 0xbc00, 0xc000,
        0xc400, 0xc800, 0xcc00, 0xd000, 0xd400, 0xd800, 0xdc00, 0xe000, 0xe400, 0xe800, 0xec00,
        0xf000, 0xf400, 0xf800, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
        0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff, 0xfbff,
    };
    static constexpr s8 shift[512]{
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x17, 0x16,
        0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
        0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
        0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x17,
        0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
        0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d,
        0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
        0x18, 0x18,
    };
    const u32 u = Common::BitCast<u32>(f);
    const u32 i = u >> 23;
    return base[i] + ((u & 0x7fffff) >> shift[i]);
}

u32 AU1_AH2_AF2(f32 a[2]) {
    return AU1_AH1_AF1(a[0]) + (AU1_AH1_AF1(a[1]) << 16);
}

void FsrEasuCon(u32 con0[4], u32 con1[4], u32 con2[4], u32 con3[4], f32 inputViewportInPixelsX,
                f32 inputViewportInPixelsY, f32 inputSizeInPixelsX, f32 inputSizeInPixelsY,
                f32 outputSizeInPixelsX, f32 outputSizeInPixelsY) {
    con0[0] = Common::BitCast<u32>(inputViewportInPixelsX / outputSizeInPixelsX);
    con0[1] = Common::BitCast<u32>(inputViewportInPixelsY / outputSizeInPixelsY);
    con0[2] = Common::BitCast<u32>(0.5f * inputViewportInPixelsX / outputSizeInPixelsX - 0.5f);
    con0[3] = Common::BitCast<u32>(0.5f * inputViewportInPixelsY / outputSizeInPixelsY - 0.5f);
    con1[0] = Common::BitCast<u32>(1.0f / inputSizeInPixelsX);
    con1[1] = Common::BitCast<u32>(1.0f / inputSizeInPixelsY);
    con1[2] = Common::BitCast<u32>(1.0f / inputSizeInPixelsX);
    con1[3] = Common::BitCast<u32>(-1.0f / inputSizeInPixelsY);
    con2[0] = Common::BitCast<u32>(-1.0f / inputSizeInPixelsX);
    con2[1] = Common::BitCast<u32>(2.0f / inputSizeInPixelsY);
    con2[2] = Common::BitCast<u32>(1.0f / inputSizeInPixelsX);
    con2[3] = Common::BitCast<u32>(2.0f / inputSizeInPixelsY);
    con3[0] = Common::BitCast<u32>(0.0f / inputSizeInPixelsX);
    con3[1] = Common::BitCast<u32>(4.0f / inputSizeInPixelsY);
    con3[2] = con3[3] = 0;
}
} // Anonymous namespace

void FsrEasuConOffset(u32 con0[4], u32 con1[4], u32 con2[4], u32 con3[4],
                      f32 inputViewportInPixelsX, f32 inputViewportInPixelsY,
                      f32 inputSizeInPixelsX, f32 inputSizeInPixelsY, f32 outputSizeInPixelsX,
                      f32 outputSizeInPixelsY, f32 inputOffsetInPixelsX, f32 inputOffsetInPixelsY) {
    FsrEasuCon(con0, con1, con2, con3, inputViewportInPixelsX, inputViewportInPixelsY,
               inputSizeInPixelsX, inputSizeInPixelsY, outputSizeInPixelsX, outputSizeInPixelsY);
    con0[2] = Common::BitCast<u32>(0.5f * inputViewportInPixelsX / outputSizeInPixelsX - 0.5f +
                                   inputOffsetInPixelsX);
    con0[3] = Common::BitCast<u32>(0.5f * inputViewportInPixelsY / outputSizeInPixelsY - 0.5f +
                                   inputOffsetInPixelsY);
}

void FsrRcasCon(u32* con, f32 sharpness) {
    sharpness = std::exp2f(-sharpness);
    f32 hSharp[2]{sharpness, sharpness};
    con[0] = Common::BitCast<u32>(sharpness);
    con[1] = AU1_AH2_AF2(hSharp);
    con[2] = 0;
    con[3] = 0;
}
} // namespace FSR

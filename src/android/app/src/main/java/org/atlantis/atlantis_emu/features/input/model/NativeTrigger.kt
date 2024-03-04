// SPDX-FileCopyrightText: 2024 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

package org.atlantis.atlantis_emu.features.input.model

// Must match enum in src/common/settings_input.h
enum class NativeTrigger(val int: Int) {
    LTrigger(0),
    RTrigger(1)
}

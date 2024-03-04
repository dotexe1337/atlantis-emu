// SPDX-FileCopyrightText: 2023 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

package org.atlantis.atlantis_emu.features.settings.model

interface AbstractShortSetting : AbstractSetting {
    fun getShort(needsGlobal: Boolean = false): Short
    fun setShort(value: Short)
}

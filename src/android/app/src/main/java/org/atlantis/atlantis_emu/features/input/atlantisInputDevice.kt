// SPDX-FileCopyrightText: 2024 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

package org.atlantis.atlantis_emu.features.input

import android.view.InputDevice
import androidx.annotation.Keep
import org.atlantis.atlantis_emu.atlantisApplication
import org.atlantis.atlantis_emu.R
import org.atlantis.atlantis_emu.utils.InputHandler.getGUID

@Keep
interface atlantisInputDevice {
    fun getName(): String

    fun getGUID(): String

    fun getPort(): Int

    fun getSupportsVibration(): Boolean

    fun vibrate(intensity: Float)

    fun getAxes(): Array<Int> = arrayOf()
    fun hasKeys(keys: IntArray): BooleanArray = BooleanArray(0)
}

class atlantisPhysicalDevice(
    private val device: InputDevice,
    private val port: Int,
    useSystemVibrator: Boolean
) : atlantisInputDevice {
    private val vibrator = if (useSystemVibrator) {
        atlantisVibrator.getSystemVibrator()
    } else {
        atlantisVibrator.getControllerVibrator(device)
    }

    override fun getName(): String {
        return device.name
    }

    override fun getGUID(): String {
        return device.getGUID()
    }

    override fun getPort(): Int {
        return port
    }

    override fun getSupportsVibration(): Boolean {
        return vibrator.supportsVibration()
    }

    override fun vibrate(intensity: Float) {
        vibrator.vibrate(intensity)
    }

    override fun getAxes(): Array<Int> = device.motionRanges.map { it.axis }.toTypedArray()
    override fun hasKeys(keys: IntArray): BooleanArray = device.hasKeys(*keys)
}

class atlantisInputOverlayDevice(
    private val vibration: Boolean,
    private val port: Int
) : atlantisInputDevice {
    private val vibrator = atlantisVibrator.getSystemVibrator()

    override fun getName(): String {
        return atlantisApplication.appContext.getString(R.string.input_overlay)
    }

    override fun getGUID(): String {
        return "00000000000000000000000000000000"
    }

    override fun getPort(): Int {
        return port
    }

    override fun getSupportsVibration(): Boolean {
        if (vibration) {
            return vibrator.supportsVibration()
        }
        return false
    }

    override fun vibrate(intensity: Float) {
        if (vibration) {
            vibrator.vibrate(intensity)
        }
    }
}

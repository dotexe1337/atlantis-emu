// SPDX-FileCopyrightText: 2023 atlantis Emulator Project
// SPDX-License-Identifier: GPL-3.0-or-later

package org.atlantis.atlantis_emu.utils

import android.view.InputDevice
import android.view.KeyEvent
import android.view.MotionEvent
import org.atlantis.atlantis_emu.features.input.NativeInput
import org.atlantis.atlantis_emu.features.input.atlantisInputOverlayDevice
import org.atlantis.atlantis_emu.features.input.atlantisPhysicalDevice

object InputHandler {
    var androidControllers = mapOf<Int, atlantisPhysicalDevice>()
    var registeredControllers = mutableListOf<ParamPackage>()

    fun dispatchKeyEvent(event: KeyEvent): Boolean {
        val action = when (event.action) {
            KeyEvent.ACTION_DOWN -> NativeInput.ButtonState.PRESSED
            KeyEvent.ACTION_UP -> NativeInput.ButtonState.RELEASED
            else -> return false
        }

        var controllerData = androidControllers[event.device.controllerNumber]
        if (controllerData == null) {
            updateControllerData()
            controllerData = androidControllers[event.device.controllerNumber] ?: return false
        }

        NativeInput.onGamePadButtonEvent(
            controllerData.getGUID(),
            controllerData.getPort(),
            event.keyCode,
            action
        )
        return true
    }

    fun dispatchGenericMotionEvent(event: MotionEvent): Boolean {
        val controllerData =
            androidControllers[event.device.controllerNumber] ?: return false
        event.device.motionRanges.forEach {
            NativeInput.onGamePadAxisEvent(
                controllerData.getGUID(),
                controllerData.getPort(),
                it.axis,
                event.getAxisValue(it.axis)
            )
        }
        return true
    }

    fun getDevices(): Map<Int, atlantisPhysicalDevice> {
        val gameControllerDeviceIds = mutableMapOf<Int, atlantisPhysicalDevice>()
        val deviceIds = InputDevice.getDeviceIds()
        var port = 0
        val inputSettings = NativeConfig.getInputSettings(true)
        deviceIds.forEach { deviceId ->
            InputDevice.getDevice(deviceId)?.apply {
                // Verify that the device has gamepad buttons, control sticks, or both.
                if (sources and InputDevice.SOURCE_GAMEPAD == InputDevice.SOURCE_GAMEPAD ||
                    sources and InputDevice.SOURCE_JOYSTICK == InputDevice.SOURCE_JOYSTICK
                ) {
                    if (!gameControllerDeviceIds.contains(controllerNumber)) {
                        gameControllerDeviceIds[controllerNumber] = atlantisPhysicalDevice(
                            this,
                            port,
                            inputSettings[port].useSystemVibrator
                        )
                    }
                    port++
                }
            }
        }
        return gameControllerDeviceIds
    }

    fun updateControllerData() {
        androidControllers = getDevices()
        androidControllers.forEach {
            NativeInput.registerController(it.value)
        }

        // Register the input overlay on a dedicated port for all player 1 vibrations
        NativeInput.registerController(atlantisInputOverlayDevice(androidControllers.isEmpty(), 100))
        registeredControllers.clear()
        NativeInput.getInputDevices().forEach {
            registeredControllers.add(ParamPackage(it))
        }
        registeredControllers.sortBy { it.get("port", 0) }
    }

    fun InputDevice.getGUID(): String = String.format("%016x%016x", productId, vendorId)
}

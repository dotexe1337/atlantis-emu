// SPDX-FileCopyrightText: 2024 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

package org.atlantis.atlantis_emu.features.input

import android.content.Context
import android.os.Build
import android.os.CombinedVibration
import android.os.VibrationEffect
import android.os.Vibrator
import android.os.VibratorManager
import android.view.InputDevice
import androidx.annotation.Keep
import androidx.annotation.RequiresApi
import org.atlantis.atlantis_emu.atlantisApplication

@Keep
@Suppress("DEPRECATION")
interface atlantisVibrator {
    fun supportsVibration(): Boolean

    fun vibrate(intensity: Float)

    companion object {
        fun getControllerVibrator(device: InputDevice): atlantisVibrator =
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
                atlantisVibratorManager(device.vibratorManager)
            } else {
                atlantisVibratorManagerCompat(device.vibrator)
            }

        fun getSystemVibrator(): atlantisVibrator =
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
                val vibratorManager = atlantisApplication.appContext
                    .getSystemService(Context.VIBRATOR_MANAGER_SERVICE) as VibratorManager
                atlantisVibratorManager(vibratorManager)
            } else {
                val vibrator = atlantisApplication.appContext
                    .getSystemService(Context.VIBRATOR_SERVICE) as Vibrator
                atlantisVibratorManagerCompat(vibrator)
            }

        fun getVibrationEffect(intensity: Float): VibrationEffect? {
            if (intensity > 0f) {
                return VibrationEffect.createOneShot(
                    50,
                    (255.0 * intensity).toInt().coerceIn(1, 255)
                )
            }
            return null
        }
    }
}

@RequiresApi(Build.VERSION_CODES.S)
class atlantisVibratorManager(private val vibratorManager: VibratorManager) : atlantisVibrator {
    override fun supportsVibration(): Boolean {
        return vibratorManager.vibratorIds.isNotEmpty()
    }

    override fun vibrate(intensity: Float) {
        val vibration = atlantisVibrator.getVibrationEffect(intensity) ?: return
        vibratorManager.vibrate(CombinedVibration.createParallel(vibration))
    }
}

class atlantisVibratorManagerCompat(private val vibrator: Vibrator) : atlantisVibrator {
    override fun supportsVibration(): Boolean {
        return vibrator.hasVibrator()
    }

    override fun vibrate(intensity: Float) {
        val vibration = atlantisVibrator.getVibrationEffect(intensity) ?: return
        vibrator.vibrate(vibration)
    }
}

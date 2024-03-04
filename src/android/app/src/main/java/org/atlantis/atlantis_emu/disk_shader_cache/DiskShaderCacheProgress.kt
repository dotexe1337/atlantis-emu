// SPDX-FileCopyrightText: 2023 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

package org.atlantis.atlantis_emu.disk_shader_cache

import androidx.annotation.Keep
import androidx.lifecycle.ViewModelProvider
import org.atlantis.atlantis_emu.NativeLibrary
import org.atlantis.atlantis_emu.R
import org.atlantis.atlantis_emu.activities.EmulationActivity
import org.atlantis.atlantis_emu.model.EmulationViewModel
import org.atlantis.atlantis_emu.utils.Log

@Keep
object DiskShaderCacheProgress {
    private lateinit var emulationViewModel: EmulationViewModel

    private fun prepareViewModel() {
        emulationViewModel =
            ViewModelProvider(
                NativeLibrary.sEmulationActivity.get() as EmulationActivity
            )[EmulationViewModel::class.java]
    }

    @JvmStatic
    fun loadProgress(stage: Int, progress: Int, max: Int) {
        val emulationActivity = NativeLibrary.sEmulationActivity.get()
        if (emulationActivity == null) {
            Log.error("[DiskShaderCacheProgress] EmulationActivity not present")
            return
        }

        emulationActivity.runOnUiThread {
            when (LoadCallbackStage.values()[stage]) {
                LoadCallbackStage.Prepare -> prepareViewModel()
                LoadCallbackStage.Build -> emulationViewModel.updateProgress(
                    emulationActivity.getString(R.string.building_shaders),
                    progress,
                    max
                )

                LoadCallbackStage.Complete -> {}
            }
        }
    }

    // Equivalent to VideoCore::LoadCallbackStage
    enum class LoadCallbackStage {
        Prepare, Build, Complete
    }
}

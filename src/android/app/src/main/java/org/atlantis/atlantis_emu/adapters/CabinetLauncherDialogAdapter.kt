// SPDX-FileCopyrightText: 2023 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

package org.atlantis.atlantis_emu.adapters

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.core.content.res.ResourcesCompat
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import org.atlantis.atlantis_emu.HomeNavigationDirections
import org.atlantis.atlantis_emu.NativeLibrary
import org.atlantis.atlantis_emu.R
import org.atlantis.atlantis_emu.atlantisApplication
import org.atlantis.atlantis_emu.databinding.DialogListItemBinding
import org.atlantis.atlantis_emu.model.CabinetMode
import org.atlantis.atlantis_emu.adapters.CabinetLauncherDialogAdapter.CabinetModeViewHolder
import org.atlantis.atlantis_emu.model.AppletInfo
import org.atlantis.atlantis_emu.model.Game
import org.atlantis.atlantis_emu.viewholder.AbstractViewHolder

class CabinetLauncherDialogAdapter(val fragment: Fragment) :
    AbstractListAdapter<CabinetMode, CabinetModeViewHolder>(
        CabinetMode.values().copyOfRange(1, CabinetMode.entries.size).toList()
    ) {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CabinetModeViewHolder {
        DialogListItemBinding.inflate(LayoutInflater.from(parent.context), parent, false)
            .also { return CabinetModeViewHolder(it) }
    }

    inner class CabinetModeViewHolder(val binding: DialogListItemBinding) :
        AbstractViewHolder<CabinetMode>(binding) {
        override fun bind(model: CabinetMode) {
            binding.icon.setImageDrawable(
                ResourcesCompat.getDrawable(
                    binding.icon.context.resources,
                    model.iconId,
                    binding.icon.context.theme
                )
            )
            binding.title.setText(model.titleId)

            binding.root.setOnClickListener { onClick(model) }
        }

        private fun onClick(mode: CabinetMode) {
            val appletPath = NativeLibrary.getAppletLaunchPath(AppletInfo.Cabinet.entryId)
            NativeLibrary.setCurrentAppletId(AppletInfo.Cabinet.appletId)
            NativeLibrary.setCabinetMode(mode.id)
            val appletGame = Game(
                title = atlantisApplication.appContext.getString(R.string.cabinet_applet),
                path = appletPath
            )
            val action = HomeNavigationDirections.actionGlobalEmulationActivity(appletGame)
            fragment.findNavController().navigate(action)
        }
    }
}

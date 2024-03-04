// SPDX-FileCopyrightText: 2023 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

package org.atlantis.atlantis_emu.fragments

import android.app.Dialog
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.DialogFragment
import androidx.recyclerview.widget.LinearLayoutManager
import com.google.android.material.dialog.MaterialAlertDialogBuilder
import org.atlantis.atlantis_emu.R
import org.atlantis.atlantis_emu.adapters.CabinetLauncherDialogAdapter
import org.atlantis.atlantis_emu.databinding.DialogListBinding

class CabinetLauncherDialogFragment : DialogFragment() {
    private lateinit var binding: DialogListBinding

    override fun onCreateDialog(savedInstanceState: Bundle?): Dialog {
        binding = DialogListBinding.inflate(layoutInflater)
        binding.dialogList.apply {
            layoutManager = LinearLayoutManager(requireContext())
            adapter = CabinetLauncherDialogAdapter(this@CabinetLauncherDialogFragment)
        }

        return MaterialAlertDialogBuilder(requireContext())
            .setTitle(R.string.cabinet_launcher)
            .setView(binding.root)
            .create()
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return binding.root
    }
}
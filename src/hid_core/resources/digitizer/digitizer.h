// SPDX-FileCopyrightText: Copyright 2018 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "hid_core/resources/controller_base.h"

namespace Service::HID {

class Digitizer final : public ControllerBase {
public:
    explicit Digitizer(Core::HID::HIDCore& hid_core_);
    ~Digitizer() override;

    // Called when the controller is initialized
    void OnInit() override;

    // When the controller is released
    void OnRelease() override;

    // When the controller is requesting an update for the shared memory
    void OnUpdate(const Core::Timing::CoreTiming& core_timing) override;
};
} // namespace Service::HID
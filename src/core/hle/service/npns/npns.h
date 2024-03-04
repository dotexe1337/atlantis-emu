// SPDX-FileCopyrightText: Copyright 2018 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

namespace Core {
class System;
}

namespace Service::NPNS {

void LoopProcess(Core::System& system);

} // namespace Service::NPNS

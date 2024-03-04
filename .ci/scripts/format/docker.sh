#!/bin/bash -ex

# SPDX-FileCopyrightText: 2019 atlantis Emulator Project
# SPDX-License-Identifier: GPL-2.0-or-later

# Run clang-format
cd /atlantis
chmod a+x ./.ci/scripts/format/script.sh
./.ci/scripts/format/script.sh

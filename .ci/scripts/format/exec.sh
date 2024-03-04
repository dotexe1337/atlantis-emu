#!/bin/bash -ex

# SPDX-FileCopyrightText: 2019 atlantis Emulator Project
# SPDX-License-Identifier: GPL-2.0-or-later

chmod a+x ./.ci/scripts/format/docker.sh
# the UID for the container atlantis user is 1027
sudo chown -R 1027 ./
docker run -v "$(pwd):/atlantis" -w /atlantis atlantisemu/build-environments:linux-clang-format /bin/bash -ex /atlantis/.ci/scripts/format/docker.sh
sudo chown -R $UID ./

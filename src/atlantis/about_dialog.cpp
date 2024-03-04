// SPDX-FileCopyrightText: Copyright 2018 atlantis Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QIcon>
#include <fmt/format.h>
#include "common/scm_rev.h"
#include "ui_aboutdialog.h"
#include "atlantis/about_dialog.h"

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent), ui{std::make_unique<Ui::AboutDialog>()} {
    const auto branch_name = std::string(Common::g_scm_branch);
    const auto description = std::string(Common::g_scm_desc);
    const auto build_id = std::string(Common::g_build_id);

    const auto atlantis_build = fmt::format("atlantis Development Build | {}-{}", branch_name, description);
    const auto override_build =
        fmt::format(fmt::runtime(std::string(Common::g_title_bar_format_idle)), build_id);
    const auto atlantis_build_version = override_build.empty() ? atlantis_build : override_build;

    ui->setupUi(this);
    // Try and request the icon from Qt theme (Linux?)
    const QIcon atlantis_logo = QIcon::fromTheme(QStringLiteral("org.atlantis_emu.atlantis"));
    if (!atlantis_logo.isNull()) {
        ui->labelLogo->setPixmap(atlantis_logo.pixmap(200));
    }
    ui->labelBuildInfo->setText(
        ui->labelBuildInfo->text().arg(QString::fromStdString(atlantis_build_version),
                                       QString::fromUtf8(Common::g_build_date).left(10)));
}

AboutDialog::~AboutDialog() = default;

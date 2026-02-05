/*
 *     Axologl - A simple logging library designed to integrate with libnx
 *     Copyright (C) 2026. Xerat0nin
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <switch.h>

#include "axologl.h"

void testOutput(const std::string& text)
{
    axologl::debug(text + ": Testing debug output");
    axologl::info(text + ": Testing info output");
    axologl::notice(text + ": Testing notice output");
    axologl::warn(text + ": Testing warning output");
    axologl::error(text + ": Testing error output");
    axologl::fatal(text + ": Testing fatal output");
}

void testLogLevelChange(const axologl::LogLevel level)
{
    axologl::setLogLevel(level);
    testOutput("Log Level: " + std::to_string(level));
    axologl::log("----------------------------------\n");
}

int main(int argc, char** argv)
{
    consoleInit(nullptr);

    const axologl::AxologlOptions options = {
        axologl::Debug,
        {
            true,
            false,
            true
        },
        true,
        "axologl/test.log"
    };

    axologl::configure(options);
    axologl::printConfiguration();

    axologl::log("Starting the Axologl test suite...\n");
    axologl::log("----------------------------------\n");

    // Test configuration output
    testOutput("Configuration");
    axologl::log("----------------------------------\n");

    axologl::disableAnsi();
    testOutput("ANSI Disabled");
    axologl::log("----------------------------------\n");

    axologl::enableAnsi();

    testLogLevelChange(axologl::Info);
    testLogLevelChange(axologl::Notice);
    testLogLevelChange(axologl::Warning);
    testLogLevelChange(axologl::Error);
    testLogLevelChange(axologl::Fatal);

    axologl::setLogLevel(axologl::Debug);

    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    while (appletMainLoop())
    {
        padUpdate(&pad);
        if (padGetButtonsDown(&pad) & HidNpadButton_Plus) break;
        consoleUpdate(nullptr);
    }

    axologl::teardown();
    consoleExit(nullptr);

    return 0;
}

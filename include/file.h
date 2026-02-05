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

#ifndef AXOLOGL_FILE_H
#define AXOLOGL_FILE_H
#include <filesystem>

namespace fs = std::filesystem;

namespace axologl
{
    class FileLogger
    {
        fs::path _logPath;
        FILE* logFile = nullptr;

        [[nodiscard]] bool ensurePath() const
        {
            if (!fs::create_directories(getParentPath()))
            {
                // Check the directory doesn't already exist
                return fs::exists(getParentPath());
            }

            return true;
        }

        void write(const std::string& text) const
        {
            fputs((text + "\n").c_str(), logFile);
        }

        [[nodiscard]] fs::path getLogFilename() const
        {
            return _logPath.filename();
        }

        [[nodiscard]] fs::path getParentPath() const
        {
            return _logPath.parent_path();
        }

        [[nodiscard]] bool getLogFileExists() const
        {
            return fs::exists(_logPath);
        }

    public:
        explicit FileLogger(const fs::path& logPath)
        {
            _logPath = logPath;
            // Check our write path exists, create it if not
            if (ensurePath())
            {
                // Check if we were provided a filename
                if (getLogFilename() != "")
                {
                    // Check if we need to rotate files
                    if (getLogFileExists())
                    {
                        // Rotate out file here
                    }
                }
                else
                {
                    // Use a default filename
                    _logPath.append("/axologl.log");
                }

                logFile = fopen(_logPath.c_str(), "a+");
            }
        }

        ~FileLogger()
        {
            fclose(logFile);
        }

        [[nodiscard]] bool ready() const
        {
            return logFile != nullptr;
        }

        void log(const std::string& text) const
        {
            // Write to file
            write(text);
        }
    };
}

#endif //AXOLOGL_FILE_H

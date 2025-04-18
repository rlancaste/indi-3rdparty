/*
    ZWO CAA Rotator
    Copyright (C) 2025 Jasem Mutlaq (mutlaqja@ikarustech.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <indirotator.h>
#include <indipropertyswitch.h>
#include <indipropertynumber.h>
#include <indipropertytext.h>
#include <inditimer.h>
#include <string>

class ASICAA : public INDI::Rotator
{
    public:
        ASICAA(int ID, const std::string &rotatorName);
        virtual ~ASICAA() = default;

        virtual bool initProperties() override;
        virtual bool updateProperties() override;

        virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
        virtual bool ISNewSwitch(const char *dev, const char *name, ISState states[], char *names[], int n) override;

    protected:
        // Connection
        virtual bool Connect() override;
        virtual bool Disconnect() override;

        // Rotator Overrides
        virtual IPState MoveRotator(double angle) override;
        virtual bool AbortRotator() override;
        virtual bool SyncRotator(double angle) override;
        virtual bool ReverseRotator(bool enabled) override;

        // Misc.
        virtual const char *getDefaultName() override;
        virtual void TimerHit() override;

    private:
        int m_ID { -1 };
        bool m_IsMoving { false };
        bool m_IsHandControl { false };

        // Temperature
        INDI::PropertyNumber TemperatureNP {1};

        // Beep
        INDI::PropertySwitch BeepSP {2};

        // Version Info Indices
        enum
        {
            VERSION_FIRMWARE,
            VERSION_SDK,
            VERSION_SERIAL,
            VERSION_COUNT
        };
        INDI::PropertyText VersionInfoTP {VERSION_COUNT};

        // Timer
        static constexpr double THRESHOLD { 0.1 };
};

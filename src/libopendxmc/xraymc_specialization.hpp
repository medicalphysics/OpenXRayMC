/*This file is part of Openxraymc.

Openxraymc is free software : you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Openxraymc is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Openxraymc. If not, see < https://www.gnu.org/licenses/>.

Copyright 2023 Erlend Andersen
*/

#pragma once

#include "xraymc/beams/beamtype.hpp"
#include "xraymc/beams/cbctbeam.hpp"
#include "xraymc/beams/ctsequentialbeam.hpp"
#include "xraymc/beams/ctspiralbeam.hpp"
#include "xraymc/beams/ctspiraldualenergybeam.hpp"
#include "xraymc/beams/dxbeam.hpp"
#include "xraymc/beams/pencilbeam.hpp"
#include "xraymc/beams/tube/tube.hpp"
#include "xraymc/material/material.hpp"
#include "xraymc/material/nistmaterials.hpp"

#include <memory>
#include <variant>

// Here we specialize types from the xraymc template library.

using Material = xraymc::Material<5>;
using Tube = xraymc::Tube;
using NISTMaterials = xraymc::NISTMaterials;

using CTSequentialBeam = xraymc::CTSequentialBeam<false>;
using CTSpiralBeam = xraymc::CTSpiralBeam<false>;
using CTSpiralDualEnergyBeam = xraymc::CTSpiralDualEnergyBeam<false>;
using CBCTBeam = xraymc::CBCTBeam<false>;
using CTAECFilter = xraymc::CTAECFilter;
using BowtieFilter = xraymc::BowtieFilter;
using PencilBeam = xraymc::PencilBeam<false>;

class DXBeam : public xraymc::DXBeam<false> {
public:
    DXBeam(const std::map<std::size_t, double>& filtrationMaterials = {});

    const std::array<double, 3>& rotationCenter() const;
    void setRotationCenter(const std::array<double, 3>& c);
    double sourcePatientDistance() const;
    void setSourcePatientDistance(double d);
    double sourceDetectorDistance() const;
    void setSourceDetectorDistance(double d);
    void setCollimation(const std::array<double, 2>& coll);
    std::array<double, 2> collimation() const;

    double primaryAngleDeg() const;
    void setPrimaryAngleDeg(double ang);
    double secondaryAngleDeg() const;
    void setSecondaryAngleDeg(double ang);

protected:
    void updatePosition();

private:
    std::array<double, 3> m_rotation_center = { 0, 0, 0 };
    double m_SPD = 100;
    double m_SDD = 100;
    std::array<double, 2> m_rotAngles = { 0, 0 };
};

using Beam = std::variant<DXBeam, CTSpiralBeam, CTSpiralDualEnergyBeam, CBCTBeam, CTSequentialBeam, PencilBeam>;

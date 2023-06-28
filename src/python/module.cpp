#include <python/nanobind.hpp>
#include "operations/OpType.hpp"
#include <nanobind/stl/string.h>

namespace mqt {

NB_MODULE(_core, m) {
  m.def(
      "add", [](int a, int b) { return a + b; }, "a"_a, "b"_a);
  nb::enum_<qc::OpType>(m, "OpType")
        .value("none",qc::OpType::None)
        .value("gphase",qc::OpType::GPhase)
        .value("i",qc::OpType::I)
        .value("h",qc::OpType::H)
        .value("x",qc::OpType::X)
        .value("y",qc::OpType::Y)
        .value("z",qc::OpType::Z)
        .value("s",qc::OpType::S)
        .value("sdag",qc::OpType::Sdag)
        .value("t",qc::OpType::T)
        .value("tdag",qc::OpType::Tdag)
        .value("v",qc::OpType::V)
        .value("vdag",qc::OpType::Vdag)
        .value("u3",qc::OpType::U3)
        .value("u2",qc::OpType::U2)
        .value("phase",qc::OpType::Phase)
        .value("sx",qc::OpType::SX)
        .value("sxdag",qc::OpType::SXdag)
        .value("rx",qc::OpType::RX)
        .value("ry",qc::OpType::RY)
        .value("rz",qc::OpType::RZ)
        .value("swap",qc::OpType::SWAP)
      .value("iswap",qc::OpType::iSWAP)
        .value("peres",qc::OpType::Peres)
        .value("peresdag",qc::OpType::Peresdag)
        .value("dcx",qc::OpType::DCX)
        .value("ecr",qc::OpType::ECR)
        .value("rxx",qc::OpType::RXX)
        .value("ryy",qc::OpType::RYY)
        .value("rzz",qc::OpType::RZZ)
        .value("rzx",qc::OpType::RZX)
        .value("xx_minus_yy",qc::OpType::XXminusYY)
        .value("xx_plus_yy",qc::OpType::XXplusYY)
        .value("compound",qc::OpType::Compound)
        .value("measure",qc::OpType::Measure)
        .value("reset",qc::OpType::Reset)
        .value("snapshot",qc::OpType::Snapshot)
        .value("showprobabilities",qc::OpType::ShowProbabilities)
        .value("barrier",qc::OpType::Barrier)
        .value("teleportation",qc::OpType::Teleportation)
        .value("classiccontrolled",qc::OpType::ClassicControlled)
        // .value("atrue",qc::OpType::ATrue)
        // .value("afalse",qc::OpType::AFalse)
        // .value("multi_a_true",qc::OpType::MultiATrue)
        // .value("multi_a_false",qc::OpType::MultiAFalse)
        // .value("opcount",qc::OpType::OpCount)
    .export_values();

  m.def("optype_from_string", &qc::opTypeFromString);
}

} // namespace mqt

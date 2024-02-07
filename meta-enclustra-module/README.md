# Yocto BSP Layer for Enclustra Modules equipped with Intel FPGA SoCs

This layer provides support for Enclustra System-on-Chip modules equipped with Intel FPGA SoCs.

For more information on available Enclustra Modules, please visit:

https://www.enclustra.com/en/products/system-on-chip-modules/

# Dependencies

This Yocto layer depends on:

URI: https://git.openembedded.org/openembedded-core<br>
layers: meta<br>
revision: 2023-04.2-mickledore

URI: https://git.yoctoproject.org/meta-intel-fpga<br>
revision: mickledore

URI: http://git.openembedded.org/meta-openembedded<br>
layers: meta-oe, meta-python, meta-networking<br>
revision: mickledore

# Submit Patches / Reporting Bugs

Please report bugs or submit patches against the meta-enclustra-module layer to following address:

support@enclustra.com

# Building Instructions

See [README](../README.md)

# License

All metadata is MIT licensed unless otherwise stated. Source code included in tree for individual recipes are under the LICENSE stated in the associated recipe (.bb file) unless otherwise stated.

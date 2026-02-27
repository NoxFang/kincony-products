# Products Software Solutions

This repository provides software resources for IoT controllers, including:

1. **ESP32 I/O Pin Definitions** – GPIO assignments for each product.
2. **ESPHome Configuration Files** – Ready-to-use YAML for Home Assistant integration.
3. **Arduino Demo Source Code** – Example sketches demonstrating basic functionalities.

## Repository Structure

- `pin_definitions/` - ESP32 I/O pin definitions for each product
  - `B4M_pin_definition.md`

- `esphome_configs/` - ESPHome YAML configuration files for Home Assistant
  - `B4M_esphome_with_tuya.yaml`
  - `B4M_esphome_without_tuya.yaml`

- `arduino_demos/` - Arduino example source code
  - `B4M/` - Product-specific demos
    - `01_sequential_on_off/`
      - `src/` - Source code (.ino)
      - `precompiled/` - Precompiled binaries (.bin)
      - `README.md`
    - `02_read_digital_inputs/`
      - `src/`
      - `precompiled/`
      - `README.md`
    - (more demos will be added)

## How to Use

- Clone the repository:
  git clone https://github.com/NoxFang/kincony-products.git
- Navigate to the folder of your product (e.g., arduino_demos/KC_B4M/).
- Read the README.md inside each demo or config folder for specific instructions.

## Contributing

Feel free to open issues or pull requests if you have improvements or additional examples. Please follow the existing folder structure and naming conventions.

## License

This project is licensed under the MIT License – see the LICENSE file for details.

## Support

Code issues: Open an issue on GitHub
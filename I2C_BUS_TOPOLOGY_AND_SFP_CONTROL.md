# AS5610-52X I2C Bus Topology and SFP Control

## I2C Controllers

The P2020 SoC has two MPC I2C controllers:
- **i2c-0** (ff703000.i2c): Management/platform bus
- **i2c-1** (ff703100.i2c): SFP/QSFP data and control buses

## Bus Number Mapping

Total: 70 I2C buses (i2c-0 through i2c-69).

### Management Bus (i2c-0)

```
i2c-0
└── PCA9548 @ 0x70 (8-channel)
    ├── ch0 → i2c-2:  RTC (rtc8564 @ 0x51)
    ├── ch1 → i2c-3:  PSU1 EEPROMs (0x3a, 0x3e, 0x78)
    ├── ch2 → i2c-4:  PSU2 EEPROMs (0x0c, 0x39, 0x3d, 0x78)
    ├── ch3-6 → i2c-5 to i2c-8: (empty)
    └── ch7 → i2c-9:  MAX6697 @ 0x4d (hwmon1), MAX1617 @ 0x18 (hwmon0)
```

### SFP/QSFP Bus (i2c-1)

```
i2c-1
├── PCA9546 @ 0x75 (4-channel, deselect-on-exit)
│   ├── ch0 → i2c-10 → PCA9548 @ 0x74 → i2c-22..29 (ports 1-8)
│   ├── ch1 → i2c-11 → PCA9548 @ 0x74 → i2c-30..37 (ports 9-16)
│   ├── ch2 → i2c-12 → PCA9548 @ 0x74 → i2c-38..45 (ports 17-24)
│   └── ch3 → i2c-13 → PCA9548 @ 0x74 → i2c-46..53 (ports 25-32)
│
├── PCA9546 @ 0x76 (4-channel, deselect-on-exit)
│   ├── ch0 → i2c-14 → PCA9548 @ 0x74 → i2c-54..61 (ports 33-40)
│   ├── ch1 → i2c-15 → PCA9548 @ 0x74 → i2c-62..69 (ports 41-48)
│   ├── ch2 → i2c-16: GPIO control bus 1 (PCA9506 @ 0x20, 0x21)
│   └── ch3 → i2c-17: GPIO control bus 2 (PCA9506 @ 0x20, 0x23, 0x24)
│
└── PCA9546 @ 0x77 (4-channel, deselect-on-exit)
    ├── ch0 → i2c-18: QSFP port 49 (sff8436 @ 0x50, ds100df410 @ 0x27)
    ├── ch1 → i2c-19: QSFP port 50
    ├── ch2 → i2c-20: QSFP port 51
    └── ch3 → i2c-21: QSFP port 52
```

### Per-Port Bus Formula

**Port N = I2C bus (21 + N)**

| Port Range | Bus Range | Mux Path | Retimer Label |
|-----------|-----------|----------|---------------|
| 1-4 | 22-25 | 0x75/ch0 → 0x74/ch0-3 | sfp_rx_eq_0..3 |
| 5-8 | 26-29 | 0x75/ch0 → 0x74/ch4-7 | (none) |
| 9-12 | 30-33 | 0x75/ch1 → 0x74/ch0-3 | sfp_rx_eq_4..7 |
| 13-16 | 34-37 | 0x75/ch1 → 0x74/ch4-7 | (none) |
| 17-20 | 38-41 | 0x75/ch2 → 0x74/ch0-3 | sfp_rx_eq_8..11 |
| 21-24 | 42-45 | 0x75/ch2 → 0x74/ch4-7 | (none) |
| 25-28 | 46-49 | 0x75/ch3 → 0x74/ch0-3 | sfp_tx_eq_0..3 |
| 29-32 | 50-53 | 0x75/ch3 → 0x74/ch4-7 | (none) |
| 33-36 | 54-57 | 0x76/ch0 → 0x74/ch0-3 | sfp_tx_eq_4..7 |
| 37-40 | 58-61 | 0x76/ch0 → 0x74/ch4-7 | (none) |
| 41-44 | 62-65 | 0x76/ch1 → 0x74/ch0-3 | sfp_tx_eq_8..11 |
| 45-48 | 66-69 | 0x76/ch1 → 0x74/ch4-7 | qsfp_tx_eq_0..3 |
| 49-52 | 18-21 | 0x77/ch0-3 (direct) | qsfp_rx_eq_0..3 |

### Per-Port Devices

Each SFP+ port bus has:
- **EEPROM at 0x50**: at24c04 (SFP+) or sff8436 (QSFP+)
- **Retimer at 0x27**: DS100DF410 (only on ports with retimers, see table above)

## SFP GPIO Control

All SFP control signals use PCA9506 40-bit GPIO expanders on bus 17 (mux@0x76 ch3).

### GPIO Expander Assignments (from ONLP sfpi.c)

| Signal | PCA9506 Addr | Ports | Direction | Active Level |
|--------|-------------|-------|-----------|-------------|
| SFP_PRESENT | 0x20 | 0-39 | Input | LOW = present |
| TX_FAULT | 0x21 | 0-39 | Input | HIGH = fault |
| RX_LOS | 0x22 | 0-39 | Input | HIGH = loss |
| TX_DISABLE | 0x24 | 0-39 | Output | HIGH = TX enabled* |
| Mixed signals | 0x23 | 40-47 | Mixed | Various |

*TX_DISABLE polarity note: ONLP sets GPIO HIGH to enable TX, suggesting an inverter
between PCA9506 output and SFP+ TX_DISABLE pin (SFF-8431 spec: TX_DISABLE is active HIGH).

### PCA9506 Register Map

| Register | Offset | Description |
|----------|--------|-------------|
| IP0-IP4 | 0x00-0x04 | Input Port (read pin state) |
| OP0-OP4 | 0x08-0x0C | Output Port (write pin state) |
| PI0-PI4 | 0x10-0x14 | Polarity Inversion |
| IOC0-IOC4 | 0x18-0x1C | I/O Configuration (1=input, 0=output) |
| MSK0-MSK4 | 0x20-0x24 | Interrupt Mask |

### TX_DISABLE Pin Mapping (PCA9506 @ 0x24)

| Port | IOC Reg | OP Reg | Bit |
|------|---------|--------|-----|
| 1-8 | 0x18 | 0x08 | 0-7 |
| 9-16 | 0x19 | 0x09 | 0-7 |
| 17-24 | 0x1A | 0x0A | 0-7 |
| 25-32 | 0x1B | 0x0B | 0-7 |
| 33-40 | 0x1C | 0x0C | 0-7 |

To enable TX on port 1:
```python
# Configure pin as output (clear IOC bit)
ioc = i2c_read(17, 0x24, 0x18)
i2c_write(17, 0x24, 0x18, ioc & ~0x01)
# Set output HIGH (TX enabled)
op = i2c_read(17, 0x24, 0x08)
i2c_write(17, 0x24, 0x08, op | 0x01)
```

**CRITICAL**: After cold boot, IOC defaults to 0xFF (all inputs) and OP to 0x00.
TX_DISABLE is FLOATING until software configures the GPIO as output and drives it.

## DS100DF410 Retimer

TI quad-channel 10G retimer/equalizer. One per group of 4 SFP+ ports.

### Register Space Selection (0xFF)

| Value | Selection |
|-------|-----------|
| 0x00 | Shared/control registers |
| 0x04 | Channel 0 registers |
| 0x05 | Channel 1 registers |
| 0x06 | Channel 2 registers |
| 0x07 | Channel 3 registers |
| 0x0C | Broadcast to all channels |

### Key Channel Registers

| Addr | Name | Default | Notes |
|------|------|---------|-------|
| 0x01 | SIG_STATUS | 0x00 | bit0: loss of signal |
| 0x02 | CDR_STATUS | 0x00 | bit4: CDR locked, bit3: SBT met |
| 0x0A | CDR_RST | 0x10 | Write 0x1C (reset), then 0x10 (release) |
| 0x1E | PFD_PRBS_DFE | 0xE9 | bits[7:5]: OUT_MUX (7=MUTED!), bit3: DFE_PD |
| 0x2F | LOCK_RATE | 0x06 | bits[7:4]: rate (0xC=10.3125Gbps) |
| 0x31 | ADAPT_EQ_SM | 0x20 | bits[6:5]: mode (0=manual,1=CTLE,2=CTLE+DFE) |

**CRITICAL**: Default register 0x1E = 0xE9 means OUTPUT IS MUTED and DFE is powered down.
Must write 0x00 to unmute output and enable DFE.

### 10G SFI Initialization

```python
i2c_write(bus, 0x27, 0xFF, 0x0C)  # Broadcast all channels
i2c_write(bus, 0x27, 0x00, 0x04)  # Channel reset
i2c_write(bus, 0x27, 0x2F, 0xC0)  # Lock rate 10.3125 Gbps
i2c_write(bus, 0x27, 0x18, 0x00)  # VCO divider = 1
i2c_write(bus, 0x27, 0x1F, 0x52)  # LPF DAC for 10G
i2c_write(bus, 0x27, 0x31, 0x40)  # Adapt mode 2 (CTLE+DFE)
i2c_write(bus, 0x27, 0x1E, 0x00)  # Unmute output, enable DFE
i2c_write(bus, 0x27, 0x2D, 0x81)  # VOD
i2c_write(bus, 0x27, 0x0A, 0x1C)  # CDR reset
time.sleep(0.02)
i2c_write(bus, 0x27, 0x0A, 0x10)  # CDR release
```

## Source References

- **ONLP sfpi.c**: `/Users/smiley/Documents/Coding/edgecore/onl/packages/platforms/accton/powerpc/powerpc-accton-as5610-52x/onlp/builds/src/module/src/sfpi.c`
- **DTS**: `open-nos-as5610/boot/as5610_52x_full.dts`
- **TI DS100DF410 Programming Guide**: SNLA323
- **ONL ds100df410 driver patch**: `opennetworklinux/linux` 3.2.65 patches

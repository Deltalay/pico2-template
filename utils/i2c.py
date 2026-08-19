import math

# Fixed configuration
ic_clk_mhz = 150
spklen = 7
rise_ns = 100
fall_ns = 100

ic_clk = ic_clk_mhz * 1e6
t_clk = 1 / ic_clk

t_rise = rise_ns * 1e-9
t_fall = fall_ns * 1e-9

# name, frequency, minimum HIGH, minimum LOW
modes = [
    ("SS", 100, 4000, 4700),  # Standard Mode
    ("FS", 400, 600, 1300),  # Fast Mode
    ("FM+", 1000, 260, 500),  # Fast Mode Plus
]

for name, scl_khz, high_ns, low_ns in modes:
    t_high = high_ns * 1e-9
    t_low = low_ns * 1e-9

    # Minimum HCNT and LCNT
    hcnt = math.ceil((t_high - t_fall) / t_clk) - spklen - 7
    lcnt = math.ceil((t_low + t_fall - t_rise) / t_clk) - 1

    # Calculate actual timing
    actual_high = (hcnt + spklen + 7) * t_clk + t_fall
    actual_low = (lcnt + 1) * t_clk - t_fall + t_rise
    target_period = 1 / (scl_khz * 1000)

    # Make sure HIGH + LOW is long enough for target frequency
    actual_period = actual_high + actual_low

    if actual_period < target_period:
        extra_cycles = math.ceil((target_period - actual_period) / t_clk)

        lcnt += extra_cycles

        actual_low = (lcnt + 1) * t_clk - t_fall + t_rise
        actual_period = actual_high + actual_low

    actual_scl = 1 / actual_period

    print(name + ":")
    print(f"Target SCL : {scl_khz} kHz")
    print(f"HCNT : {hcnt}")
    print(f"LCNT : {lcnt}")
    print(f"SCL HIGH : {actual_high * 1e9:.2f} ns")
    print(f"SCL LOW : {actual_low * 1e9:.2f} ns")
    print(f"Actual SCL : {actual_scl / 1000:.2f} kHz")

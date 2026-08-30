from math import ceil

IC_CLK = 150_000_000

MODE = [100_000, 400_000, 1_000_000]

MIN_SCL_LOW = [
    4.7,  # us
    1.3,  # us
    0.12,  # us
]

ADD_DATA = []

for i in range(len(MODE)):
    scl_period = 1 / MODE[i]
    ic_clk_period = 1 / IC_CLK

    total_count = round(scl_period / ic_clk_period)

    min_lcnt = ceil(MIN_SCL_LOW[i] * 1e-6 / ic_clk_period)

    lcnt = min_lcnt
    hcnt = total_count - lcnt

    ADD_DATA.append(
        {
            "SCL": MODE[i],
            "HCNT": hcnt,
            "LCNT": lcnt,
            "TOTAL": hcnt + lcnt,
        }
    )

for data in ADD_DATA:
    print(data)
